#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int* generate_rand_nums(int rank){
	int i;
	int arr[SIZE];

	srand(time(NULL) + rank);

	for (i = 0; i < SIZE; i++){
		arr[i] = rand() % 1000;
		printf("%d, ", arr[i]);
	}

	return arr;
}

int compute_sum(int* arr){
	int i, s = 0;

	for (i = 0; i < SIZE; i++)
		s += arr[i];

	return s;
}
int main(int argc, char *argv[])
{
	int rank, size;
	int* procArr;
	double start_time, end_time;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank == 0){
		printf("Root process\n\n");
	}
		
	if(rank != 0) {
		start_time = MPI_Wtime();
		printf("\nStart time for process %d: %f \n", rank, start_time);
		printf("\nProcess %d elements: ", rank);
		procArr = generate_rand_nums(rank);
		int sum = compute_sum(procArr);
		printf("\nSum is: %d ", sum);
		end_time = MPI_Wtime();
		printf("\nFinish time for process %d: %f \n", rank, end_time);	
		printf("\nTime elapsed for process %d: %f\n", rank, (end_time - start_time));
	}
	
	MPI_Finalize();
}

