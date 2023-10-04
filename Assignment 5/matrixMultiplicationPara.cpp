#include <bits/stdc++.h>
#include <omp.h>

#define N 300  // Size of the matrices

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
    for(int n=2;n<101;n++){
        double sptime = omp_get_wtime();
        srand(time(NULL));
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                A[i][j]=rand()%10;
                B[i][j]=rand()%10;
                C[i][j]=0;
            }
        }
        // printf("Matrix A:\n");
        // display(A);
        
        // printf("\nMatrix B:\n");
        // display(B);

        // #pragma omp parallel for num_threads(n) shared(A, B, Cp)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    Cp[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        // printf("\nResultant Matrix C (Matrix Multiplication of A and B):\n");
        // display(C);
        
        double paraTime = omp_get_wtime()-sptime;
        printf("Size: %d Threads: %d Parallel Time: %f\n",N,n, paraTime);
    }
    return 0;
}
