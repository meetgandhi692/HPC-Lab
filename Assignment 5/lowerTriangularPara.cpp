#include <stdio.h>
#include <omp.h>
#include<cstdlib>

#define N 10
#define n 6

void display(int A[N][N]){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int A[N][N], B[N][N], C[N][N], Cp[N][N];

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            C[i][j]=0;
            if(i>=j){
                A[i][j]=rand()%10;
                B[i][j]=rand()%10;
            }else{
                A[i][j]=0;
                B[i][j]=0;
            }
        }
    }

    int i, j;

    // printf("Matrix A:\n");
    // display(A);
    
    // printf("\nMatrix B:\n");
    // display(B);

    double seqTime=omp_get_wtime();
    for (i = 0; i < N; i++) {
        for (j = 0; j <= i; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    seqTime=omp_get_wtime()-seqTime;
    double paraTime=omp_get_wtime();
    #pragma omp parallel for private(i,j) shared(A,B,C) num_threads(n)
    for (i = 0; i < N; i++) {
        for (j = 0; j <= i; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    paraTime=omp_get_wtime()-paraTime;

    // printf("\nResultant Matrix C (Matrix Multiplication of A and B):\n");
    // display(C);

    printf("Size: %d\nThreads: %d\nSeq Time: %f\nParallel Time: %f\n\n",N,n,seqTime, paraTime);
    return 0;
}
