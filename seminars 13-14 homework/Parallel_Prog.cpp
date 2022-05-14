#include<stdio.h>
#include<math.h>
#include <thread>
#include "iostream"
#include "chrono"


double circle(double, double);


void direct(int limit_a, int limit_Nmax, int min_a) {
    double x, y, Pi;
    long long int a = min_a;
    int i = 0;
    double Ncirc = 0;
    double Nmax = a;
    while (a < limit_a) {
        Nmax = a;
        while (Nmax <= limit_Nmax) {
            Ncirc = 0;
            i = 0;
            while (i < Nmax) {
                x = (random() % (a * 1000)) / 1000;
                y = (random() % (a * 1000)) / 1000;
                if (
                        y * y
                        <=
                        circle(x, (a
                                   / 2))) {
                    Ncirc++;
                }
                i++;
            }

            Pi = (Ncirc / Nmax) * 4;
            Nmax *= 2;

            std::cout << a << " " << Nmax << " " << Pi << std::endl;
        }
        a *= 2;
    }
}

double circle(double x, double radius) {

    double y = radius * radius - x * x;
    return y;
}

int main() {
    {
        auto start = std::chrono::steady_clock::now();
        direct(1e7, 1e7, 100);
        auto finish = std::chrono::steady_clock::now();
        std::cout << std::endl << "======================" << std::endl;
        std::cout << "Non-parallel" << std::endl;
        std::cout << "Working time " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count()
                  << " ms"
                  << std::endl;
    }

    {
        auto start = std::chrono::steady_clock::now();
        std::thread a(direct, 1e7 / 2, 1e7, 100);
        std::thread b = std::thread(direct, 1e7, 1e7, 1e7 / 2);
        a.join();
        b.join();
        auto finish = std::chrono::steady_clock::now();
        std::cout << std::endl << "======================" << std::endl;
        std::cout << "Parallel" << std::endl;
        std::cout << "Working time " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count()
                  << " ms"
                  << std::endl;

    }
    return 0;
}