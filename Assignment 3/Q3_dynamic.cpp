#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000
#define n 4

int main() {
    int *a = (int *)malloc(sizeof(int) * N);
    int *c = (int *)malloc(sizeof(int) * N);
    int b = 10;
    for (int i = 0; i < N; i++) {
        a[i] = 0;
    }
    double itime, ftime, exec_time;
    itime = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic, 2)
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b;
    }
    ftime = omp_get_wtime();
    exec_time = ftime - itime;
    printf("Indexes: %d\nThreads: %d\nTime taken is %f\n",N,n, exec_time);
}
