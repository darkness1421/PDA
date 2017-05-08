#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"



__global__ void RoyFloyd(int* matrix, int k, int N) {

	int i = blockIdx.x;
	int j = threadIdx.x;

	if((matrix[i*N + k] + matrix[k*N + j]) < matrix[i*N + j])
		matrix[i*N + j] = matrix[i*N + k] + matrix[k*N + j];	
}


int main(int argc, char **argv)
{	
	int thread_per_block = 512, i, j;
	int N = 100;
	int* cuda_matrix;
	int size = sizeof(int)* N * N;	
	int *matrix = (int*)malloc(sizeof(int)*N*N);
	int *result = (int*)malloc(sizeof(int)*N*N);
	int num_block = ceil((float)(N*N / (thread_per_block)));
	srand(time(NULL));

	for (int i = 0; i < N*N; i++)
		matrix[i] = rand() % 50;
	for (int i = 0; i < N; i++)
		matrix[i*N + i] = 0;
	
	memcpy(result, matrix, sizeof(int)*N*N);

	cudaMalloc((void**)&cuda_matrix, size);
	cudaMemcpy(cuda_matrix, matrix, size, cudaMemcpyHostToDevice);
	
	for (int k = 0; k < N; ++k) {
		RoyFloyd << <num_block, (thread_per_block) >> >(cuda_matrix, k, N);
	}

	cudaMemcpy(matrix, cuda_matrix, size, cudaMemcpyDeviceToHost);
	cudaFree(cuda_matrix);

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
			printf("dist[%d][%d] = %d \n", i, j, result[i*N + j]);
	}

}