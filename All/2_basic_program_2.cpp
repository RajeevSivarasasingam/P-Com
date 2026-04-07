 // mpiexec -n 4 sample.exe
// Q: master have integer array send to 1 , 1 receive the array

#include <mpi.h>
#include <stdio.h>
int main()
{
	int np;
	int pid;
	MPI_Init(NULL, NULL); // initialize the mpi environment
	MPI_Comm_size(MPI_COMM_WORLD, &np); //get total num of process
	MPI_Comm_rank(MPI_COMM_WORLD, &pid); //get process id
	MPI_Status sta;

	if (pid == 0)
	{
		int send_num[5] = { 2,4,6,8,10 };
		MPI_Send(&send_num, 5, MPI_INT, 1, 50, MPI_COMM_WORLD);//()
		printf("My processer id is %d, I'm the  sender \n ",pid);

	}
	if (pid == 1)
	{
		int recv_num[5];
		MPI_Recv(&recv_num, 5, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		printf("My processer id is %d, I'm the receiver \n",pid);
		printf("Received msg : ");
			for (int i=0;i < 5; i++)
			{
				printf("%d \t ",recv_num[i]);
			}
	}
	//Finalize the environment
	MPI_Finalize();
}
//Output
////C:\Users\sivar\Desktop\PCom\prc\sample\sample\x64\Debug>mpiexec -n 4 sample.exe
//My processer id is 0, I'm the  sender
//
//My processer id is 1, I'm the receiver
//Received msg : 2         4       6       8       10
