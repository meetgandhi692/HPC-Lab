#include <iostream>
#include <omp.h>

#define num 1

int fibonacci(int n) {
    if (n <= 1)
        return n;

    int x, y;
    #pragma omp task shared(x) if(n > 20)
    x = fibonacci(n - 1);

    #pragma omp task shared(y) if(n > 20)
    y = fibonacci(n - 2);

    #pragma omp taskwait
    return x + y;
}

int main() {
    int n = 45;

    long long int result=0;
    double time=omp_get_wtime();
    #pragma omp parallel num_threads(num)
    {
        #pragma omp single nowait
        {
            result = fibonacci(n);
        }
    }
    time=omp_get_wtime()-time;
    printf("%dth term is %d\n",n, result);
    printf("Threads: %d\nTime: %f\n",num,time);
    return 0;
}
