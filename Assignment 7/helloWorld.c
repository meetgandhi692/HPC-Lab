#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;

    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get the rank (process ID) and size (total number of processes)
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Check if the number of processes is not 10
    if (size != 10) {
        printf("This program is designed to run with 10 processes.\n");
    } else {
        // Print "Hello, World!" along with the rank
        printf("Hello, World! I am process %d of %d.\n", rank, size);
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
