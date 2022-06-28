#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>


#define ARRAY_SIZE 1280 //en son 1280 çalýþtýrmýþým kitaptaki kod bu þekilde AVX (daha önceki video denemeleri :D)


void dgemm(int n, double* A, double* B, double* C)
{
	for (int i = 0; i < n; i += 4)
		for (int j = 0; j < n; j++) {
			__m256d c0 = _mm256_load_pd(C + i + j * n); /* c0 = C[i][j] */
			for (int k = 0; k < n; k++)
				c0 = _mm256_add_pd(c0, /* c0 += A[i][k]*B[k][j] */
					_mm256_mul_pd(_mm256_load_pd(A + i + k * n),
						_mm256_broadcast_sd(B + k + j * n)));
			_mm256_store_pd(C + i + j * n, c0); /* C[i][j] = c0 */

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

	printf("optimized DGEMM code took (1280x1280) %.6f seconds to execute.\n", elapsed_time);
	return 0;
}
