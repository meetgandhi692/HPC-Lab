#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

int main(){
    double time=omp_get_wtime();
    const int N=100000;
    float a[N];
    float sum[N];
    // srand(time(NULL));    
    for(int i=0;i<N;i++){
        a[i]=rand();
        if(i==0)
            sum[i]=a[i];
        if(i>0){
            sum[i]+=sum[i-1];
        }
a    time=omp_get_wtime()-time;
    printf("Time: %f\n",time);
}