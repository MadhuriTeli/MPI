#include<stdio.h>
#include<mpi.h>
#include<math.h>

double function(double x)
{
	double I;
	I=2+sin(2*sqrt(x));
	return I;
}

int main(int argc, char * argv[])
{
	int rank, size, i, n;
	double start, end, a, b, h, SUM=0, Result=0;

	a=0;
	b=1;
	n=4;

	MPI_Init(&argc, &argv);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	h= (b-a)/size;
	start= a+(rank*h);
	end=(a+(rank*h))+h;

	/*if((rank==0) || (rank==(size-1))) 
	{
		SUM = (3.0/8.0)*h*function(start);
		if(rank==(size-1))
		{
			SUM=SUM+((3.0/8.0)*h*function(b));
		}
	printf("\n Rank=%d\t Start=%f\t SUM=%f\th=%f\t funct=%f\n\n", rank, start, SUM,h,function(start));
	}*/


	if(rank==0) 
	{
		SUM = (3.0/8.0)*h*function(start);
		
		printf("\n Rank=%d\t Start=%f\t SUM=%f\th=%f\t funct=%f\n\n", rank, start, SUM,h,function(start));
	}
	else
	{
		if(rank%3==0)
		{
			SUM = (3.0/8.0)*h*2*function(start);
		}
		else
		{
			SUM = (3.0/8.0)*h*3*function(start);
		}
		if(rank==(size-1))
		{
			SUM=SUM+((3.0/8.0)*h*function(b));
		}
	
		printf("\n Rank=%d\t Start=%f\t SUM=%f\th=%f\t funct=%f\n\n", rank, start, SUM,h,function(start));
	}

	MPI_Reduce(&SUM, &Result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if(rank==0){
		printf("\n Result=%f", Result);
	}

	MPI_Finalize();
}
