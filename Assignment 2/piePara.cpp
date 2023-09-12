#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

#define n 8
using namespace std;

int main() {
    int totalPoints = 100000000; // Total number of points to generate
    int pointsInsideCircle = 0;

    srand(time(0)); // Seed for random number generation
    double stime=omp_get_wtime();
    #pragma omp parallel for num_threads(n) reduction(+:pointsInsideCircle)
    for (int i = 0; i < totalPoints; ++i) {
        double x = (double)rand() / RAND_MAX; // Random number between 0 and 1
        double y = (double)rand() / RAND_MAX; // Random number between 0 and 1

        if (x * x + y * y <= 1) {
            pointsInsideCircle++;
        }
    }
    double etime=omp_get_wtime();
    double piApproximation = 4.0 * pointsInsideCircle / totalPoints;
    
    printf("Pi Approximation: %f\nTotal points: %d\nNumber of threads: %d\nTotal time: %f\n",piApproximation,totalPoints,n,etime-stime);
    return 0;
}