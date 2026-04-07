 
//mpiexec -n 4 sample.exe
// Q: master send a arr to 1, 1 find sum and send 0

#include <mpi.h>
#include <stdio.h>

int main()
{
	int np;
	int pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np); //num of process
	MPI_Comm_rank(MPI_COMM_WORLD, &pid); 

	MPI_Status sta;

	if (pid == 0)
	{
		int arr[5] = { 10,20,30,40,50 };
		MPI_Send(&arr, 5, MPI_INT, 1, 80, MPI_COMM_WORLD);
		printf("my processer id %d, I'm the sender ", pid);

		int recv;
		MPI_Recv(&recv, 1, MPI_INT, 1, 55, MPI_COMM_WORLD, &sta);
		printf("Sum of the numbers I sent is %d. \n", recv);
	}
	if (pid == 1)
	{
		int recv_arr[5];
		int sum = 0;
		MPI_Recv(&recv_arr, 5, MPI_INT, 0, 80, MPI_COMM_WORLD,&sta);
		printf("My processor id is %d and I'm the receiver. \n", pid);
		for (int i = 0; i < 5; i++)
		{
			sum = sum + recv_arr[i];
		}
		MPI_Send(&sum, 1, MPI_INT, 0, 55, MPI_COMM_WORLD);

	}

	MPI_Finalize();
	return 0;
}

//C:\Users\sivar\Desktop\PCom\prc\sample\sample\x64\Debug>mpiexec -n 4 sample.exe
//my processer id 0, I'm the sender Sum of the numbers I sent is 150.
//My processor id is 1 and I'm the receiver.
