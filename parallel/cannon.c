#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char * argv[])
{
	FILE *fptr;
	int rank, size,dimension,i,j, n,n1, k=0,i1,temp, j1, ii,jj,kk, index; 
	int **A, **B, **C; //Matrices A, B And C
	int *A1, *B1, *C1; //Array for respective
	int *recvA, *recvB,  sendA[2][2],*result, sendB[2][2];//*sendA, *sendB,result[2][2],
	int dispA, dispB, left, right, top, bottom;
	
	int periods[2] = {1,1};
	int coords[2], reorder=0;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int dims[2] = {sqrt(size), sqrt(size)}; //4*4= # of processors 
	MPI_Comm newDomain,oldDomain;
	MPI_Status status;
	MPI_Request request;
	
	//creating 2 dimension virtual topology
	MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder , &newDomain);
	MPI_Cart_coords(newDomain, rank, 2, coords);
	//printf(" %d_%d_%d ",rank,coords[0],coords[1]);

	if(rank==0)
	{
		//Reading Two matrices from the File
		fptr=fopen("cannonText.txt","r");
		if(fptr==NULL){
			printf("\n unable to read file");
		}
		else
		{
			fscanf(fptr,"%d",&dimension);
			printf("\ndimension=%d\t\n",dimension);

			A1=(int *)calloc((dimension*dimension),sizeof(int));
			B1=(int *)calloc((dimension*dimension),sizeof(int));
			C1=(int *)calloc((dimension*dimension),sizeof(int));

			A=(int **)calloc(dimension,sizeof(int*));
			B=(int **)calloc(dimension,sizeof(int*));
			C=(int **)calloc(dimension,sizeof(int*));

			for(i=0; i<dimension; ++i)
			{
				A[i]=(int *)calloc(dimension,sizeof(int));
				B[i]=(int *)calloc(dimension,sizeof(int));
				C[i]=(int *)calloc(dimension,sizeof(int));
			}

			printf("matrix A:\n");
			for(i=0; i<dimension; ++i)
			{	
				for(j=0; j<dimension; ++j)
				{
					fscanf(fptr,"%d",&A[i][j]);
					printf("%d\t",A[i][j]);
				}
				printf("\n");
			}
			
			printf("\n\n");
			printf("matrix B:\n");
			for(i=0; i<dimension; ++i)
			{	
				for(j=0; j<dimension; ++j)
				{
					fscanf(fptr,"%d",&B[i][j]);
					printf("%d\t",B[i][j]);
				}
				printf("\n");
			}
		}
		fclose(fptr);
		//n =is the dimension of subMatrix(chunk)
		n=(dimension/sqrt(size)) * (dimension/sqrt(size)); 

		//Rearranging A and B to array A1 and B1	
		for(i=0;i<dimension;i+=sqrt(n))
		{
			j=0;
			while(j<dimension)
			{
				temp=i;
				for(j1=0;j1<sqrt(n);++j1)
				{
					for(i1=0;i1<sqrt(n);++i1)
					{
						A1[k]=A[temp][j++];
						//printf("%d\t",A1[k]);
						++k;
					}
					j-=sqrt(n);
					temp+=1;
				}
				j+=(sqrt(n));
				//printf("\n");
			}
		}
		printf("\n\n");
		k=0;
		for(i=0;i<dimension;i+=sqrt(n))
		{
			j=0;
			while(j<dimension) //n
			{
				temp=i;
				for(j1=0;j1<sqrt(n);++j1)
				{
					for(i1=0;i1<sqrt(n);++i1)
					{
						B1[k]=B[temp][j++];
						//printf("%d\t",B1[k]);
						++k;
					}
					j-=sqrt(n);
					temp+=1;
				}
				j+=(sqrt(n));
				//printf("\n");
			}
		}

		
	}

	MPI_Bcast(&dimension, 1 ,MPI_INT ,0 , MPI_COMM_WORLD);
	MPI_Bcast(&n, 1 ,MPI_INT ,0 , MPI_COMM_WORLD);

	n1=(dimension/sqrt(size));

	//recvA=(int *)calloc(n,sizeof(int));
	//recvB=(int *)calloc(n,sizeof(int));
	//sendA=(int *)calloc(n,sizeof(int));
	//sendB=(int *)calloc(n,sizeof(int));
	result=(int *)calloc(n,sizeof(int));

	MPI_Scatter(A1, n, MPI_INT, &sendA, n, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(B1, n, MPI_INT, &sendB, n, MPI_INT, 0, MPI_COMM_WORLD);
	
	//int MPI_Cart_shift(MPI_Comm comm, int direction, int disp, int *rank_source, int *rank_dest)

	for(i=0;i<sqrt(size);++i)
	{
		index=0;
		if(i==0)
		{
			dispA=coords[0];
			dispB=coords[1];	
		}
		else
		{
			dispA=1;
			dispB=1;
		}

		MPI_Cart_shift(newDomain , 1, dispA, &left, &right); //here 1 means left-right
		MPI_Sendrecv_replace(sendA, n, MPI_INT,left, 11, right, 11,
                         newDomain, MPI_STATUS_IGNORE);
		
		MPI_Cart_shift(newDomain , 0, dispB, &top, &bottom);//here 0 means bottom-up
		MPI_Sendrecv_replace(sendB, n, MPI_INT,top, 10, bottom, 10,
                         newDomain, MPI_STATUS_IGNORE);
		
		for(ii=0;ii<sqrt(n);++ii)
		{
			for(jj=0;jj<sqrt(n);++jj)
			{
				for(kk=0;kk<sqrt(n);++kk)
				{
					//result[ii][jj] += sendA[ii][kk] * sendB[kk][jj];
					result[index] += sendA[ii][kk] * sendB[kk][jj];
				}
				++index;
			}
		}

	}

	MPI_Gather(result, n, MPI_INT, C1, n, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank==0)
	{
		k=0;
		for(i=0;i<dimension;i+=sqrt(n))
		{
			j=0;
			while(j<dimension)
			{
				temp=i;
				for(j1=0;j1<sqrt(n);++j1)
				{
					for(i1=0;i1<sqrt(n);++i1)
					{
						C[temp][j++]=C1[k];
						//printf("%d\t",C1[k]);
						++k;
					}
					j-=sqrt(n);
					temp+=1;
				}
				j+=(sqrt(n));
			}
		}

		printf("Resultant  matrix:\n");
		for(i=0; i<dimension; ++i)
		{	
			for(j=0; j<dimension; ++j)
			{
				printf("%d\t",C[i][j]);
			}
			printf("\n");
		}
	}

	/*for(j=0; j<n; ++j)
	{
		printf("%d__%d\n",rank,result[j]);
	}
		printf("\n");*/
	MPI_Finalize();
}


