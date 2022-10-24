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

string GetExeFileName()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    return string(buffer);
}

string GetPath()
{
    string path = GetExeFileName();
    return path.substr(0, path.find_last_of("\\/"));
}

char* prepareDataForCreatorProcess(char* binaryFile, int reportsAmount) {
    char data[200] = "Creator ";
    strcat(data, binaryFile);
    strcat(data, " ");
    strcat(data, to_string(reportsAmount).c_str());
    return data;
}


void runCreatorProcess(char* data) {
    STARTUPINFOA startupInfo;
    PROCESS_INFORMATION proccessInformation;

    ZeroMemory(&startupInfo, sizeof(STARTUPINFOA));
    startupInfo.cb = sizeof(STARTUPINFOA);
    ZeroMemory(&proccessInformation, sizeof(proccessInformation));

    char path[200];
    strcpy(path, GetPath().c_str());
    strcat(path, "\\Creator.exe");

    if (!CreateProcessA(path, data, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &proccessInformation))
    {
        cout << "The creator process is not created.\n";
        return;
    }

    WaitForSingleObject(proccessInformation.hProcess, INFINITE);

    CloseHandle(proccessInformation.hThread);

    CloseHandle(proccessInformation.hProcess);
}

void readBinaryFile(char* filename) {
    ifstream in(filename, ios::binary);
    cout << "Employees:\n";
    while (in.peek() != EOF) {
        Employee employee;
        in.read((char*)&employee, sizeof(struct Employee));
        cout << "Employee number:\n" << employee.num << "\nEmployee name:\n" << employee.name << "\nEmployee hours:\n" << employee.hours << "\n\n";
    }
    in.close();
}
char* prepareDataForReporterProcess(char* binaryFileName, char* reportFileName, double pay)
{
    char data[200] = "Reporter ";
    char* a = strcat(data, binaryFileName);
    char* b = strcat(a, " ");
    char* c = strcat(b, reportFileName);
    char* d = strcat(c, " ");
    char* reporter = new char[200];
    strcpy(reporter, strcat(d, to_string(pay).c_str()));

    return reporter;
}

void runReporterProcess(char* data)
{
    STARTUPINFOA startupInfo;
    PROCESS_INFORMATION proccessInformation;

    ZeroMemory(&startupInfo, sizeof(STARTUPINFOA));
    startupInfo.cb = sizeof(STARTUPINFOA);
    ZeroMemory(&proccessInformation, sizeof(proccessInformation));

    char path[200];
    strcpy(path, GetPath().c_str());
    strcat(path, "\\Reporter.exe");

    if (!CreateProcessA(path, data, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &proccessInformation))
    {
        cout << "The creator process is not created.\n";
        return;
    }

    WaitForSingleObject(proccessInformation.hProcess, INFINITE);

    CloseHandle(proccessInformation.hThread);

    CloseHandle(proccessInformation.hProcess);
}

void readFile(char* fileName)
{
    ifstream fin(fileName);

    char line[200];
    while (!fin.eof())
    {
        fin.getline(line, 200);
        cout << line << "\n";
    }

    fin.close();
}

int main() {
    char* binaryFileName = new char[30];
    cout << "Enter binary file name:\n";
    cin >> binaryFileName;
    cout << "\n";

    int reportsAmount;
    cout << "Enter reports amount:\n";
    cin >> reportsAmount;
    cout << "\n";

    char* dataForCreator = prepareDataForCreatorProcess(binaryFileName, reportsAmount);
    cout << dataForCreator << "\n";
    runCreatorProcess(dataForCreator);

    readBinaryFile(binaryFileName);

    char* fileReportName = new char[30];
    cout << "\nEnter file report name:\n";
    cin >> fileReportName;
    cout << "\n";

    double pay;
    cout << "Enter pay for hour:\n";
    cin >> pay;
    cout << "\n";

    char* dataForReporter = prepareDataForReporterProcess(binaryFileName, fileReportName, pay);
    cout << dataForReporter << "\n";
    runReporterProcess(dataForReporter);

    readFile(fileReportName);

    return 0;
}
