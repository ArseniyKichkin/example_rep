#include <iostream>
#include "fstream"
#include "string"
#include "algorithm"

// NOTE THAT YOU HAVE TO SPECIFY YOUR OWN FULL PATH TO THE FILES!
std::string PATH = "/home/arsenii/example_rep/for_homework.txt";
std::string path = "/home/arsenii/example_rep/file1.txt";
std::string path2 = "/home/arsenii/example_rep/file2.txt";

void delete_single_comments(std::string Path_in, std::string Path_out) {
    std::string s;
    std::ofstream file2;
    std::ifstream file;
    file.open(Path_in);
    while (getline(file, s)) {
        if (s.find("//") != std::string::npos) {
            if (s.substr(s.find("//")).find('"') == std::string::npos) {
                file2.open(Path_out, std::ios_base::app);
                s = s.erase(s.find("//"), s.size() - s.find("//"));
                file2 << s << std::endl;
                file2.close();
            } else {
                std::string sub0 = s.substr(0, s.find("//"));
                std::string sub1 = s.substr(s.find("//"));
                std::string aux = sub1.substr(0, sub1.find('"'));
                std::string sub2 = sub1.substr(sub1.find('"'));
                if (sub2.find("//") != std::string::npos) {
                    file2.open(Path_out, std::ios_base::app);
                    sub2 = sub2.erase(sub2.find("//"), sub2.size() - sub2.find("//"));
                    file2 << sub0 + aux + sub2 << std::endl;
                    file2.close();
                } else {
                    file2.open(Path_out, std::ios_base::app);
                    file2 << sub0 + sub1 << std::endl;
                    file2.close();
                }
            }

        } else {
            file2.open(Path_out, std::ios_base::app);
            file2 << s << std::endl;
            file2.close();
        }


    }
    file.close();
}


void delete_multi_comments(std::string Path_in, std::string Path_out) {
    std::string a;
    std::ofstream file_out;
    std::ifstream file_in;
    file_in.open(Path_in);

    while (getline(file_in, a)) {
        if (a.find("/*") != std::string::npos or a.find("*/") != std::string::npos) {
            if (a.find("/*") != std::string::npos && a.find("*/") != std::string::npos) {
                a = a.erase(a.find("/*"), a.find("*/") - a.find("/*") + 2);
                file_out.open(Path_out, std::ios_base::app);
                file_out << a << std::endl;
                file_out.close();
            } else if (a.find("/*") != std::string::npos and a.find("*/") == std::string::npos) {
                a = a.erase(a.find("/*"), a.size() - a.find("/*"));
                file_out.open(Path_out, std::ios_base::app);
                file_out << a << std::endl;
                file_out.close();
            } else if (a.find("/*") == std::string::npos and a.find("*/") != std::string::npos) {
                a.erase();
                file_out.open(Path_out, std::ios_base::app);
                file_out << a << std::endl;
                file_out.close();
            }

        } else {
            file_out.open(Path_out, std::ios_base::app);
            file_out << a << std::endl;
            file_out.close();
        }
    }
    file_in.close();
}


int main() {

    delete_single_comments(PATH, path2);

    delete_multi_comments(path2, path);

    return 0;
}