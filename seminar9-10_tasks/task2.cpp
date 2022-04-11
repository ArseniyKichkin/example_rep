#include <iostream>
#include <algorithm>
#include <random>
#include "vector"
#include "string"


std::vector<std::string> lst = {"Monkey", "Cherry", "7", "Banana"};

int getRandomFloatingPointBetween_progressive(int min, int max) {
    std::random_device rd; // uniformly-distributed integer random number generator
    std::mt19937 gen(rd()); //инициализируем Вихрь Мерсенна случайным стартовым числом
    std::uniform_int_distribution<> dis(min, max);//uniform distribution between min and max
    return dis(gen);
}

auto lambda_abs = [](int left, int right){return std::abs(left) < std::abs(right);};

int main() {
    std::vector<int> result(3);
    for (int i = 0; i < 3; ++i) {
        result.at(i) = getRandomFloatingPointBetween_progressive(0, 4);
    }
    for (auto x : result){
        std::cout << lst[x] << '\n';
    }
    if (result.at(0) == result.at(1) && result.at(0) == result.at(2)){
        std::cout << "You win!" << '\n';
    }
    else{
        std::cout << "You lost(" << '\n';
    }
}