#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 12
#define n 4

void hello_world() {
    printf("Hello world\n");
}

void print(int i) {
    printf("Value %d\n", i);
}

int main() {
    double time=omp_get_wtime();
    #pragma omp parallel num_threads(n)
    {
        #pragma omp for nowait 
        for (int i = 0; i < N; i++) {
            printf("i: %d, thread: %d\n",i,omp_get_thread_num());
        }
        hello_world();
    }
    time=omp_get_wtime()-time;
    printf("Time: %f\n",time);
}
