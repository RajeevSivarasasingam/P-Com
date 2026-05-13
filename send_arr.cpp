
#include <iostream>
#include<mpi.h>
#include<stdio.h>

//Run: mpiexec -n 4 P4.exe

int main()
{
    int pid, np;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    MPI_Status  sta;

    int value;
    int sum = 0;

    // np=2

    if (pid == 0)
    {     //master process     
        int arr[] = { 1,2,3,4,5 };

        //p0 send value 
        for (int i = 2; i < 5; i++)
        {
            MPI_Send(&arr[i], 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        }
        printf("master(p0)  send value");


    }
    if (pid == 1)
    {
        int Recv_arr[4];
        for (int i = 0; i <= 3; i++)
        {
            MPI_Recv(&Recv_arr[i], 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &sta);

        }
        printf("p1 recive value");

    }
    MPI_Finalize();

    return 0;

}
