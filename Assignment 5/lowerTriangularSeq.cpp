#include <stdio.h>
#include <omp.h>
#include<cstdlib>


#define N 300 // Size of the matrices

void display(int A[N][N]){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}

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

    // printf("Matrix A:\n");
    // display(A);
    
    // printf("\nMatrix B:\n");
    // display(B);

    double stime = omp_get_wtime();
    for (i = 0; i < N; i++) {
        for (j = 0; j <= i; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    // printf("\nResultant Matrix C (Matrix Multiplication of A and B):\n");
    // display(C);
    double etime = omp_get_wtime();
    double time = etime - stime;
    printf("\nTime taken is %f\n\n", time);
    return 0;
}
