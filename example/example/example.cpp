#include <iostream>

template<typename T>

class AutoPtr {
public:
	AutoPtr(T* data) : m_data(data) {}
	~AutoPtr() {
		if (m_data != nullptr)
			delete m_data;
	}
private:
	T* m_data;
};

class Student {
public:
	Student() { std::cout << "I became a student\n"; }
	~Student() { std::cout << "I did not pass exams\n"; }
};


int main() {
	AutoPtr<Student> ptr_student(new Student());
	{
		AutoPtr<Student> ptr_student2(new Student());
	}
	std::cout << "Finish";
}