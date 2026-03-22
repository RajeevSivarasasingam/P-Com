#include <mpi.h> 
#include <stdio.h> 
int main()
{
	int np;
	int pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	MPI_Status sta;

	if (pid == 0)
	{
	 
		int arr[4] = {2, 4, 6, 8};

		MPI_Send(&arr, 4, MPI_INT, 1, 50, MPI_COMM_WORLD);

		printf("PID : %d ,send value: \n ", pid, arr);

		for (int i = 0; i < 4; i++)
		{
			printf("%d ", arr[i]);
		}
	}
	else if (pid == 1)
	{
		int recv_arr[4];
		MPI_Recv(&recv_arr, 4, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);

		printf("PID : %d ,Received value:\n ", pid, recv_arr);
		for (int i = 0; i < 4; i++)
		{
			printf("%d ", recv_arr[i]);
		}


	}
	 
	MPI_Finalize();
	return 0;
}


// output
// PID : 0 ,send value:
 // 2 4 6 8
// PID : 1 ,Received value:
 // 2 4 6 8