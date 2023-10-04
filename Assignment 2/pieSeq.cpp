#include <iostream>
#include <cstdlib>
#include<ctime>
#include<omp.h>
using namespace std;

int main() {
    int totalPoints = 100000000;
    int pointsInsideCircle = 0;
 
    srand(time(0)); 

    double time=omp_get_wtime();
    for(int i = 0; i < totalPoints; ++i) {
        double x = (double)rand() / RAND_MAX; // Random number between 0 and 1
        double y = (double)rand() / RAND_MAX; // Random number between 0 and 1

        if (x * x + y * y <= 1) {
            pointsInsideCircle++;
        }
    }
    time=omp_get_wtime()-time;
    double piApproximation = 4.0 * pointsInsideCircle / totalPoints;
    printf("Pi Approximation: %f\nTotal points: %n\nTotal time: %f\n",piApproximation,totalPoints,time);
    return 0;
}
