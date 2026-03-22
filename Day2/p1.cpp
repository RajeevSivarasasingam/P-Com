
//  for run first build (ctr+sh+B) then go to debug file run in cmd
// mpiexec -n 4 Project1.exe

#include <mpi.h> 
#include <stdio.h> 
int main()
{
	int np;
	int pid;
	MPI_Init(NULL, NULL);			//starts the MPI environment
	MPI_Comm_size(MPI_COMM_WORLD, &np);	// gets the number of processes.
	MPI_Comm_rank(MPI_COMM_WORLD, &pid); //gets the rank (ID) of the current process.


	if (pid == 0)
	{
		printf("\n Hello world . . . \n My pid= %d \n No_of_process= %d", pid, np);

	}
	else if (pid == 1)
	{
		printf("\n Hi I am  pid 1. . . \n My pid= %d \n No_of_process= %d", pid, np);

	}
	else if (pid == 2)
	{
		printf("\n Hi I am  pid 2. . . \n My pid= %d \n No_of_process= %d", pid, np);

	}
	else
	{
		printf("\n  Hi I am pid 3. . . \n My pid= %d \n No_of_process= %d", pid, np);

	}
	MPI_Finalize();
	return 0;
}


//output
//C:\Users\User\Desktop\2021ict102\P-com\Day1\Project1\x64\Debug>mpiexec -n 4 Project1.exe
// PID : 0 ,send value: 5

// PID : 1 ,Received value: 5