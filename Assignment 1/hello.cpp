#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
#pragma omp parallel num_threads(16)

    {
        printf("thread No. %d  Hello World\n", omp_get_thread_num());
    }
    return 0;
}