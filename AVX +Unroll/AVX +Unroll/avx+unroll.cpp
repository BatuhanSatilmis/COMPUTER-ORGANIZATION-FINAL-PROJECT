#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define ARRAY_SIZE 1280 //v3 kodumuz bu þekilde
#define UNROLL (4)

void do_block(int n, int si, int sj, int sk,
	double* A, double* B, double* C)
{
	for (int i = si; i < si + ARRAY_SIZE; i += UNROLL * 4)
		for (int j = sj; j < sj + ARRAY_SIZE; j++) {
			__m256d c[4];
			for (int x = 0; x < UNROLL; x++)
				c[x] = _mm256_load_pd(C + i + x * 4 + j * n);
			/* c[x] = C[i][j] */
			for (int k = sk; k < sk + ARRAY_SIZE; k++)
			{
				__m256d b = _mm256_broadcast_sd(B + k + j * n);
				/* b = B[k][j] */
				for (int x = 0; x < UNROLL; x++)
					c[x] = _mm256_add_pd(c[x], /* c[x]+=A[i][k]*b */
						_mm256_mul_pd(_mm256_load_pd(A + n * k + x * 4 + i), b));
			}
			for (int x = 0; x < UNROLL; x++)
				_mm256_store_pd(C + i + x * 4 + j * n, c[x]);
			/* C[i][j] = c[x] */
		}
}
void dgemm(int n, double* A, double* B, double* C)
{
	for (int sj = 0; sj < n; sj += ARRAY_SIZE)
		for (int si = 0; si < n; si += ARRAY_SIZE)
			for (int sk = 0; sk < n; sk += ARRAY_SIZE)
				do_block(n, si, sj, sk, A, B, C);
}

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
	printf("optimized DGEMM code took (1280x1280) %.6f seconds to execute.\n", elapsed_time);
	return 0;
}
