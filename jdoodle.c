#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M 1000
#define N 1000
#define K 1000
#define NUM_THREADS 4

int A[M][K], B[K][N], C[M][N];
pthread_t threads[NUM_THREADS];

void *multiply(void *arg) {
    int thread_id = *(int *)arg;
    int start = thread_id * M / NUM_THREADS;
    int end = (thread_id + 1) * M / NUM_THREADS;

    for (int i = start; i < end; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

int main() {
    int thread_ids[NUM_THREADS];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            A[i][j] = rand() % 100;
        }
    }

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            B[i][j] = rand() % 100;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, multiply, (void *)&thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