//int MPI_Isend(void *buffer, int count, MPI_Datatype datatype, int dest, int tag, MPI_Communicator comm, MPI_Request *request);
//int MPI_Irecv(void *buffer, int count, MPI_Datatype datatype, int source, int tag, MPI_Communicator comm, MPI_Request *request);


/*MPI_Gather(void* send_data,int send_count,MPI_Datatype send_datatype,void* recv_data,
int recv_count,
PI_Datatype recv_datatype,
int root,
    MPI_Comm communicator)


int MPI_Sendrecv_replace(void *buf, int count, MPI_Datatype datatype,
                         left, int sendtag, int source, int recvtag,
                         MPI_Comm comm, MPI_Status * status)

MPI_Sendrecv_replace(sendA, n, MPI_INT,
                         int dest, 11, right, int 11,
                         newDomain, MPI_Status * status)

                         */


















/* call MPI_Cart_create(old_comm, ndims, dim_size,
     &       periods, reorder, new_comm, ierr)*/
 //dimension/sqrt(size);
	//oldDomain=MPI_COMM_WORLD;
	/*if(rank==0)
	{
		fptr=fopen("cannonText.txt","r");
		if(fptr==NULL){
			printf("\n unable to read file");
		}
		else
		{
			for(i=0; i<dimension; ++i)
			{	
				for(j=0; j<dimension; ++j)
				{
					fscanf(fptr,"%d",&matrix[i][j]);
					printf("%d\t",matrix[i][j]);
				}
				printf("\n");
			}
		}
		fclose(fptr);
	}*/
