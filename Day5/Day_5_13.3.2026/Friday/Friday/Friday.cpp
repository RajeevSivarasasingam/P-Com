#include <mpi.h>
#include <stdio.h>


//Run: mpiexec -n 4 Friday.exe

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
		int passingNumberToProcess1 = 34;

		// send numbers to process 1
		MPI_Send(&passingNumberToProcess1, 1, MPI_INT, (pid + 1), 50, MPI_COMM_WORLD);
		printf("Number sent to process %d. %d\n", pid, passingNumberToProcess1);

		// receive number from process 2 
		int receivingNumberFromProcess2;
		MPI_Recv(&receivingNumberFromProcess2, 1, MPI_INT, (np - 1), 52, MPI_COMM_WORLD, &sta);
		printf("\nNumber recieved from process %d. % d\n", pid, receivingNumberFromProcess2);
	}
	else
	{
		if (pid != 0 && pid != (np - 1))
		{
			int receivingNumberFromProcess0;
			// recieve number
			MPI_Recv(&receivingNumberFromProcess0, 1, MPI_INT, (pid - 1), 50, MPI_COMM_WORLD, &sta);
			printf("\nNumber recieved from process %d. %d\n", pid, receivingNumberFromProcess0);

			// send number to process 2
			MPI_Send(&receivingNumberFromProcess0, 1, MPI_INT, (pid + 1), 51, MPI_COMM_WORLD);
			printf("Number sent to process %d. %d\n", pid, receivingNumberFromProcess0);
		}
		else
		{
			int receivingNUmberFromProcees1;
			// receive number from process 1
			MPI_Recv(&receivingNUmberFromProcees1, 1, MPI_INT, (pid - 1), 51, MPI_COMM_WORLD, &sta);
			printf("\nNumber recieved from process %d. %d\n", pid, receivingNUmberFromProcees1);

			// send number to process 0 again 
			MPI_Send(&receivingNUmberFromProcees1, 1, MPI_INT, 0, 52, MPI_COMM_WORLD);
			printf("Number sent to process %d. %d\n", pid, receivingNUmberFromProcees1);
		}
	}
	MPI_Finalize();
	return 0;
}