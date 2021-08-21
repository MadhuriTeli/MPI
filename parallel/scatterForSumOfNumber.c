#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main(int argc, char * argv[])
{
	int rank, size, N, n;
	int start, end, i, masterArray[20];
	MPI_Status status;
	int localsum=0, SUM;
	MPI_Init(& argc,& argv);

	N=20;
	SUM=0;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	n= N/size;


	if(rank==0){

		for(i=0; i<20; ++i){
			masterArray[i]=rand()%100;
			//printf("\n %d\t:", masterArray[i]);
		}
	}
	
	MPI_Scatter(masterArray, n, MPI_INT, masterArray, n, MPI_INT, 0, MPI_COMM_WORLD);

	/*if(rank==size-1)
	{
		end=N;
	}*/

	for(i=0;i<n;++i)
	{
		localsum=localsum+masterArray[i];
	}
	printf("\nrank=%d\t\tlocalsum= %d\n",rank,localsum);

	MPI_Reduce(&localsum, &SUM, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if(rank==0)
	{
		printf("\nSUM= %d", SUM);
	}
	
	MPI_Finalize();
}


/*


MPI_Scatter(
    void* send_data,
    int send_count,
    MPI_Datatype send_datatype,
    void* recv_data,
    int recv_count,
    MPI_Datatype recv_datatype,
    int root,
    MPI_Comm communicator)


*/
