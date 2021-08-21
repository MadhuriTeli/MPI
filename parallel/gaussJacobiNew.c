#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<math.h>
//#define dimension 3
#define theta 0.000001

int main(int argc, char * argv[])
{
	int rank, size, flag=0, k=0, part;
	
	int i,j,n, N,dimension;
	//float oldResult[dimension], newResult[dimension], norm, sum1=0,sum=0;
	//float matrix[dimension][dimension], row[dimension], v, vector[dimension];

	float *oldResult, *newResult, norm, sum1=0,sum=0;
	float **matrix, *mat, *row, v, *vector;

	FILE *fptr;

	MPI_Status status;
	MPI_Init(& argc,& argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	

	if(rank==0)
	{
		fptr=fopen("gj.txt","r");
		if(fptr==NULL){
			printf("\n unable to read file");
		}
		else
		{
			//fscanf(fptr,"%d", &dimension);
			fscanf(fptr,"%d",&dimension);
			printf("\ndimension=%d\t\n",dimension);


			matrix=(float **)calloc(dimension,sizeof(float*));
			for(i=0; i<dimension; ++i)
			{
				matrix[i]=(float *)calloc(dimension,sizeof(float));
			}

			mat=(float *)calloc((dimension*dimension),sizeof(float));
			vector=(float *)calloc(dimension,sizeof(float));
			oldResult=(float *)calloc(dimension,sizeof(float));

			k=0;

			for(i=0; i<dimension; ++i)
			{	
				for(j=0; j<dimension; ++j)
				{
					fscanf(fptr,"%f",&matrix[i][j]);
					printf("%f\t",matrix[i][j]);
					mat[k]=matrix[i][j];
					++k;
				}
				printf("\n");
			}

			printf("\n vector:\n");
			for(j=0; j<dimension; ++j)
			{
				fscanf(fptr,"%f",&vector[j]);
				printf("%f\t",vector[j]);
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
	
	MPI_Bcast(&dimension, 1, MPI_INT ,0 , MPI_COMM_WORLD);
	row = (float *)calloc(dimension,sizeof(float));
	newResult=(float *)calloc(dimension,sizeof(float));
	oldResult=(float *)calloc(dimension,sizeof(float));

	part=dimension/size;
	n=dimension*part;

	//MPI_Scatter(matrix, n, MPI_INT, &matrix[rank], n, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(mat, n, MPI_FLOAT, row, n, MPI_FLOAT, 0, MPI_COMM_WORLD);
	MPI_Scatter(vector, part, MPI_FLOAT, &v, part, MPI_FLOAT, 0, MPI_COMM_WORLD);
	MPI_Bcast(oldResult, dimension, MPI_FLOAT ,0 , MPI_COMM_WORLD);
	
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
				//sum = sum + (float)matrix[rank][j]*oldResult[j];
				sum = sum + row[j]*oldResult[j];
			}
		}
			//newResult[rank]=((float)vector[rank]-(float)sum)/(float)matrix[rank][rank];
		newResult[rank]=(v-sum)/row[rank];
		//printf("%d__sum:%d\n",rank,sum);

		MPI_Allgather(&newResult[rank], 1, MPI_FLOAT, newResult, 1, MPI_FLOAT, MPI_COMM_WORLD);
		//sum=0.00000;
	
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
		MPI_Bcast(&flag, 1 ,MPI_INT ,0 , MPI_COMM_WORLD);
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
		free(mat);
		free(vector);
		free(oldResult);
		for(i=0;i< dimension;++i)
		{
			free(matrix[i]);
		}
	}

	free(row);
	free(newResult);

	MPI_Finalize();

}
