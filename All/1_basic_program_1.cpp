#include <mpi.h>
#include <stdio.h>
int main()
{
	int np;
	int pid;
	MPI_Init(NULL,NULL) ;
	MPI_Comm_size(MPI_COMM_WORLD,&np);
	MPI_Comm_rank(MPI_COMM_WORLD,&pid);
	MPI_Status sta;
	if(pid==0)
	{
		int Send_msg=10;
		MPI_Send(&Send_msg,1,MPI_INT,1,50,MPI_COMM_WORLD);
		printf("My processor id is %d and I'm the sender. The msg is %d \n",pid,Send_msg);
	}
	if(pid==1)
	{
		int Recv_msg;
		MPI_Recv(&Recv_msg,1,MPI_INT,0,50,MPI_COMM_WORLD,&sta);
		printf("My processor id is %d and I'm the receiver. The msg is %d \n",pid,Recv_msg);
	}
	MPI_Finalize();
	return 0;
}
