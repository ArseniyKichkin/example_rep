#include "json.hpp"

#include <fstream>

#include <ostream>
#include <iostream>

using json = nlohmann::json;


int main(){
    std::fstream f_out("file_1.txt", std::ios::out);
    json j;
    std::string name;
    int age;
    std::cin >> name >> age;
    j["firstname"] = name;
    j["age"] = age;
    f_out <<  j;

    f_out.close();
    return 0;
};