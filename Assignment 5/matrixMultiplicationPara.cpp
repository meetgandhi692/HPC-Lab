#include <bits/stdc++.h>
#include <omp.h>

#define N 200  // Size of the matrices
#define n 6 // Number of threads to use

void display(int A[N][N]){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int A[N][N],B[N][N],C[N][N],Cp[N][N];
    srand(time(NULL));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            A[i][j]=rand()%10;
            B[i][j]=rand()%10;
            C[i][j]=0;
        }
    }
    int i, j, k;

    // printf("Matrix A:\n");
    // display(A);
    
    // printf("\nMatrix B:\n");
    // display(B);

    double stime = omp_get_wtime();
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    double seqTime=omp_get_wtime()-stime;
    double sptime = omp_get_wtime();
    #pragma omp parallel for num_threads(n) private(i, j, k) shared(A, B, Cp)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                Cp[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    double paraTime = omp_get_wtime()-sptime;

    // printf("\nResultant Matrix C (Matrix Multiplication of A and B):\n");
    // display(C);
    
    printf("Size: %d\nThreads: %d\nSeq Time: %f\nParallel Time: %f\n\n",N,n,seqTime, paraTime);
    return 0;
}
