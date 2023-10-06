#include<bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    int n=1;
    int N=10000;
    // for(n=2;n<=100;n++){
        double t = omp_get_wtime();

        int nums1[N], nums2[N];
        srand(time(NULL));
        for (int i = 0; i < N; i++) {
            nums1[i] = rand()%10;
            nums2[i] = rand()%10;
        }
        sort(nums1,nums1+N);
        sort(nums2,nums2+N,greater<int>());

        int sum = 0;
        // #pragma omp parallel for num_threads(n) reduction(+:sum)
        for (int i = 0; i < N; i++) {
            sum += (nums1[i] * nums2[i]);
        }

        t = omp_get_wtime() - t;
        printf("Min Product: %d Indexes: %d Threads: %d Time: %f\n", sum,N,n,t);
    // }
    return 0;
}