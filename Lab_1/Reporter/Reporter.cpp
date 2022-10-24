#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "vector"
#include "algorithm"
using namespace std;
struct Employee {
    int num;
    char name[10];
    double hours;
};

bool compareEmpoyers(Employee& o1, Employee& o2) {
    return o1.num < o2.num;
}

vector<Employee> readEmployers(char* filename) {
    ifstream in(filename, ios::binary);
    vector<Employee> emloyers;
    while (in.peek() != EOF) {
        Employee eployee;
        in.read((char*)&eployee, sizeof(struct Employee));
        emloyers.push_back(eployee);
    }
    in.close();
    return emloyers;
}

int main(int argc, char* argv[]) {

    char* binFileName = argv[1];
    ofstream fout(argv[2]);
    double pay = atof(argv[3]);

    vector<Employee> employers = readEmployers(binFileName);
    sort(employers.begin(), employers.end(), compareEmpoyers);

    fout << "Отчет по файлу " << argv[0] << endl;

    for (int i = 0; i < employers.size(); i++) {
        fout << employers[i].num << " " << employers[i].name << " " << employers[i].hours << " " << employers[i].hours * pay << endl;
    }


    fout.close();
    system("pause");
    return 1;
}
