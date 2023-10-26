#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

int main(){
    double ttime=omp_get_wtime();
    const int N=250000;
    float a[N];
    float sum[N];
    srand(time(NULL));    
    for(int i=0;i<N;i++){
        a[i]=rand();
        sum[i]=0;
    }
    sum[0]=a[0];
    for(int i=1;i<N;i++){
        sum[i]=a[i]+sum[i-1];
    }
    ttime=omp_get_wtime()-ttime;
    // for(int i=0;i<N;i++){
    //     printf("%.0f %.0f\n",a[i],sum[i]);
    // }
    printf("Time: %f\n",ttime);
}