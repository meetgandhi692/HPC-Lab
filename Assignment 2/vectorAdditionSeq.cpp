#include <omp.h>
#include <stdio.h>

int main() {
    int N = 100000;
    int A[N];
    for (int i = 0; i < N; i++)
        A[i] = 10;

    int B[N];
    for (int i = 0; i < N; i++)
        B[i] = 20;

    int C[N] = {0};
    double stime = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
        // printf("Index: %d Thread: %d\n", i, omp_get_thread_num());
    }
    double etime = omp_get_wtime();

    // for (int i = 0; i < N; i++) {
    //     printf("%d ", C[i]);
    // }

    double time = etime - stime;
    printf("\nNumber of indexes: %d\nTime taken is %f\n",N,time);
    return 0;
}
