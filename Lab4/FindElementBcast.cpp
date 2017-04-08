#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define SIZE 100
#define KEY 95


int main(int argc, char *argv[])
{
	int rank, size, segmentSize, startPos, endPos, found=-1, finalFound = -1;
	int arr[SIZE];

	srand(time(NULL));	

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {
		for (int i = 0; i < SIZE; i++) {
			arr[i] = rand() % 100;
		}
	}

	segmentSize = SIZE / size;
	if (SIZE % size != 0)
		++segmentSize;

	MPI_Bcast(arr, SIZE, MPI_INT, 0, MPI_COMM_WORLD);

	startPos = rank * segmentSize;
	endPos = startPos + segmentSize - 1;
	//printf("Process %d: start: %d; end: %d; elements: ", rank, startPos, endPos);
	for (int i = startPos; i <= endPos && i < SIZE; i++) {
		//printf("%d ", arr[i]);
		if (arr[i] == KEY) {
			found = i;
			printf(" \n%d %d", i, arr[i]);
		}
	}

	MPI_Reduce(&found, &finalFound, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);	
	if(rank == 0)
		if (finalFound == -1)
			printf("\nThe number wasn`t found\n");
		else printf("\nNumber found on position %d", finalFound);

	MPI_Finalize();

}

