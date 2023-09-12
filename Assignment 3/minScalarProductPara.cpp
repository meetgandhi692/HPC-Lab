#include<bits/stdc++.h>
#include <omp.h>
#define n 8
int sort(int nums[]) {
    int i, j;
    for (i = 0; i < n; i++) {
        int turn = i & 2;
    #pragma omp parallel for private(j) shared(nums) num_threads(n)
        for (j = turn; j < n - 1; j += 2)
            if (nums[j] > nums[j + 1]) {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
    }
}
int sort_des(int nums[]) {
    int i, j;
    for (i = 0; i < n; ++i) {
        int turn = i & 2;
    #pragma omp parallel for private(j) shared(nums) num_threads(n)
        for (j = turn; j < n - 1; j += 2) {
            if (nums[j] < nums[j + 1]) {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }
}

int main() {
    int N=100000;
    int nums1[N], nums2[N];
    srand((unsigned)time(NULL));
    for (int i = 0; i < N; i++) {
        nums1[i] = rand()%10;
        nums2[i] = rand()%10;
    }
    
    double t = omp_get_wtime();
    
    sort(nums1);
    sort_des(nums2);
    
    int sum = 0;
    #pragma omp parallel for num_threads(n) reduction(+:sum)
    for (int i = 0; i < N; i++) {
        sum += (nums1[i] * nums2[i]);
    }

    t = omp_get_wtime() - t;
    printf("Min Scalar Product: %d\n", sum);
    printf("Number of indexes: %d\nNumber of threads: %d\nTime taken: %f\n", N,n,t);
    return 0;
}