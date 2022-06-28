#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define ARRAY_SIZE 1280
void do_block(int n, int si, int sj, int sk, double* A, double
	* B, double* C)
{
	for (int i = si; i < si + ARRAY_SIZE; ++i)
		for (int j = sj; j < sj + ARRAY_SIZE; ++j)
		{
			double cij = C[i + j * n];/* cij = C[i][j] */
			for (int k = sk; k < sk + ARRAY_SIZE; k++)
				cij += A[i + k * n] * B[k + j * n];/* cij+=A[i][k]*B[k][j] */
			C[i + j * n] = cij;/* C[i][j] = cij */
		}
}

void dgemm(int n, double* A, double* B, double* C)
{
	for (int sj = 0; sj < n; sj += ARRAY_SIZE)
		for (int si = 0; si < n; si += ARRAY_SIZE)
			for (int sk = 0; sk < n; sk += ARRAY_SIZE)
				do_block(n, si, sj, sk, A, B, C);
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