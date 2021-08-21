#include<stdio.h>
#include<mpi.h>

int main(int argc, char * argv[])
{
	int rank, size, N, n;
	int start, end, i;
	MPI_Status status;
	int localsum=0, SUM;
	MPI_Init(& argc,& argv);

	N=100;
	SUM=0;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	n= N/size;
	start= rank*n;
	end=(rank*n)+n;

	if(rank==size-1)
	{
		end=N;
	}

	for(i=start;i<end;++i)
	{
		localsum=localsum+i;
	}

	if(rank==0)
	{
		for(i=1;i<size;++i)
		{
				MPI_Recv(&SUM, 1, MPI_INT, i, rank-1, MPI_COMM_WORLD, &status);
				localsum+=SUM;
		}
		printf("\n\ntotal= %d", localsum);
	}
	else
	{
		MPI_Send(&localsum, 1, MPI_INT, 0, rank-1, MPI_COMM_WORLD);

	}

	/*if(rank==(size-1))
	{
		for(i=0;i<size-1;++i)
		{
				MPI_Recv(&SUM, 1, MPI_INT, i, rank-1, MPI_COMM_WORLD, &status);
				localsum+=SUM;
		}
		printf("\n\ntotal= %d", localsum);
	}
	else
	{
		MPI_Send(&localsum, 1, MPI_INT, size-1, rank-1, MPI_COMM_WORLD);

	}*/


	MPI_Finalize();
}
