#include <iostream>
#include <windows.h>
#include <iostream>
using namespace std;



struct Parametr {
	int  n;
	int* arr;
};

DWORD WINAPI minmax(LPVOID param)
{
	Parametr* parametr = (Parametr*) param;
	int max = parametr->arr[0], min = parametr->arr[0];
	for (int i = 1; i < parametr->n; i++) {
		if (parametr->arr[i] > max) {
			max = parametr->arr[i];
		}
		else if (parametr->arr[i] < min) {
			min = parametr->arr[i];
		}
		Sleep(7);
	}

	cout << "max: " << max << " " << "min: " << min << endl;
	return 0;
}


DWORD WINAPI average(LPVOID param)
{
	Parametr* parametr = (Parametr*)param;
	double average = 0;

	for (int i = 0; i < parametr->n; i++) {
		average += parametr->arr[i];
		Sleep(12);
	}

	cout << "average: " << average / parametr->n << endl;
	return 0;
}

HANDLE StartMinMax(Parametr& param) {
	HANDLE Thread;
	DWORD  IDThread;

	Thread = CreateThread(NULL, 0, minmax, (void*)&param, 0, &IDThread);
	if (Thread == NULL)
		cout << "Tread is not begin";
	return Thread;
}

HANDLE StartAverage(Parametr& param) {
	HANDLE Thread;
	DWORD  IDThread;

	Thread = CreateThread(NULL, 0, average, (void*)&param, 0, &IDThread);
	if (Thread == NULL)
		cout << "Tread is not begin";
	return Thread;
}

int main()
{
	Parametr parametr;
	int n;

	cout << "Number of elements" << endl;
	cin >> n;
	parametr.n = n;

	int* arr = new int[n];
	cout << "Elements: ";
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	parametr.arr = arr;
    
	HANDLE firstThread = StartMinMax(parametr);
	HANDLE secondThread = StartAverage(parametr);

	WaitForSingleObject(firstThread, INFINITE);
	WaitForSingleObject(secondThread, INFINITE);

	CloseHandle(firstThread);
	CloseHandle(secondThread);


	return 0;
}

