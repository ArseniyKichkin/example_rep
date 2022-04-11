#include <iostream>
#include <algorithm>
#include <random>
#include "chrono"
#include "vector"
#include "set"


class Time { // класс измерения времени
public:
    void start(std::chrono::time_point<std::chrono::steady_clock> t_b) {
        this->begin = t_b;
    }

    void end(std::chrono::time_point<std::chrono::steady_clock> t_e) {
        this->finish = t_e;
    }

    void el(std::chrono::time_point<std::chrono::steady_clock> end_time,
            std::chrono::time_point<std::chrono::steady_clock> start_time) {
        auto elapsed_ns = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        std::cout << elapsed_ns.count();
    }

    std::chrono::time_point<std::chrono::steady_clock> begin;
    std::chrono::time_point<std::chrono::steady_clock> finish;

};

int getRandomFloatingPointBetween_progressive(int min, int max) {
    std::random_device rd; // uniformly-distributed integer random number generator
    std::mt19937 gen(rd()); //инициализируем Вихрь Мерсенна случайным стартовым числом
    std::uniform_int_distribution<> dis(min, max);//uniform distribution between min and max
    return dis(gen);
}

int main(){
    std::vector<int> vct;
    std::set<int> st;
    int N = 100;
    for (int i = 0; i < N; ++i){
        int a = getRandomFloatingPointBetween_progressive(-100, 100);
        st.insert(a);
        vct.push_back(a);
    }
    std::sort(vct.begin(), vct.end());

    Time t;
    t.start(std::chrono::steady_clock::now());
    for (int i = 0; i < N; ++i){
        int a = getRandomFloatingPointBetween_progressive(-100, 100);
        st.insert(a);
    }
    t.end(std::chrono::steady_clock::now());
    std::cout << "Сет, 100 чисел: ";
    t.el(t.finish, t.begin);
    std::cout << " мкс" << '\n';


    t.start(std::chrono::steady_clock::now());
    for (int i = 0; i < N; ++i){
        int a = getRandomFloatingPointBetween_progressive(-100, 100);
        vct.push_back(a);
    }
    t.end(std::chrono::steady_clock::now());


    std::cout << "Вектор, 100 чисел: ";
    t.el(t.finish, t.begin);
    std:: cout << " мкс" << '\n';

// Действительно, времена выполнения двух операций почти одинаковы.


    return 0;
}