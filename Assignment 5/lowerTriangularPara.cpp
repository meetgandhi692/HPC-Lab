#include <stdio.h>
#include <omp.h>
#include<cstdlib>


#define N 35 // Size of the matrices
#define NUM_THREADS 8

int main() {
    int A[N][N];
    int B[N][N];
    int C[N][N];

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            C[i][j]=0;
            if(i>=j){
                A[i][j]=rand()%100;
                B[i][j]=rand()%100;
            }else{
                A[i][j]=0;
                B[i][j]=0;
            }
        }
    }

    int i, j;

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
    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel for private(i,j) shared(A,B,C)
    for (i = 0; i < N; i++) {
        for (j = 0; j <= i; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    printf("\nResultant Matrix C (Sum of Lower Triangular Matrices A and B):\n");
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
