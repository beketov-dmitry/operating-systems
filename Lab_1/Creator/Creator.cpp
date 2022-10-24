#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#pragma warning(disable : 4996)

using namespace std;
struct Employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    char fileName[200];
    strcpy(fileName, argv[1]);
    ofstream fout(fileName, ios::binary);
    int num = atoi(argv[2]);
    for (int i = 0; i < num; i++)
    {
        Employee employee;
        cout << "Enter number:" << endl;
        cin >> employee.num;
        cout << "Enter employee name:" << endl;
        cin >> employee.name;
        cout << "Enter employee hours:" << endl;
        cin >> employee.hours;
        fout.write((char*)&employee, sizeof(struct Employee));
    }
    fout.close();
    system("pause");
    return 1;
}

