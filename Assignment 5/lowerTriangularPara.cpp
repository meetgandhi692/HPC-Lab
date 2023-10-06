#include <stdio.h>
#include <omp.h>
#include<cstdlib>

#define N 400


void display(int A[N][N]){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n=1;
    for(n=2;n<51;n++){
        double paraTime=omp_get_wtime();
        int A[N][N], B[N][N], C[N][N];
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

        // printf("Matrix A:\n");
        // display(A);
        
        // printf("\nMatrix B:\n");
        // display(B);

        #pragma omp parallel for num_threads(n)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j <= i; j++) {
                C[i][j] = A[i][j] + B[i][j];
            }
        }

        // printf("\nResultant Matrix C (Matrix Multiplication of A and B):\n");
        // display(C);

        paraTime=omp_get_wtime()-paraTime;
        printf("Size: %d Threads: %d Parallel Time: %f\n",N,n, paraTime);
    }
    return 0;
}
