#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int rank;
    int size;
    int x0 = 1;
    int sum;
    int m = 2;
    int total_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int left = (rank - 1 + size) % size;
    int right = (rank + 1) % size;
    int x = x0;

    for(int i=0; i<m; i++) {
        MPI_Send(&x, 1, MPI_INT, right, 0, MPI_COMM_WORLD);
        MPI_Recv(&sum, 1, MPI_INT, left, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        x += sum;
    }
    printf("Rango %d: valor final = %d\n", rank, x);

    MPI_Reduce(&x, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0) {
        printf("Suma total de los valores finales: %d\n", total_sum);
    }

    MPI_Finalize();
    return 0;
}
