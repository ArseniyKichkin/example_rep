#include "cuda.h"
#include "stdio.h"


__global__ void matrixMultiplication(float *A, float *B, float *C, int N) {
    const int TILE_SIZE = 32;
    __shared__ float A_tile[TILE_SIZE][TILE_SIZE];
    __shared__ float B_tile[TILE_SIZE][TILE_SIZE];
    int row = blockIdx.y * TILE_SIZE + threadIdx.y;
    int col = blockIdx.x * TILE_SIZE + threadIdx.x;
    float sum = 0.0;

    for (int k = 0; k < N/TILE_SIZE; k++) {
        A_tile[threadIdx.y][threadIdx.x] = A[row*N + (k*TILE_SIZE + threadIdx.x)];
        B_tile[threadIdx.y][threadIdx.x] = B[(k*TILE_SIZE+threadIdx.y)*N + col];
        __syncthreads();

        for (int i = 0; i < TILE_SIZE; i++) {
            sum += A_tile[threadIdx.y][i] * B_tile[i][threadIdx.x];
        }
        __syncthreads();
    }
    C[row*N+col] = sum;
}

int main() {
    int N = 1024;
    size_t size = N * N * sizeof(float);

    float *A = (float*) malloc(size);
    float *B = (float*) malloc(size);
    float *C = (float*) malloc(size);

    float *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);

    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    dim3 blockDim(32, 32);
    dim3 gridDim((N + blockDim.x - 1) / blockDim.x, (N + blockDim.y - 1) / blockDim.y);

    matrixMultiplication<<<gridDim, blockDim>>>(d_A, d_B, d_C, N);

    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    free(A);
    free(B);
    free(C);

    return 0;
