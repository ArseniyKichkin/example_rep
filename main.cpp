#include "vector"
#include "iostream"
#include "chrono"
#include "array"
#include "deque"
#include "list"
#include "forward_list"
#include "algorithm"


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

int main() {
    {
        std::vector<int> v{1, 2, 3, 4, 5}; // создаем вектор на 5 элементов
        std::cout << v.capacity() << ' ' << v.size() << '\n';
        v.push_back(1); // добавляем 1 элемент в конец
        std::cout << v.capacity() << ' ' << v.size()
                  << '\n'; // видим, что емкость вектора при нехватке места увеличивается вдвое по сравнению с изначальной
        v.resize(15); // при вызове метода resize() исходная емкость увеличивается до 15
        std::cout << v.capacity() << ' ' << v.size() << '\n';
        v.push_back(1);
        std::cout << v.capacity() << ' ' << v.size()
                  << '\n'; // при нехватке места емкость снова увеличивается в два раза, но уже относительно
        // новой емкости, указанной в методе resize()
        //v.resize(60000000);
        v.push_back(1);
        std::cout << v.capacity() << ' ' << v.size()
                  << '\n'; // поэксперементировав с выделением очень большого количества элементов вектора, я обнаружил, что предел для него на моем компьютере составляет
        // число элементов типа int между 1400000000 и 1500000000. Когда вектор пытается увеличить емкость при нехватке места, запросив такое количество памяти, компьютер зависает и через некоторое время прерывает выполнение программы кодом SigKill
        // Возможно, на ОС Windows это работает не так, и в предельном случае емкость увеличивается не в два раза, а лишь на количество добавляемых элементов (нет возможности проверить, т.к. Windows на моем компьютере сломался)
        std::cout << "====================" << '\n';
    }

    {
        std::array<int, 1000> arr;
        std::vector<int> vect(1000);
        std::deque<int> deq(1000);
        std::list<int> lst(1000);
        std::forward_list<int> f_lst(1000);

        Time t;
        t.start(std::chrono::steady_clock::now());
        std::sort(arr.begin(), arr.end());
        t.end(std::chrono::steady_clock::now());

        std::cout << "Время сортировки массива на 1000 элементов: ";
        t.el(t.finish, t.begin);
        std::cout << " мкс" << '\n';

        t.start(std::chrono::steady_clock::now());
        std::sort(vect.begin(), vect.end());
        t.end(std::chrono::steady_clock::now());

        std::cout << "Время сортировки вектора на 1000 элементов: ";
        t.el(t.finish, t.begin);
        std::cout << " мкс" << '\n';

        t.start(std::chrono::steady_clock::now());
        std::sort(deq.begin(), deq.end());
        t.end(std::chrono::steady_clock::now());

        std::cout << "Время сортировки стека на 1000 элементов: ";
        t.el(t.finish, t.begin);
        std::cout << " мкс" << '\n';

        t.start(std::chrono::steady_clock::now());
        lst.sort();
        t.end(std::chrono::steady_clock::now());

        std::cout << "Время сортировки двусвязного списка на 1000 элементов: ";
        t.el(t.finish, t.begin);
        std::cout << " мкс" << '\n';

        t.start(std::chrono::steady_clock::now());
        f_lst.sort();
        t.end(std::chrono::steady_clock::now());

        std::cout << "Время сортировки односвязного списка на 1000 элементов: ";
        t.el(t.finish, t.begin);
        std::cout << " мкс" << '\n';
    }

    std::cout << "==============" << '\n';

    {
        std::array<int, 1000000> arr;
        std::vector<int> vect(1000000);
        std::deque<int> deq(1000000);
        std::list<int> lst(1000000);
        std::forward_list<int> f_lst(1000000);

        Time t;
        t.start(std::chrono::steady_clock::now());
        std::sort(arr.begin(), arr.end());
        t.end(std::chrono::steady_clock::now());

        std::cout << "Время сортировки массива на 1000000 элементов: ";
        t.el(t.finish, t.begin);
        std::cout << " мкс" << '\n';

        t.start(std::chrono::steady_clock::now());
        std::sort(vect.begin(), vect.end());
        t.end(std::chrono::steady_clock::now());

        std::cout << "Время сортировки вектора на 1000000 элементов: ";
        t.el(t.finish, t.begin);
        std::cout << " мкс" << '\n';

        t.start(std::chrono::steady_clock::now());
        std::sort(deq.begin(), deq.end());
        t.end(std::chrono::steady_clock::now());

        std::cout << "Время сортировки стека на 1000000 элементов: ";
        t.el(t.finish, t.begin);
        std::cout << " мкс" << '\n';

        t.start(std::chrono::steady_clock::now());
        lst.sort();
        t.end(std::chrono::steady_clock::now());

        std::cout << "Время сортировки двусвязного списка на 1000000 элементов: ";
        t.el(t.finish, t.begin);
        std::cout << " мкс" << '\n';

        t.start(std::chrono::steady_clock::now());
        f_lst.sort();
        t.end(std::chrono::steady_clock::now());

        std::cout << "Время сортировки односвязного списка на 1000000 элементов: ";
        t.el(t.finish, t.begin);
        std::cout << " мкс" << '\n';
    }
    // При сортировке контейнеров с 1000 элементами лидирует статический массив. На втором месте оказывается односвязный
    // список, и третьим является динамический вектор.
    // В большинстве случаев односвязный список сортируется быстрее вектора, но бывает, что иногда проигрывает ему.
    // На четвертом месте по скорости оказывается стек, а медленнее всего сортируется двусвязный список.

    // В случае сортировки с 1000000 элементов ситуация та же, но теперь стек становится самым медленным, уступая
    // двусвязному списку.
}