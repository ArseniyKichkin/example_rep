#include "iostream"
#include "string"
#include "fstream"
using namespace std;


int main(){
    string Path = "file1.txt";
    ofstream fout;
    fout.open(Path);

    int len;
    cout << "Введите длину каждой строки: " << endl;
    cin >> len;
    auto size = len * sizeof(char);

    int number;
    cout << "Введите количество строк: " << endl;
    cin >> number;

    if(!fout.is_open()) cout << "Ошибка!" << endl;
    else {
        cout << "Введите строки: ";
        for (int i = 0; i < number; ++i){
            string x;
            cin >> x;
            fout << x << endl;
        }
    }

    fout.close();
    int row;
    cout << "Введите номер строки, которую нужно вывести: " << endl;
    cin >> row;

    ifstream fin;
    fin.open(Path);
    if (fin.is_open()){
        fin.seekg(row * (size + 1));
    }
    char ch;
    string line;
    getline(fin, line);
    cout << line;


    return 0;
}