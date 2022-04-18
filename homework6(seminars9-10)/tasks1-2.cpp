#include <iostream>
#include <random>
#include "algorithm"
#include "set"


double getRandomFloatingPointBetween_progressive(int min, int max) {
    std::random_device rd; // uniformly-distributed integer random number generator
    std::mt19937 gen(rd()); //инициализируем Вихрь Мерсенна случайным стартовым числом
    std::uniform_real_distribution<> dis(min, max);//uniform distribution between min and max
    return dis(gen);
}

class Hero {
private:
    std::string name;
    int health;
    int strength;

public:
    void Strike(Hero &otherHero) {
        int i = getRandomFloatingPointBetween_progressive(0, this->strength);
        if (i <= otherHero.health and otherHero.health > 0) otherHero.health -= i;
        else {
            std::cout << "Hero Elf dead" << '\n';
            otherHero.health = 0;
        }
    }

    int getHealth() {
        return health;
    }

    Hero(std::string name, int health, int strength) : name(name), health(health), strength(strength) {}
};

int main() {
    // Task 1
    {
        Hero One("First", 100, 50);
        Hero Two("Second", 100, 70);
        One.Strike(Two);
        One.Strike(Two);
        One.Strike(Two);
        One.Strike(Two);
        std::cout << Two.getHealth() << '\n';
    }
    // Task 2
    std::vector<int> seq{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (auto x: seq) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    // добавление нескольких элементов
    std::cout << "Enter 5 elms" << '\n';
    for (int i = 0; i < 5; ++i) {
        int j;
        std::cin >> j;
        seq.push_back(j);
    }
    for(auto x : seq){
        std::cout << x << " ";
    }
    std::cout << '\n';

    std::random_shuffle(seq.begin(), seq.end()); // перемешивание случайным образом

    for(auto x : seq){
        std::cout << x << " ";
    }
    std::cout << '\n';

    std::set<int> st;
    for (auto x: seq) {
        st.insert(x);
    }
    seq.clear();
    for (auto x: st)
        seq.push_back(x); // удаление дубликатов

    for(auto x : seq){
        std::cout << x << " ";
    }
    std::cout << '\n';


    std::cout << "Quantity of odd numbers: " <<  std::count_if(seq.begin(), seq.end(),[](int k)
    { return (k % 2 != 0); }) << '\n'; //кол-во нечетных элементов

    std::cout << "Max in seq: " << *std::max_element(seq.begin(), seq.end()) << '\n';
    std::cout << "Min in seq: " << *std::min_element(seq.begin(), seq.end()) << '\n';

    // Поиск простого числа
    for (int x : seq){
        if (x == 1) continue;
        if (x == 3) std::cout << "Prime number: " << x << '\n';
        if (x * x % 24 == 1) std::cout << "Prime number: " << x << '\n';
    }



    // Замена всех чисел их квадратами
    for (auto it = seq.begin(); it != seq.end(); ++it){
        *it = (*it) * (*it);
    }
    std::cout << "Squares of numbers: ";
    for(auto x : seq){
        std::cout << x << " ";
    }
    std::cout << '\n';

    std::vector<int> seq2;
    for(int i = 0; i < seq.size(); ++i){
        int a = getRandomFloatingPointBetween_progressive(-100, 100);
        seq2.push_back(a);
        std::cout << a << " ";
    }
    std::cout << "- Sequence 2" << '\n';

    int sum = 0;

    for (int x = 0; x < seq2.size(); ++x)
        sum += seq2[x];
    std::cout << "Sum of elms in seq2 = " << sum << '\n';


    for(auto x : seq2){
        std::cout << x << " ";
    }
    std::cout << '\n';
    seq2[0] = 1;
    seq2[1] = 1;
    seq2.resize(seq.size());

    for(auto x : seq2){
        std::cout << x << " ";
    }
    std::cout << " - substitution of the first 2 numbers with 1" << '\n';

    std::vector<int> seq3 (seq2.size());
    for (int i = 0; i < seq.size(); ++i){
        seq3[i] = seq[i] - seq2[i];
    }

    for(auto x : seq3){
        std::cout << x << " ";
    }
    std::cout << " - seq - seq2" << '\n';

    for (auto x = seq3.begin(); x < seq3.end(); ++x){
        if (*x < 0) *x = 0;
        if (*x == 0) seq3.erase(x);
    }

    for(auto x : seq3){
        std::cout << x << " ";
    }
    std::cout << " - zeros deleted and negative numbers substituted with zero" << '\n';

    std::reverse(seq3.begin(), seq3.end());
    for(auto x : seq3){
        std::cout << x << " ";
    }
    std::cout << " - reversed seq3" << '\n';

    std::sort(seq3.rbegin(), seq3.rend());
    for(int x = 0; x < 3; ++x){
        std::cout << seq3[x] << " ";
    }
    std::cout << "- top 3 biggest elements " << '\n';

    std::sort(seq.begin(), seq.end());
    for(auto x : seq3){
        std::cout << x << " ";
    }
    std::cout << " - sorted seq" << '\n';

    std::sort(seq2.begin(), seq2.end());
    for(auto x : seq3){
        std::cout << x << " ";
    }
    std::cout << " - sorted seq2" << '\n';

    std::vector<int> seq4 = seq;
    //seq4.resize(seq.size() + seq2.size());
    seq4.insert(seq4.end(), seq2.begin(), seq2.end());

    for(auto x : seq4){
        std::cout << x << " ";
    }
    std::cout << " - concatenation of seq and seq2" << '\n';
    std::cout << "======================" << '\n';

    return 0;
}