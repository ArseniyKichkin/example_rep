#include <iostream>
#include <memory>

template<typename T>

class AutoPtr {
public:
	AutoPtr(T* data) : m_data(data) {}
	~AutoPtr() {
		if (m_data != nullptr)
			delete m_data;
	}
	T* operator->() { return m_data; }
	T* operator*() { return *m_data; }
	
private:
	T* m_data;
};

class Student {
public:
	Student() { std::cout << "I became a student\n"; }
	~Student() { std::cout << "I did not pass exams\n"; }
	std::string name = "Ivan-MIPT";
};


int main() {
	Student* s = new Student();
	std::cout << s->name;
	AutoPtr<Student> ptr_student(new Student());
	{
		AutoPtr<Student> ptr_student_copy(new Student());
	}
	std::cout << "Finish";
	std::unique_ptr<Student>* array_ptr = new std::unique_ptr<Student>[10];
	std::unique_ptr<std::unique_ptr<Student>> array_ptr = unique;
	delete[] array_ptr;
}