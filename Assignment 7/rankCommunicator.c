#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (size != 5) {
        printf("This program must be run with exactly 5 processes\n");
        MPI_Finalize();
        return 1;
    }
    
    printf("Hello, I am process %d of 5\n", rank);
    
    MPI_Finalize();
    return 0;
}
