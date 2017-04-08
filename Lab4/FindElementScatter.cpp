#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define SIZE 100
#define KEY 95


int main(int argc, char *argv[])
{
	int rank, size, segmentSize, index, found[SIZE], finalFound[SIZE + 10];
	int arr[SIZE], segment[SIZE];

	srand(time(NULL));

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	segmentSize = SIZE / size;
	if (SIZE % size != 0) {
		++segmentSize;
	}

	if (rank == 0) {
		printf("Array elements are:\n");
		for (int i = 0; i < SIZE; i++) {
			arr[i] = rand() % 100;
			printf("%d, ", arr[i]);
			finalFound[i] = 0;
		}
		arr[35] = 95;
		arr[98] = 95;
	}

	MPI_Scatter(arr, segmentSize, MPI_INT, segment, segmentSize, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < segmentSize; i++)
		found[i] = 0;

	index = 0;
	//printf("\nProcess %d:\n", rank);
	for (int i = 0; i < segmentSize; i++) {
		if (segment[i] == KEY) {
			found[index++] = i + rank*segmentSize;
		}
	}

	MPI_Gather(found, segmentSize, MPI_INT, finalFound, segmentSize, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0) {
			int poz = 0;

			while (poz < SIZE + 10) {
				if (finalFound[poz] > 0) {
					printf("\nNumber found on the following positions: ");
					break;
				}
				poz++;
			}				
			while (poz < SIZE + 10) {
				if (finalFound[poz] > 0) 
					printf("%d ", finalFound[poz]);
				poz++;
			}

	}

	MPI_Finalize();
	return 0;
}
