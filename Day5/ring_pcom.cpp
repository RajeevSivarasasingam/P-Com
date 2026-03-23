 
#include <iostream>
#include<mpi.h>
#include<stdio.h>

int main()
{
    int pid,np;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
        
    MPI_Status  sta;    

    int value;

    int next = (pid + 1) % np;
    int prev = (pid - 1 + np) % np;

    if (pid == 0)     
    {     //master process     
        value = 5;
        MPI_Send(&value, 1, MPI_INT, next, 60, MPI_COMM_WORLD);
        printf("master pid: %d,Send value: %d to %d \n", pid, value,next);

        MPI_Recv(&value, 1, MPI_INT, prev, 60, MPI_COMM_WORLD, &sta);    
        printf("master pid: %d,Receive value: %d form %d \n", pid, value, prev);
        
    }
    else
    {   
        MPI_Recv(&value, 1, MPI_INT, prev, 60, MPI_COMM_WORLD, &sta);
        printf("PID: %d, Receive Value: %d from %d\n", pid, value, prev);

        MPI_Send(&value, 1, MPI_INT, next, 60, MPI_COMM_WORLD);
        printf("PID: %d,Send value: %d to %d", pid, value,next);

    }
    MPI_Finalize();

    return 0;
   
}
 
 //Output: 
 // master pid: 0 send value: 5 to 1
// pid: 1 received value: 5 from 0
// pid: 1 send value: 5 to 2
// pid: 2 received value: 5 from 1
// pid: 2 send value: 5 to 3
// pid: 3 received value: 5 from 2
// pid: 3 send value: 5 to 0
// master pid: 0 received value: 5 from 3