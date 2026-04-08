//mpiexec -n 4 sample.exe
// Dice coefficient (T3 Q1)
#include <mpi.h>
#include <stdio.h>
int main()
{
	int np;
	int pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;

	int	recv_A[32];
	int recv_B[8];
	int local_intersection =0;
	int total_intersection =0;
	
	if (pid == 0)
	{
		int tempA[32] = { 45,41,92,79,11,83,97,91,98,67,53,34,68,72,76,12,
						 78,59,64,6,89,62,26,23,17,35,36,18,25,55,43,56 };
		int tempB[32] = { 5,18,96,63,23,10,42,34,58,84,35,61,51,41,1,13,
						 45,22,53,44,56,96,62,71,67,72,78,46,83,91,97,98 };

		printf("process 0  \n");
		//send sequence A  (full A for all workers)
		for (int i = 1; i <= 3; i++)
		{
			MPI_Send(&tempA[0], 32, MPI_INT, i, 50, MPI_COMM_WORLD);
			//&temp[0] - address of the first element, start from this send 32 elements
		}
		//send sequence B (split into 8)
		for (int i = 1; i <= 3; i++)
		{
			MPI_Send(&tempB[i * 8], 8, MPI_INT, i, 50, MPI_COMM_WORLD);
			// i=1, start from index 8 , 9th element, send 8 element
			//p0 (0-7), p1 (8-15),p3 (16-23), p4 (24-31)

		}

		
		//print B part fist 8 elements
		/*printf("elments of B (8): \n");
		for (int i = 0; i < 8; i++)
		{
			printf("%d \t", tempB[i]);
		}*/

		//copy & print A
		printf("A: \t");
		for (int i = 0; i < 32; i++)
		{
			recv_A[i] = tempA[i];
			printf("%d \t", recv_A[i]);
		}
		//copy & print B
		printf("\n B: \t");
		for (int i = 0; i < 8; i++)
		{
			recv_B[i] = tempB[i];
			printf("%d \t", recv_B[i]);

		}

		//caclate intersection
		for(int i=0;i<8;i++)
		{
			for (int j = 0; j < 32; j++)
			{
				if (recv_B[i] == recv_A[j])
				{
					local_intersection++;
					break;
				}
			}
		}
		printf("\n loacl |AnB|: %d \n", local_intersection);

		total_intersection = local_intersection;
		//recv from others
		int temp;
		for (int i = 1; i < 4; i++)
		{
			MPI_Recv(&temp, 1, MPI_INT, i,60, MPI_COMM_WORLD, &sta);
			total_intersection += temp;
		}
		printf("\ntoatal intersection: %d\n", total_intersection);
		//dice coefficient
		int sizeA = 32;
		int sizeB = 32;
		double dice = (2.0 * total_intersection) / (sizeA + sizeB);
		printf("dice Coefficient: %.3f\n", dice);
		printf("similarity :%.2f%%", dice * 100);


	}
	if (pid !=0)
	{
		printf("other process \n");
		//recv A(32)
		MPI_Recv(&recv_A, 32, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		//recv B(8)
		MPI_Recv(&recv_B, 8, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		//caclate intersection
		for(int i=0;i<8;i++)
		{
			for (int j = 0; j < 32; j++)
			{
				if (recv_B[i] == recv_A[j])
				{
					local_intersection++;
					break;
				}
			}
		}
		printf("\n loacl |AnB|: %d \n", local_intersection);
		MPI_Send(&local_intersection, 1, MPI_INT, 0, 60, MPI_COMM_WORLD);

	}	 
	MPI_Finalize();
}

//output
 //loacl |AnB|: 7
//other process

 loacl |AnB|: 2
other process

 loacl |AnB|: 4
process 0
A:      45      41      92      79      11      83      97      91      98      67      53      34      68      72     76       12      78      59      64      6       89      62      26      23      17      35      36      18      25     55       43      56
 B:     5       18      96      63      23      10      42      34
 loacl |AnB|: 3

toatal intersection: 16
dice Coefficient: 0.500
similarity :50.00%
