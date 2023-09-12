#include <omp.h>
#include <pthread.h>
#include <stdio.h>

int main() {
    int N = 100000;
    int A[N];
    for (int i = 0; i < N; i++)
        A[i] = 20;
    int S = 2;

    double itime;
    itime = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        A[i] *= S;
        // printf("Index: %d Thread: %d\n", i, omp_get_thread_num());
    }
    double ftime = omp_get_wtime();

    // for (int i = 0; i < N; i++) {
    //     printf("%d ", A[i]);
    // }

    double exec_time = ftime - itime;
    printf("\nNumber of indexes: %d\nTime taken is %f\n",N,exec_time);
    printf("\n");
}
