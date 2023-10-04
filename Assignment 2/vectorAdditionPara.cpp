#include <omp.h>
#include <bits/stdc++.h>

int main() {
    int n=1;
    int N = 20000;
    int A[N];
    int B[N];
    
    for(n=1;n<51;n++){
        double stime = omp_get_wtime();
        int C [N] = {0};
        srand(time(0));
        for (int i = 0; i < N; i++){
            A[i] = rand()%10;
            B[i] = rand()%10;
        }

        #pragma omp parallel for reduction(+:C) num_threads(n)
        for (int i = 0; i < N; i++) {
            C[i] = A[i] + B[i];
            // printf("Index: %d Thread: %d\n", i, omp_get_thread_num());
        }

        // for (int i = 0; i < N; i++) {
        //     printf("%d ", C[i]);
        // }

        double etime = omp_get_wtime();
        double time = etime - stime;
        printf("Threads: %d Time Taken: %f\n",n,time);
    }
    // printf("\nNumber of total threads: %d\nNumber of indexes: %d\nTime taken is %f\n",n,N,time);

    return 0;
}
