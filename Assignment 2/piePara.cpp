#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

int main() {
    int n=1;
    for(n=2;n<101;n++){
        double stime=omp_get_wtime();
        int totalPoints = 100000000; // Total number of points to generate
        srand(time(0));
        
        int pointsInsideCircle = 0;

        #pragma omp parallel for num_threads(n) reduction(+:pointsInsideCircle)
        for (int i = 0; i < totalPoints; ++i) {
            double x = (double)rand() / RAND_MAX; 
            double y = (double)rand() / RAND_MAX;

            if (x * x + y * y <= 1) {
                pointsInsideCircle++;
            }
        }
        double piApproximation = 4.0 * pointsInsideCircle / totalPoints;
        
        double etime=omp_get_wtime();
        // printf("Pi Approximation: %f\nTotal points: %d\nNumber of threads: %d\nTotal time: %f\n",piApproximation,totalPoints,n,etime-stime);
        printf("%f Threads: %d Time: %f\n",piApproximation,n,etime-stime);
    }
    return 0;
}