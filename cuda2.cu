#include <cuda.h>
#include <stdio.h>
#include <time.h>
#define TILE_SIZE 2

__global__ void matrixMultiplication(float *A, float *B, float *C, int N) {
//    __shared__ float A_tile[TILE_SIZE][TILE_SIZE];
//    __shared__ float B_tile[TILE_SIZE][TILE_SIZE];
    __shared__ float A_tile[TILE_SIZE * TILE_SIZE];
    __shared__ float B_tile[TILE_SIZE * TILE_SIZE];
    int row = blockIdx.y * TILE_SIZE + threadIdx.y;
    int col = blockIdx.x * TILE_SIZE + threadIdx.x;
    float sum = 0.0;

    for (int k = 0; k < N/TILE_SIZE; k++) {
//        A_tile[threadIdx.y][threadIdx.x] = A[row*N + (k*TILE_SIZE + threadIdx.x)];
//        B_tile[threadIdx.y][threadIdx.x] = B[(k*TILE_SIZE+threadIdx.y)*N + col];
          A_tile[threadIdx.y * TILE_SIZE + threadIdx.x] = A[row*N + (k*TILE_SIZE + threadIdx.x)];
          B_tile[threadIdx.y * TILE_SIZE + threadIdx.x] = B[(k*TILE_SIZE+threadIdx.y)*N + col];

        __syncthreads();

        for (int i = 0; i < TILE_SIZE; i++) {
//            sum += A_tile[threadIdx.y][i] * B_tile[i][threadIdx.x];
              sum += A_tile[threadIdx.y * TILE_SIZE  + i] * B_tile[i * N + threadIdx.y];
        }
        __syncthreads();
    }
    C[row*N+col] = sum;
}
clock_t start, end;
float time_used;

int main() {
    int N = 4;
    size_t size = N * N * sizeof(float);

    float *A = (float*) malloc(size);
    float *B = (float*) malloc(size);
    float *C = (float*) malloc(size);
    for (int row = 0; row < N; ++row){
        for (int col = 0; col < N; ++col){
            A[N * row + col] = col + N * row;
            B[N * row + col] = 2. * (col + N * row);
        }
    }
    for (int row = 0; row < N; ++row){
        printf("%f %f %f %f\n", A[row*N], A[row*N + 1], A[row*N + 2], A[row*N + 3]);
    }
    printf("\n");
    for (int row = 0; row < N; ++row){
        printf("%f %f %f %f\n", B[row*N], B[row*N + 1], B[row*N + 2], B[row*N + 3]);
    }
    printf("\n");



    float *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);



    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    dim3 blockDim(TILE_SIZE, TILE_SIZE);
    dim3 gridDim((N + blockDim.x - 1) / blockDim.x, (N + blockDim.y - 1) / blockDim.y);
    start = clock();
    matrixMultiplication<<<gridDim, blockDim>>>(d_A, d_B, d_C, N);

    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);
    end = clock();
    time_used = ((float) (end - start)) / CLOCKS_PER_SEC;

    for (int row = 0; row < N; ++row){
        printf("%f %f %f %f\n", C[row*N], C[row*N + 1], C[row*N + 2], C[row*N + 3]);
    }
    printf("%f\n", time_used);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    free(A);
    free(B);
    free(C);

    return 0;
}


