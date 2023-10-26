#include <iostream>
#include <omp.h>

void parallel_prefix_sum(int* arr, int n,int nn) {
    #pragma omp parallel num_threads(nn)
    {
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();

        int chunk_size = n / num_threads;
        int start = thread_id * chunk_size;
        int end = (thread_id == num_threads - 1) ? n : start + chunk_size;

        for (int i = start + 1; i < end; ++i) {
            arr[i] += arr[i - 1];
        }

        int add_to_rest = (thread_id == num_threads - 1) ? arr[end - 1] : arr[end - 1] - arr[end];
        
        #pragma omp barrier
        for (int i = end; i < n; ++i) {
            arr[i] += add_to_rest;
        }
    }
}

int main() {
    int nn=1;
    for(nn=2;nn<51;nn++){
        int ttime=omp_get_wtime();
        const int n = 250000;
        int arr[n];
        srand(time(NULL));
        for(int i=0;i<n;i++){
            arr[i]=rand();
        }
        // for (int i = 0; i < n; ++i) {
        //     std::cout << arr[i] << " ";
        // }
        // std::cout<<"\n";
        parallel_prefix_sum(arr, n,nn);
        // for (int i = 0; i < n; ++i) {
        //     std::cout << arr[i] << " ";
        // }
        // std::cout<<"\n";
        // ttime=omp_get_wtime()-ttime;
        printf("Threads: %d Index: %d Time: %f\n",nn,n,omp_get_wtime()-ttime);
    }
    return 0;
}
