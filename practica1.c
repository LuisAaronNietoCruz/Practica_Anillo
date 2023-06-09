#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
  int numproc;
  int miproc;
  int x0 = 0;
  int m = 2;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &miproc);
  MPI_Comm_size(MPI_COMM_WORLD, &numproc);

  if (miproc == 0) {
    MPI_Send(&x0, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
  }

  for (int cycle = 0; cycle < m; cycle++) {
    int prev = miproc - 1;
    if (miproc == 0) {
      prev = numproc - 1;
    }
    MPI_Recv(&x0, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &status);

    int i = prev + 1 + numproc * cycle;
    x0 += i;
    int next = miproc + 1;
    if (miproc == numproc - 1) {
      next = 0;
    }

    MPI_Send(&x0, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
  }

  if (miproc == 0) {
    printf("Suma total de los valores finales: %d\n", x0);
  }

//printf("Rango: %d/n", "Numero de procesos: %d/n", miproc, numproc);

  MPI_Finalize();
  return 0;
}
