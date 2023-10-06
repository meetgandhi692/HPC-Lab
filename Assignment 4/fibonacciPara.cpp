#include <iostream>
#include <omp.h>

int fibonacci(int n) {
    if (n <= 1)
        return n;

    int x, y;
    #pragma omp task
    x = fibonacci(n - 1);

    #pragma omp task
    y = fibonacci(n - 2);

    #pragma omp taskwait
    return x + y;
}

int main() {
    double time=omp_get_wtime();
    int num=10;
    int n = 30;
    long long int result=0;
    #pragma omp parallel num_threads(num)
    {
        #pragma omp single nowait
        {
            result = fibonacci(n);
        }
    }
    printf("%dth term is %d\n",n, result);
    printf("Threads: %d\nTime: %f\n",num,time);
    time=omp_get_wtime()-time;
    return 0;
}
