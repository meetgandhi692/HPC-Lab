#include <stdio.h>
#include <omp.h>

#define N 3  // Size of the matrices
#define NUM_THREADS 8  // Number of threads to use

int main() {
    int A[N][N]={
        {1, 2, 3},
        {3, 2, 1},
        {2, 3, 1}
    };
    int B[N][N]={
        {3, 2, 1},
        {2, 3, 1},
        {1, 2, 3}
    };
    int C[N][N];
    int i, j, k;

    printf("Matrix A:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    double stime = omp_get_wtime();
    // Perform matrix multiplication in parallel using OpenMP
    omp_set_num_threads(NUM_THREADS);  // Set the number of threads to use

    #pragma omp parallel for private(i, j, k) shared(A, B, C)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0; // Initialize the result matrix element to 0
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("\nResultant Matrix C (Matrix Multiplication of A and B):\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    double etime = omp_get_wtime();
    double time = etime - stime;
    printf("\nTime taken is %f\n\n", time);
    return 0;
}
