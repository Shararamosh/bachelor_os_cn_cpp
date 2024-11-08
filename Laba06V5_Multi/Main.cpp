#include <iostream>
#include <mutex>
#include <thread>
#include <Windows.h>
#include <random>
#include <ctime>
#include <stdio.h>
#define ThrL 4
using namespace std;

typedef struct {
	int cols;
	int rows;
	int curRow;
	int** array1;
	int** array2;
	int** resArr;
} ThrData;

unsigned long uThrID;

DWORD WINAPI Thread(CONST LPVOID pParams)
{
	ThrData* data = (ThrData*)pParams;
	for (int i = data->curRow; i < data->rows; i++)
		for (int j = 0; j < data->cols; j++)
			for (int k = 0; k < data->cols; k++)
			{
				data->resArr[i][j] += data->array1[i][k] * data->array2[k][j];
			}
	cout << "This is thread." << endl;
	return 0;
}

void PrintMatrix(int** mat, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << mat[i][j] << ' ';
		cout << endl;
	}
	return;
}

int main()
{
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int** matrixA;
	int** matrixB;
	int** matrixC;
	int n;
	unsigned int t0, t1;
	ThrData* TData;
	TData = new ThrData[ThrL];
	cout << "Многопоточный вариант." << endl;
	cout << "Введите размер матрицы: " << endl;
	cin >> n;
	matrixA = new int* [n];
	matrixB = new int* [n];
	matrixC = new int* [n];
	for (int i = 0; i < n; i++)
	{
		matrixA[i] = new int[n];
		matrixB[i] = new int[n];
		matrixC[i] = new int[n];
	}
	HANDLE hThreads[ThrL];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matrixA[i][j] = rand() % 10;
			matrixB[i][j] = rand() % 10;
			matrixC[i][j] = 0;
		}
	}
	cout << "Сгенерирована матрица A:" << endl;
	PrintMatrix(matrixA, n);
	cout << "Сгенерирована матрица B:" << endl;
	PrintMatrix(matrixB, n);
	TData[0].curRow = 0;
	TData[0].rows = 1;
	TData[0].cols = n;
	TData[0].array1 = matrixA;
	TData[0].array2 = matrixB;
	TData[0].resArr = matrixC;
	t0 = clock();
	hThreads[0] = CreateThread(NULL, 0, &Thread, &TData[0], 0, &uThrID);
	for (int i = 1; i < ThrL - 1; i++)
	{
		TData[i].curRow = TData[i - 1].curRow + 1;
		TData[1].rows = TData[i - 1].curRow + i + 1;
		TData[i].cols = n;
		TData[i].array1 = matrixA;
		TData[i].array2 = matrixB;
		TData[i].resArr = matrixC;
		hThreads[i] = CreateThread(NULL, 0, &Thread, &TData[i], 0, &uThrID);
	}
	int i = ThrL - 1;
	TData[i].rows = n;
	TData[i].cols = n;
	TData[i].curRow = TData[i - 1].curRow + 1;
	TData[i].array1 = matrixA;
	TData[i].array2 = matrixB;
	TData[i].resArr = matrixC;
	hThreads[i] = CreateThread(NULL, 0, &Thread, &TData[i], 0, &uThrID);
	for (int i = 0; i < ThrL; i++)
	{
		WaitForSingleObject(hThreads[i], INFINITE);
	}
	for (int i = 0; i < ThrL; i++)
	{
		CloseHandle(hThreads[i]);
	}
	t1 = clock();
	double d = t1 - t0;
	cout << "Произведение матриц A и B:" << endl;
	PrintMatrix(matrixC, n);
	cout << "Время выполнения умножения: " << d << " миллисекунд." << endl;
	system("pause");
	return 0;
}