
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int pid, np;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int value, sum;
    MPI_Status status;

    if(pid == 0)
    {
        int arr[6] = {1,2,3,4,5,6};

        // send values to P1..P5
        for(int i=1;i<6;i++)
            MPI_Send(&arr[i],1,MPI_INT,i,0,MPI_COMM_WORLD);	

        int sum1, sum3;

        MPI_Recv(&sum1,1,MPI_INT,1,0,MPI_COMM_WORLD,&status);
        MPI_Recv(&sum3,1,MPI_INT,3,0,MPI_COMM_WORLD,&status);

        int total = arr[0] + sum1 + sum3;

        printf("Final Total Sum = %d\n", total);
    }

    else
    {
        MPI_Recv(&value,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);

        if(pid==2)
        {
            MPI_Send(&value,1,MPI_INT,1,0,MPI_COMM_WORLD);
        }

        if(pid==1)
        {
            int v2;
            MPI_Recv(&v2,1,MPI_INT,2,0,MPI_COMM_WORLD,&status);
            sum = value + v2;
            MPI_Send(&sum,1,MPI_INT,0,0,MPI_COMM_WORLD);
        }

        if(pid==5)
        {
            MPI_Send(&value,1,MPI_INT,4,0,MPI_COMM_WORLD);
        }

        if(pid==4)
        {
            int v5;
            MPI_Recv(&v5,1,MPI_INT,5,0,MPI_COMM_WORLD,&status);
            sum = value + v5;
            MPI_Send(&sum,1,MPI_INT,3,0,MPI_COMM_WORLD);
        }

        if(pid==3)
        {
            int v4;
            MPI_Recv(&v4,1,MPI_INT,4,0,MPI_COMM_WORLD,&status);
            sum = value + v4;
            MPI_Send(&sum,1,MPI_INT,0,0,MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}