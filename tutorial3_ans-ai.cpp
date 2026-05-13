#include <mpi.h>
#include <iostream>
using namespace std;

// Function to check if element exists in A
bool exists(int A[], int size, int key) {
    for (int i = 0; i < size; i++) {
        if (A[i] == key)
            return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N = 32;
    int A[N];
    int B[N];
    int local_B[8];

    if (rank == 0) {
        // Initialize sequences
        int tempA[N] = {45,41,92,79,11,83,97,91,98,67,53,34,68,72,76,12,
                        78,59,64,6,89,62,26,23,17,35,36,18,25,55,43,56};

        int tempB[N] = {5,18,96,63,23,10,42,34,58,84,35,61,51,41,1,13,
                        45,22,53,44,56,96,62,71,67,72,78,46,83,91,97,98};

        // Copy data
        for (int i = 0; i < N; i++) {
            A[i] = tempA[i];
            B[i] = tempB[i];
        }

        // (a) Send A to all other processes
        for (int i = 1; i < size; i++) {
            MPI_Send(A, N, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        // (b) Distribute B manually
        for (int i = 1; i < size; i++) {
            MPI_Send(&B[i * 8], 8, MPI_INT, i, 1, MPI_COMM_WORLD);
        }

        // P0 keeps first 8 elements
        for (int i = 0; i < 8; i++) {
            local_B[i] = B[i];
        }
    }
    else {
        // Receive A from master
        MPI_Recv(A, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Receive part of B
        MPI_Recv(local_B, 8, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // (c) Print received values
    cout << "Process " << rank << " received: ";
    for (int i = 0; i < 8; i++) {
        cout << local_B[i] << " ";
    }
    cout << endl;

    // (d) Compute local intersection
    int local_count = 0;
    for (int i = 0; i < 8; i++) {
        if (exists(A, N, local_B[i])) {
            local_count++;
        }
    }

    cout << "Process " << rank << " local intersection count: "
         << local_count << endl;

    // (e) Send local counts to master
    if (rank == 0) {
        int global_count = local_count;

        for (int i = 1; i < size; i++) {
            int temp;
            MPI_Recv(&temp, 1, MPI_INT, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            global_count += temp;
        }

        // Compute Dice coefficient
        double dice = (2.0 * global_count) / (N + N);
        double similarity = dice * 100;

        cout << "\nTotal Intersection = " << global_count << endl;
        cout << "Dice Coefficient = " << dice << endl;
        cout << "Similarity = " << similarity << "%" << endl;
    }
    else {
        MPI_Send(&local_count, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}