
#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define ARRAY_SIZE 1024 //unoptimized code

void dgemm(int n, const double* A, const double* B, double* C)
{
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			C[i * n + j] = 0;
			for (k = 0; k < n; k++)
			{
				C[i * n + j] += A[k + i * n] * B[k * n + j];
			}
		}
	}
}

int main()
{
	double* A = (double*)calloc(ARRAY_SIZE * ARRAY_SIZE, sizeof(double));
	double* B = (double*)calloc(ARRAY_SIZE * ARRAY_SIZE, sizeof(double));
	double* C1 = (double*)calloc(ARRAY_SIZE * ARRAY_SIZE, sizeof(double));
	double* C2 = (double*)calloc(ARRAY_SIZE * ARRAY_SIZE, sizeof(double));


	for (int i = 0; i < ARRAY_SIZE * ARRAY_SIZE; i++)
	{
		A[i] = rand() % 100;
		B[i] = rand() % 100;
	}

	clock_t t;

	t = clock();
	dgemm(ARRAY_SIZE, A, B, C1);
	t = clock() - t;

	double elapsed_time = ((double)t) / CLOCKS_PER_SEC;
	printf("Unoptimized DGEMM code took (1024x1024) %.6f seconds to execute.\n", elapsed_time);

	return 0;
}

