#include <memory>
#include <iostream>


class BankCell {
public:
	BankCell(int money) : _money(money) {}
	int getMoney() { return _money; }
private:
	int _money;
};

class Human{
public:
	Human(BankCell * ptr) : _ptr(ptr) {}
	BankCell* operator -> () { return _ptr; }
	BankCell& operator * () { return *_ptr; }
	BankCell* _ptr;
};

int main() {
	BankCell* cell = new BankCell(1000);
	Human Arseniy = Human(cell);
	std::cout<<(*Arseniy).getMoney();
}

