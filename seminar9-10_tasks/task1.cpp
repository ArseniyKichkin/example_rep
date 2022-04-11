#include <iostream>
#include <algorithm>
#include <random>


//std::vector<std::string> lst = {'Monkey', 'Cherry', '7', 'Banana'};

int getRandomFloatingPointBetween_progressive(int min, int max) {
    std::random_device rd; // uniformly-distributed integer random number generator
    std::mt19937 gen(rd()); //инициализируем Вихрь Мерсенна случайным стартовым числом
    std::uniform_int_distribution<> dis(min, max);//uniform distribution between min and max
    return dis(gen);
}

auto lambda_abs = [](int left, int right){return std::abs(left) < std::abs(right);};

int main(){
    //std::vector<int> result(3);
    //for (int i = 0; i < 3; ++i){
    //    result.at(i) = getRandomFloatingPointBetween_progressive(1, 4);
    //}
    //for (auto x : result){
    //    std::cout << x << '\n';
    //}
    std::vector<int> row (10);
    for (int i = 0; i < row.size(); ++i){
        row.at(i) = getRandomFloatingPointBetween_progressive(-2, 2);
    }

    for (auto x : row){
        std::cout << x << ' ';
    }
    std::cout << '\n';

    std::sort(row.begin(), row.end(), lambda_abs);

    for (auto x : row){
        std::cout << x << ' ';
    }
}