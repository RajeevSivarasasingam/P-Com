 //mpiexec -n 8 sample.exe

#include <mpi.h>
#include <stdio.h>

#define N 8	// size of matrix and vector
int main()
{
	int np;
	int pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;
	
	int X[N];
	int row[N];		//store row num
	int result=0;	//each dot product results
	int Y[N];		// final array

	if (pid == 0)
	{
		int A[N][N] = {
			{2,4,6,8,1,3,5,7},
			{1,3,5,7,2,4,6,8},
			{9,11,13,15,2,4,6,8},
			{10,12,14,16,1,3,5,7},
			{5,7,9,11,3,6,8,2},
			{6,8,10,12,4,7,9,3},
			{13,15,17,19,5,8,10,4},
			{14,16,18,20,6,9,11,5}
		};
		int X[N] = { 1,2,3,4,5,6,7,8 };

		//send X to all process
		for (int i = 1; i < 8; i++) // don't send 0 so start 1
		{
			MPI_Send(X, 8, MPI_INT, i, 10, MPI_COMM_WORLD);  //&X[0] = X
		}
		//send row of A (8 elements) all process
		for (int i = 1; i < 8; i++)	// start i=1
		{			
			MPI_Send(&A[i][0], 8, MPI_INT, i, 20, MPI_COMM_WORLD);
			//MPI_Send(A[i], 8, MPI_INT, i, 20, MPI_COMM_WORLD); // both are same &A[i][0]=A[i] (index address)			
		}

		//master dot product row0 * X
		for (int i = 0; i < 8; i++)
		{
			result += A[0][i] * X[i];
		}
		Y[0] = result;

		//recv results
		for (int i = 1; i < 8; i++) // i=0, y=0 already added so start 1
		{
			MPI_Recv(&result, 1, MPI_INT, i, 30, MPI_COMM_WORLD, &sta);
			Y[i] = result;
		}
		//print final result
		printf("\n Final result vector: ");
		for (int i = 0; i < 8; i++)
		{
			printf("%d ", Y[i]);
		}
	}
	else //if(pid!=0)
	{
		//recv from p0
		MPI_Recv(X, 8, MPI_INT, 0, 10, MPI_COMM_WORLD,&sta);
		MPI_Recv(row, 8, MPI_INT, 0, 20, MPI_COMM_WORLD,&sta);

		//print recv row
		printf("process %d received row: ", pid);
		for (int i = 0; i < 8; i++)
		{
			printf("%d ", row[i]);
		}
		// 
		for (int i = 0; i < 8; i++)
		{
			result += row[i] * X[i];
		}
		printf("\n dot product: %d",result);

		//send result
		MPI_Send(&result, 1, MPI_INT, 0, 30, MPI_COMM_WORLD);
	}
	
	MPI_Finalize();
}
//
//output:
//process 5 received row : 6 8 10 12 4 7 9 3
//dot product : 249
//process 4 received row : 5 7 9 11 3 6 8 2
//dot product : 213
//process 7 received row : 14 16 18 20 6 9 11 5
//dot product : 381
//process 3 received row : 10 12 14 16 1 3 5 7
//dot product : 254
//process 2 received row : 9 11 13 15 2 4 6 8
//dot product : 270
//process 6 received row : 13 15 17 19 5 8 10 4
//dot product : 345
//process 1 received row : 1 3 5 7 2 4 6 8
//dot product : 190
