#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>

int main()
{
	int N;
	time_t t0, t1;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	printf("Однопоточный вариант.\n");
	printf("Введите размер матрицы: ");
	scanf_s("%d", &N);

	srand(time(0));
	double** m1 = (double**)malloc(N * sizeof(double*));
	double** m2 = (double**)malloc(N * sizeof(double*));
	double** r = (double**)malloc(N * sizeof(double*));

	for (int i = 0; i < N; i++) {
		m1[i] = (double*)malloc(N * sizeof(double));
		m2[i] = (double*)malloc(N * sizeof(double));
		r[i] = (double*)malloc(N * sizeof(double));
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			m1[i][j] = 0 + rand() % 11;
			m2[i][j] = 0 + rand() % 11;
			r[i][j] = 0;
		}
	}
	t0 = time(0);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				r[i][j] += m1[i][k] * m2[k][j];
	t1 = time(0);
	
	printf("Матрица 1:\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%g ", m1[i][j]);
		printf("\n");
	}
	printf("\n");

	printf("Матрица 2:\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%g ", m2[i][j]);
		printf("\n");
	}
	printf("\n");

	printf("Матрица 3:\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%g\t", r[i][j]);
		printf("\n");
	}
	
	double d = difftime(t1, t0);
	printf("Длительность выполнения умножения: %f", d);
	printf("\n");

	for (int i = 0; i < N; i++) {
		free(m1[i]);
		free(m2[i]);
		free(r[i]);
	}
	free(m1);
	free(m2);
	free(r);
	system("pause");
	return 0;
}
