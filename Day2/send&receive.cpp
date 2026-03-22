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
		int num = 5;
	 

		MPI_Send(&num, 1, MPI_INT, 1, 50, MPI_COMM_WORLD);

		printf("PID : %d ,send value: %d \n ", pid, num);

	}
	else if (pid == 1)
	{
		int recv_num;
		MPI_Recv(&recv_num, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);

		printf("PID : %d ,Received value: %d \n ", pid, recv_num);


	}
	 
	MPI_Finalize();
	return 0;
}