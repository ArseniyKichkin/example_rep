#include <iostream>
#include <memory>

class BankCell{
public:
    BankCell(int money = 0) : _money(money) {}
    int getMoney(){
        return _money;
    }
    ~BankCell(){
        std::cout << "Cell destroyed\n";
    }
private:
    int _money;
};


class Human{
public:
    Human() = default;
    Human(std::shared_ptr<BankCell> ptr) : _ptr(ptr) {}
    std::shared_ptr<BankCell> getCell(){
        return _ptr;
    }
private:
    std::shared_ptr<BankCell> _ptr;
};


int main() {
    BankCell *cell = new BankCell(1000);
    std::shared_ptr<BankCell> cell_ptr(cell);
    Human Arseniy = Human(cell_ptr);
    std::cout << "Arseniy's money: " << Arseniy.getCell()->getMoney() << '\n';
    {
        std::shared_ptr<BankCell> cell_ptr_1(Arseniy.getCell());
        Human Ivan = Human(cell_ptr_1);
        std::cout << "Ivan's money: " << Ivan.getCell()->getMoney() << "\n";
        std::cout << "Killing the first pointer\n";
    }
    std::cout << "Killing the last pointer\n";
    return 0;
}