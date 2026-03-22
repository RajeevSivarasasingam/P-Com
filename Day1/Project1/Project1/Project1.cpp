#include <mpi.h> 
#include <stdio.h> 
int main()
{
	int np;
	int pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	printf("\n Hello world . . . \n My pid= %d \n No_of_process= %d", pid, np);
	MPI_Finalize();
	return 0;
}