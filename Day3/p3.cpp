#include <mpi.h>
#include <stdio.h>

int main() {
    int  pid;
    
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    if (pid == 0) {
        // Master process: prepare an array to store values from slaves
        int recv_values[np];   // array size = number of processes
        MPI_Status sta;

        printf("Master PID : %d, waiting for values...\n", pid);

        // Receive values from all slaves
        for (int i = 1; i < np; i++) {
            MPI_Recv(&recv_values[i], 1, MPI_INT, i, 50, MPI_COMM_WORLD, &sta);
            printf("Master received value %d from Slave %d\n", recv_values[i], i);
        }

        // Example: print the collected array
        printf("\nAll values collected in array:\n");
        for (int i = 1; i < np; i++) {
            printf("recv_values[%d] = %d\n", i, recv_values[i]);
        }

    }
    else {
        // Slave processes: send a value to master
        int num = pid * 10; // each slave generates a unique value
        MPI_Send(&num, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
        printf("Slave PID : %d, Sent value: %d\n", pid, num);
    }

    MPI_Finalize();
    return 0;
}
