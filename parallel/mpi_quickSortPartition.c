#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int quickSort(int number[25],int p, int first, int last, int num[12])
{
	/*int i,j , pivot, temp;
	if(first<last)
	{
		//pivot=first;
		pivot=p;
		i=first;
		j=last;

		while(i<j)
		{
			while(number[i]<=pivot && i<last)
			{
				i++;
			}
			while(number[j]> pivot)
			{
				j--;
			}
			if(i<j)
			{
				temp=number[i];
				number[i]=number[j];
				number[j]=temp;
			}
		}

		temp=pivot;
		pivot=number[j];
		number[j]=temp;
		
	}*/



	int i,j , pivot, temp, m, n, pivotElement, index=0;
	if(first<last)
	{

		if(p!=number[0])
		{
			pivot=p;
			i=first;
			j=last;
		
			m=0, n=j;

			while(i<=j){
				if(number[i]<pivot){
					num[m]=number[i];
					m++;
					i++;
				}
				else{
					num[n]=number[i];
					i++;
					n--;
				}
			}

			for(i=0;i<=(last-first);++i)
			{
				//printf("\n num=%d", num[i]);
				number[i]=num[i];
			}

			for(i=0;i<=(last-first);++i)
			{
				
				if(number[i]<=pivot){
					index=index+1;
				}	
				else{
					break;
				}
			}	
			//if(index==0)
			//	return (index);
			//else
				return (index-1);
			
		}
		else
		{
		pivot=0;
		pivotElement=number[0];
		i=first;
		j=last;

		while(i<j)
		{
			while(number[i]<=number[pivot] && i<last)
			{
				i++;
			}
			while(number[j]> number[pivot])
			{
				j--;
			}
			if(i<j)
			{
				temp=number[i];
				number[i]=number[j];
				number[j]=temp;
			}
		}

		temp=number[pivot];
		number[pivot]=number[j];
		number[j]=temp;

		for(i=0;i<=(last-first);++i){
	
			if(number[i]<=pivotElement){
				index=index+1;
			}	
			else{
				break;
			}	
		}
		//if(index==0)
		//	return (index);
		//else
			return (index-1);

		}

	}















/*int i,j , pivot, temp, m, n, pivotElement, index=0;
if(first<last)
	{
		//pivot=first;
		if(p==number[0])
		{
			pivot=0;
			i=first;
			j=last;
			pivotElement=number[0];
		
	
		while(i<j)
		{
			while(number[i]<=number[pivot] && i<last)
			{
				i++;
			}
			while(number[j]> number[pivot])
			{
				j--;
			}
			if(i<j)
			{
				temp=number[i];
				number[i]=number[j];
				number[j]=temp;
			}
		}

		temp=number[pivot];
		number[pivot]=number[j];
		number[j]=temp;
		
	//}

	for(i=0;i<(last-first);++i){
	
		if(number[i]<=pivotElement){
			index=index+1;
		}	
		else{
			break;
		}
	}
	return (index-1);
	}
	else
	{

		pivot=p;
			i=first;
			j=last;
			
		m=0, n=j;

		while(i<=j){
			if(number[i]<=pivot){
				num[m]=number[i];
				m++;
				i++;
			}
			else{
				
num[n]=number[i];
				i++;
				n--;
			}
		
		}

		for(i=0;i<(last-first);++i)
		{
			number[i]=num[i];
		}

		for(i=0;i<(last-first);++i){
	
		if(number[i]<=pivot){
			index=index+1;
		}	
		else{
			break;
		}
	}
	return (index-1);
		
	}*/



}



int main(int argc, char * argv[])
{
	int rank, size, N, n;
	
	int i, pivot, flag=0, pivotIndex, index1,index, count=0, temp=0, demo, pivot1;

	int number[12], num[12], recv[12];
	MPI_Status status;
	N=12;
	
	MPI_Init(& argc,& argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	

	if(rank==0){

		for(i=0; i<12; ++i){
			number[i]=rand()%80;
			printf("\n %d\t:", number[i]);
		}
		pivot=number[0];
	}
	
	n=N/size;

	MPI_Scatter(number, n, MPI_INT, number, n, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast( &pivot, 1 ,MPI_INT ,0 , MPI_COMM_WORLD);


	printf("\n -----------------------\n");
	index = quickSort(number, pivot, 0, n-1, num);

	printf("\n After sorted elements of %d processor:\n", rank);
	for(i=0;i<n;++i)
	{
		printf("%d\t", number[i]);

	}
	printf("\nIndex %d rank of pivot=%d",rank, index);
	printf("\n ----------------------------------rupali-------------------------------------\n");

	if(rank==0 || rank==1)
	{
		//count=index+1; 

		count=n-(index+1);
		MPI_Send(&count, 1, MPI_INT, rank+2, 1, MPI_COMM_WORLD);
		MPI_Send(&number[index+1], count, MPI_INT, rank+2, 1, MPI_COMM_WORLD); //[index+1]
		MPI_Recv(&count, 1, MPI_INT, rank+2, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(recv, count, MPI_INT, rank+2, 1, MPI_COMM_WORLD, &status);

	}

	else{
		//count=n-index; 
		count=index+1;
		MPI_Recv(&count, 1, MPI_INT, rank-2, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(recv, count, MPI_INT, rank-2, 1, MPI_COMM_WORLD, &status);
		MPI_Send(&count, 1, MPI_INT, rank-2, 1, MPI_COMM_WORLD);
		MPI_Send(number, count, MPI_INT, rank-2, 1, MPI_COMM_WORLD);//[index]

		
		}
		printf("\n Recv array is of %d processor:\n", rank);
		/*if(rank==0 || rank==1)
		{
			printf("\n\n");
			//printf("\n count= %d and index= %d of %d processor:\n",count, index, rank);
			temp=0;
			
			temp=count;
			for(i=0;i<=index;++i)
			{
				recv[temp]=number[i]; 
				++temp;
			}
		}
		else
		{
			printf("\n\n");
			//printf("\n count= %d and index= %d of %d processor:\n",count, index, rank);
			temp=count;
			demo=index+1;
			for(i=demo;i<n;++i)
			{
				recv[temp]=number[i];
				++temp;
			}
			
		}*/
		for(i=0; i<5; ++i)
		{
			//printf("reciving  %d array:", rank);
			printf("%d___%d\t",rank,recv[i]);
		}
		printf("\n\n");





		//stage 2

	/*	if(rank==0 || rank==2)
		{
			pivot1=recv[0];
			MPI_Send(&pivot1, 1, MPI_INT, rank+1, 1, MPI_COMM_WORLD);
		}
		else
		{
			MPI_Recv(&pivot1, 1, MPI_INT, rank-1, 1, MPI_COMM_WORLD, &status);
		}
		
		printf("\n -----------------------\n");
		index1 = quickSort(recv, pivot1, 0, temp-1, num);

		printf("\n stage2 sorting  processor=%d     pivot1=%d:\n", rank, pivot1 );
		for(i=0;i<temp;++i)
		{
			printf("%d\t", recv[i]);

		}
		printf("\nIndex of pivot=%d", index1);
		printf("------------------------------------\n");*/

	MPI_Finalize();
}

/*

MPI_Bcast(
    void* data,
    int count,
    MPI_Datatype datatype,
    int root,
    MPI_Comm communicator)


*/
