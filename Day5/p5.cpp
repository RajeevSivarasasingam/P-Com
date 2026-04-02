 
#include <iostream>
#include<mpi.h>
#include<stdio.h>

//Run: mpiexec -n 4 P4.exe

int main()
{
    int pid,np;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
        
    MPI_Status  sta;    

    int value;     
    int sum = 0;

    if (pid == 0)     
    {     //master process     
        int arr[6] = { 1,2,3,4,5,6 };

        //p0 send value to p1..p5
        for (int i = 1; i < 6; i++)
        {
            MPI_Send(&arr[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

                
        
    }
    else
    {   
        MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &sta);

        if (pid == 2) //  p2 send value to p1  (eg:value=a2)
        {
            MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        }
        
        if (pid == 1) //  p1 get value from p2 (a2) and add value( sum1=a1+a2)
        {
            int v2;
            MPI_Recv(&v2, 1, MPI_INT, 2, 0, MPI_COMM_WORLD,&sta);
            sum = value + v2;

        } 
        
        if (pid == 5) //   p5 send value to p4 (value a5)
        {
            MPI_Send(&value, 1, MPI_INT, 4, 0, MPI_COMM_WORLD);

        } 
        if (pid == 4) //   p4 get value from p5 (value a5) and do ( sum4= a4+a5 )
        {              //after send sum4 to p3 
            int v5;
            MPI_Recv(&v5, 1, MPI_INT, 5, 0, MPI_COMM_WORLD, &sta);
            sum = value + v5;

            //send sum4 to p3
            MPI_Send(&sum, 1, MPI_INT, 3,0, MPI_COMM_WORLD);
        } 
        
        if (pid == 3) //p3 get value from p4  do sum3 = a3 + sum4 after send sum3 to p0
        {              
            int v4;
            MPI_Recv(&v4, 1, MPI_INT, 4, 0, MPI_COMM_WORLD, &sta);
            sum = value + v4;

            //send sum3 to p0
            MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

        }


    }
    MPI_Finalize();

    return 0;
   
}
 
