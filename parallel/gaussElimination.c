#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<math.h>
#define dimension 4
#define theta 0.000001

int main(int argc, char * argv[])
{
	FILE *fptr;
	int rank, size,i,j, n, k=0,i1, j1,ii, jj, kk, resultMat[dimension][dimension],part; 
	float matrix[dimension][dimension], B[dimension] ,b, row[dimension], divVar,
	 recvRow[dimension], recvB, mulfactor, Result[dimension], sum=0.0;
	//int **A, *B, part;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	MPI_Status status;
	MPI_Request request;
	

	if(rank==0)
	{
		fptr=fopen("gaussEl.txt","r");
		if(fptr==NULL){
			printf("\n unable to read file");
		}
		else
		{
			for(i=0; i<dimension; ++i)
			{	
				//A[i]=(int *)calloc(dimension,sizeof(int));
				for(j=0; j<dimension; ++j)
				{
					fscanf(fptr,"%f",&matrix[i][j]);
					printf("%f\t",matrix[i][j]);
				}
				printf("\n");
			}

			printf("\n vector:\n");
			for(j=0; j<dimension; ++j)
			{
				fscanf(fptr,"%f",&B[j]);
				printf("%f\t",B[j]);
			}
			
		}
	fclose(fptr);
	}
	
	part=dimension/size;
	n=dimension*part;

	MPI_Scatter(matrix, n, MPI_FLOAT, row, n, MPI_FLOAT, 0, MPI_COMM_WORLD);
	MPI_Scatter(B, part, MPI_FLOAT, &b, part, MPI_FLOAT, 0, MPI_COMM_WORLD);

	for(j=0;j<n;++j)
	{
		Result[j]=0;
	}
	printf("\n");

	for(i=0; i< size; ++i)
	{
		if(rank==i)
		{
			divVar = row[rank];
			for(j=i;j<n;++j)
			{
				row[j] = row[j] / divVar;
			}

			b = b/divVar;
			for(j=(rank+1);j<size;++j)
			{
				MPI_Send(row, n, MPI_FLOAT, j, 1, MPI_COMM_WORLD);
				MPI_Send(&b, 1, MPI_FLOAT, j, 2, MPI_COMM_WORLD);
			}
		}

		if(rank>i)
		{
			MPI_Recv(recvRow, n, MPI_FLOAT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&recvB, 1, MPI_FLOAT, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


			mulfactor = row[i];
			b= b-(mulfactor* recvB);

			for(j=i;j<n;++j)
			{
				row[j] = row[j] -(recvRow[j]*mulfactor); //multiplication factor p1= a00/a01
			}

		}
		
	}
	
	/*for(j=0;j<n;++j)
	{
		printf("%d__:%f__%f\n",rank, b, row[j]);
		//printf("%d__:%f\n",rank, temp[j]);
	}

	printf("\n\n");*/




/*for(j=0;j<dimension;++j)
		{
			if(j!=rank)
			{
				sum = sum + (float)matrix[rank][j]*oldResult[j];
			}
		}

			newResult[rank]=((float)vector[rank]-(float)sum)/(float)matrix[rank][rank];*/
	for(i=(size-1); i>=0; --i)
	{
		if(rank==i)
		{
			//Result[rank]=b;
			for(j=0;j<dimension;++j)
			{
				if(j!=rank)
				{
					sum = sum + (row[j] * Result[j]);
				}
			}

			Result[rank]=(b-sum)/row[rank];

			for(j=(rank-1);j>=0;--j)
			{
				MPI_Send(&Result[rank], 1, MPI_FLOAT, j, 1, MPI_COMM_WORLD);
				//	MPI_Bcast(&Result[rank], 1 ,MPI_FLOAT ,0 , MPI_COMM_WORLD);

			}
		}

		if(rank<i)
		{
			MPI_Recv(&Result[i], 1, MPI_FLOAT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	}

if(rank==0){
	for(j=0;j<n;++j)
	{
		printf("%d__:%f\n",rank, Result[j]);
	}
}	
	MPI_Finalize();
}




























