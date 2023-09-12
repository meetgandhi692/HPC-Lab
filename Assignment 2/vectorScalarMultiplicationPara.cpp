#include <omp.h>
#include <stdio.h>
#define n 8

int main() {
    int N = 100000;
    int A[N];
    for(int i = 0; i < N; i++)
        A[i] = 20;
    int S=2;

    double itime;
    itime = omp_get_wtime();
    #pragma omp parallel for reduction(* : A) num_threads(n)
    for (int i = 0; i < N; i++) {
        A[i] *= S;
        // printf("Index: %d Thread: %d\n", i, omp_get_thread_num());
    }
    double ftime = omp_get_wtime();

    // for (int i = 0; i < N; i++) {
    //     printf("%d ", A[i]);
    // }

    double exec_time = ftime - itime;
    printf("\nNumber of total threads: %d\nNumber of indexes: %d\nTime taken is %f\n",n,N,exec_time);
    printf("\n");
}
