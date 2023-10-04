#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

int main() {
    int n=1;
    int totalPoints = 100000000; // Total number of points to generate
    for(n=1;n<101;n++){
        srand(time(0)); // Seed for random number generation
        double stime=omp_get_wtime();
        
        int pointsInsideCircle = 0;

        #pragma omp parallel for num_threads(n) reduction(+:pointsInsideCircle)
        for (int i = 0; i < totalPoints; ++i) {
            double x = (double)rand() / RAND_MAX; // Random number between 0 and 1
            double y = (double)rand() / RAND_MAX; // Random number between 0 and 1

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