#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<math.h>
#define dimension 3
#define theta 0.000001


int main(int argc, char * argv[])
{
	int rank, size, matrix[dimension][dimension], vector[dimension], flag=0, k=0, part;
	
	int i,j,n, N;
	float oldResult[dimension], newResult[dimension], norm, sum1=0,sum=0;

	FILE *fptr;

	MPI_Status status;
	MPI_Init(& argc,& argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	part=dimension/size;
	n=dimension*part;

	if(rank==0)
	{
		fptr=fopen("gj.txt","r");
		if(fptr==NULL){
			printf("\n unable to read file");
		}
		else
		{
			//fscanf(fptr,"%d", &dimension);
			for(i=0; i<dimension; ++i)
			{	
				for(j=0; j<dimension; ++j)
				{
					fscanf(fptr,"%d",&matrix[i][j]);
					printf("%d\t",matrix[i][j]);
				}
				printf("\n");
			}

			printf("\n vector:\n");
			for(j=0; j<dimension; ++j)
			{
				fscanf(fptr,"%d",&vector[j]);
				printf("%d\t",vector[j]);
			}
			printf("\n guess values:\n");
			for(j=0; j<dimension; ++j)
			{
				fscanf(fptr,"%f",&oldResult[j]);
				printf("%f\t",oldResult[j]);
			}
		}
		close(fptr);
	}
	
	MPI_Scatter(matrix, n, MPI_INT, &matrix[rank], n, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(vector, part, MPI_INT, &vector[rank], part, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(oldResult, dimension ,MPI_FLOAT ,0 , MPI_COMM_WORLD);
	

	do{
		if(rank==0)
		{
			for(j=0;j<dimension; ++j)
			{
				printf("%d__Rupali:%f\n",rank, oldResult[j]);
			}
		}

		for(j=0;j<dimension;++j)
		{
			if(j!=rank)
			{
				sum = sum + (float)matrix[rank][j]*oldResult[j];
			}
		}
		//printf("%d__matrix[rank][rank]:%d\n",rank,matrix[rank][rank]);
			newResult[rank]=((float)vector[rank]-(float)sum)/(float)matrix[rank][rank];
		//printf("\n%d__newresult:%f\n",rank, newResult[rank]);
		//printf("%d__sum:%d\n",rank,sum);

		MPI_Allgather(&newResult[rank], 1, MPI_FLOAT, newResult, 1, MPI_FLOAT, MPI_COMM_WORLD);
		//sum=0.00000;
	/*	for(j=0;j<dimension; ++j)
		{
			printf("%d__newwwwwwwwww:%d\n",rank, newResult[j]);
			//printf("%d__vector[j]:%d\n",rank,vector[rank]);

		}

		for(j=0;j<dimension; ++j)
		{
			//printf("%d__matrix[i][j]:%d\n",rank,matrix[rank][j]);
			printf("%d__newwwwwwwwwww[j]:%f\n",rank,newResult[j]);

		}*/

		if(rank==0)
		{

			for(j=0;j<dimension; ++j)
			{
			//printf("%d__matrix[i][j]:%d\n",rank,matrix[rank][j]);
				printf("%d__newwwwwwwwwww[j]:%f\n",k,newResult[j]);

			}

			for (i = 0; i < dimension; ++i)
			{
				sum1 = sum1 + pow((newResult[i]-oldResult[i]), 2);	
				printf("\n %d____substraction[%d]==%f",k,i, newResult[i]-oldResult[i]);	
			}

			norm = sqrt(sum1);
			//printf("%d__sum1:%f\n",rank,sum1);

			printf("%d___sum1==%f\n ",k, sum1);
			printf("%d__norm:%f\n", rank, norm);

			if(norm <= theta)
			{
				flag=1;
			}
			else
			{
				flag=0;
			}

		sum1=0;
		}
		MPI_Bcast(&flag, 1 ,MPI_FLOAT ,0 , MPI_COMM_WORLD);
		printf("%d__flag:%d\n",rank,flag);

		if(flag==1)
		{
			break;
		}
		
			MPI_Allgather(&newResult[rank], 1, MPI_FLOAT, oldResult, 1, MPI_FLOAT, MPI_COMM_WORLD);
			sum=0.00000;
	}while(1);
	
	if(rank==0)
		{

			for(j=0;j<dimension; ++j)
			{
			//printf("%d__matrix[i][j]:%d\n",rank,matrix[rank][j]);
				printf("\nResult %d :%f\n",j,newResult[j]);

			}
	}
	MPI_Finalize();

}
