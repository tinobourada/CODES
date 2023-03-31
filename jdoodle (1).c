#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define M 1000
#define N 1000
#define K 1000

int A[M][K], B[K][N], C[M][N];

int main() {
    #pragma omp parallel for
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return 0;
}
