 
#include <iostream>
#include<mpi.h>
#include<stdio.h>

int main()
{
    int pid,np;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    int value=100;
    int rvalue;

    MPI_Status  sta;

    if (pid == 0)     
    {     //master process
     
 
        //send ==> pid+1
        //recv ==> np-1         receive from last processer
        MPI_Send(&value, 1, MPI_INT, pid+1, 60, MPI_COMM_WORLD);
        printf("master pid: %d,Send value: %d\n", pid, value);


        MPI_Recv(&value, 1, MPI_INT, np - 1, 60, MPI_COMM_WORLD, &sta);    
        printf("master pid: %d,Receive value: %d, Statis: %d\n", pid, value,np-1);
        

    }
    else if(pid !=0 && pid != np-1)
    {   //

        // recv ==> pid-1
        //send ==> pid+1
        MPI_Recv(&rvalue, 1, MPI_INT, pid-1, 60, MPI_COMM_WORLD, &sta);
        printf(" PID: %d,Receive Value: %d, Status: %d\n",pid, rvalue,pid-1);

        MPI_Send(&value, 1, MPI_INT, pid+1, 50, MPI_COMM_WORLD);
        printf("PID: %d, Send Value: %d\n", pid, value);

    }
    else
    {   // last process

        //recv ==> pid-1
        //send ==> 0
        MPI_Recv(&rvalue, 1, MPI_INT, pid-1, 50, MPI_COMM_WORLD, &sta);
        printf("PID: %d, Receive Value: %d,Status: %d\n", pid, rvalue, pid - 1);

        MPI_Send(&value, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
        printf("PID: %d,Send value: %d", pid, value);



    }
    MPI_Finalize();

    return 0;
   
}
 
