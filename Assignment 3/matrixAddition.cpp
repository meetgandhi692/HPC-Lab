#include<bits/stdc++.h>
#include<omp.h>

const int N=300;
using namespace std;

void display(int a[N][N]){
    for(int i=0;i<1;i++){
        for(int j=0;j<10;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

int main(){
    int n=1;
    for(n=2;n<51;n++){
        double stime=omp_get_wtime();
        int a[N][N],b[N][N],c[N][N];

        srand((unsigned)time(NULL));
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                a[i][j]=rand()%10;
                b[i][j]=rand()%10;
                c[i][j]=0;
            }
        }
        // display(a);
        // display(b);
        // display(c);
        #pragma omp parallel for collapse(2) num_threads(n)
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                c[i][j]=a[i][j]+b[i][j];
            }
        }
        double etime=omp_get_wtime();
        // display(c);

        printf("Indexes: %d Threads: %d Time: %f\n",N,n,etime-stime);
    }
    return 0;
}