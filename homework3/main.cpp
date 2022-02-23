#include <stack>
#include "vector"
#include "iostream"
#include "chrono"


void printStack(std::stack<int> & s){
    std::vector<int> a;
    while(! s.empty()){
        std::cout<<s.top()<<'\n';
        a.push_back(s.top());
        s.pop();
    }
    for (auto it = a.rbegin(); it != a.rend(); ++it){
        s.push(*it);
    }
}

int main(){
    std::stack<int> s;
    for(int i = 0 ; i < 10; ++i){
        s.push(i);
    }
    auto start = std::chrono::steady_clock::now();
    printStack(s);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    printStack(s);
}