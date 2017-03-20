#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LIMIT     1000     

int isPrime(int number) {

	if (number < 2) return 0;
	if (number == 2) return 1;
	if (number % 2 == 0) return 0;
	int squareroot = sqrt(number);
	for (int i = 3; i <= squareroot; i += 2) {
		if (number % i == 0) return 0;
	}
	return 1;
}

int main(int argc, char *argv[])
{
	int	ntasks, rank, start, step;               

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

	start = (rank * 2) + 1;       
	step = ntasks * 2;          

	if (rank == 0) {
		printf("2\n");
	}

	for (int i = start; i <= LIMIT; i += step) {
		if (isPrime(i)) {
			printf("%d\n", i);
		}
	}

	MPI_Finalize();
}