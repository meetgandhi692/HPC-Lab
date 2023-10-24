#include <omp.h>
#include<bits/stdc++.h>

using namespace std;
const int N = 400;

int main() {
    int n=1;
    for(int n=2;n<51;n++){
        double ptime = omp_get_wtime();
        int matrix[N][N];
        int vector[N];
        int result[N] = {0};
        srand(time(NULL));
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                matrix[i][j] = rand()%10;
            }
            vector[i] = rand()%10;
        }

        #pragma omp parallel for num_threads(n)
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                result[i] += matrix[i][j] * vector[j];
            }
        }

        ptime = omp_get_wtime()-ptime;
        // for(int i = 0; i < N; ++i) {
        //     printf("%d ", result[i]);
        // }
        printf("Threads: %d Index: %d Time: %f\n", n,N,ptime);
    }

    return 0;
}