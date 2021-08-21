#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#define dimension 8


int main(int argc, char * argv[])
{
	int rank, size, matrix[dimension][dimension], vector[dimension], result[dimension], sum=0, resultantVector[dimension], part;
	
	int i,j,n, N, disp[dimension], sendCount[dimension], temp, dispR[dimension];

	MPI_Status status;
	MPI_Init(& argc,& argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	part=dimension/size;
	n=dimension*part;

	if(rank==0)
	{
		

		for(i=0; i<dimension; ++i)
		{	
			vector[i]=rand()%10;
			for(j=0; j<dimension; ++j)
			{
				matrix[i][j]=rand()%11;
				printf("%d\t",matrix[i][j]);
			}
			printf("\n");
		}

		printf("\n vector:\n");
		for(j=0; j<dimension; ++j)
		{
			printf("%d\t",vector[j]);
		}
	
		
	}
	
		
	if(dimension%size!=0)
	{
		for(i=0;i<size;++i)
		{
			disp[i]=i*n;
			dispR[i]=i;
		}
		for(i=0;i<size;++i)
		{
			if(i==(size-1))
			{
				sendCount[i]=(n*n)-disp[i];
			}
			else
			{
				sendCount[i]=disp[i+1]-disp[i];
			}
		}

		MPI_Scatterv(matrix, sendCount, &disp[rank], MPI_INT, matrix, sendCount[rank], MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(vector, dimension ,MPI_INT ,0 , MPI_COMM_WORLD);


		temp=sendCount[rank]/dimension;
		for(i=0;i<temp;++i) //part
		{
			result[i]=0;
			for(j=0;j<dimension; ++j)
			{
				result[i]=result[i]+(matrix[i][j]*vector[j]);
			}

			printf("\n %d processor result[i]:%d\n",rank, result[i]);
		}

		MPI_Gatherv(result, temp, MPI_INT, resultantVector, &temp, &dispR[rank], MPI_INT, 0, MPI_COMM_WORLD);
	}
	else
	{

		MPI_Scatter(matrix, n, MPI_INT, matrix, n, MPI_INT, 0, MPI_COMM_WORLD);
		//MPI_Scatterv(matrix, sendCount, &disp[rank], MPI_INT, matrix, sendCount[rank], MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(vector, dimension ,MPI_INT ,0 , MPI_COMM_WORLD);
	

		//temp=sendCount[rank]/dimension;
		for(i=0;i<part;++i) //temp
		{
			result[i]=0;
			for(j=0;j<dimension; ++j)
			{
				result[i]=result[i]+(matrix[i][j]*vector[j]);
			}

			printf("\n %d processor result[i]:%d\n",rank, result[i]);
		}
		MPI_Gather(result, part, MPI_INT, resultantVector, part, MPI_INT, 0, MPI_COMM_WORLD);
	}


	
	/*MPI_Scatter(matrix, n, MPI_INT, matrix, n, MPI_INT, 0, MPI_COMM_WORLD);
	//MPI_Scatterv(matrix, sendCount, &disp[rank], MPI_INT, matrix, sendCount[rank], MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(vector, dimension ,MPI_INT ,0 , MPI_COMM_WORLD);
	

	//temp=sendCount[rank]/dimension;
	for(i=0;i<part;++i) //temp
	{
		result[i]=0;
		for(j=0;j<dimension; ++j)
		{
			result[i]=result[i]+(matrix[i][j]*vector[j]);
		}

		printf("\n %d processor result[i]:%d\n",rank, result[i]);
	}

	
	
	MPI_Gather(result, part, MPI_INT, resultantVector, part, MPI_INT, 0, MPI_COMM_WORLD);*/
   	//MPI_Gatherv(result, temp, MPI_INT, resultantVector, &temp, &dispR[rank], MPI_INT, 0, MPI_COMM_WORLD); 
	if(rank==0)
	{
		printf("\n %d resultant vector:", rank);
		for(j=0; j<dimension; ++j)
		{
			printf("%d\t",resultantVector[j]);
		}

	}
	
	MPI_Finalize();

}

/*

MPI_Gather(
    void* send_data,
    int send_count,
    MPI_Datatype send_datatype,
    void* recv_data,
    int recv_count,
    MPI_Datatype recv_datatype,
    int root,
    MPI_Comm communicator)



int MPI_Scatterv(
  void *sendbuf,
  int *sendcnts,
  int *displs,
  MPI_Datatype sendtype,
  void *recvbuf,
  int recvcnt,
  MPI_Datatype recvtype,
  int root,
  MPI_Comm comm
);

*/

