#include <stdio.h>
#include <stdlib.h>

// Initialize a mutex to 1
int mutex = 1;

// Number of full slots as 0a
int full = 0;

// Number of empty slots as size of buffer
int empty = 10;

int x = 0;

void producer() {
    --mutex;
    ++full;
    --empty;
    x++;         //Item Produced
    printf("Producer produces item %d\n",x);
    ++mutex;
}

void consumer() {
    --mutex;
    --full;
    ++empty;
    printf("Consumer consumes item %d\n",x);
    x--;       //Item Removed
    ++mutex;
}

int main() {
    int n, i;
    printf("\n1. Press 1 for Producer"
           "\n2. Press 2 for Consumer"
           "\n3. Press 3 for Exit");

    #pragma omp critical
    for (i = 1; i > 0; i++) {
        printf("\nEnter your choice: ");
        scanf("%d", &n);
        switch (n) {
        case 1:
            // If mutex is 1 and empty is non-zero, then it is possible to produce
            if ((mutex == 1) && (empty != 0)) {
                producer();
            }
            // Otherwise, print buffer is full
            else {
                printf("Buffer is full!");
            }
            break;
        case 2:
            // If mutex is 1 and full is non-zero, then it is possible to consume
            if ((mutex == 1) && (full != 0)) {
                consumer();
            }
            // Otherwise, print Buffer is empty
            else {
                printf("Buffer is empty!");
            }
            break;
        // Exit Condition
        case 3:
            exit(0);
            break;
        }
    }
}
