#include<iostream>
#include<fstream>
#include"Simplex.hpp"
#include<stdlib.h>
using namespace std;


Simplex :: Simplex()
{
	char filename[10];

	ifstream fin;
	cout<<"\nEnter the simplex matrix file name:";
	cin>>filename;
	fin.open(filename);

	Cb=new double[row];
	Xb=new double[row];
	ratio=new double[row];
	Cj=new double[column-1];
	Zj=new double[column-1];
	Zj_Cj=new double[column-1];


	fin>>row>>column;
	cout<<"\nIn the matrx Rows = "<<row<<" columnS ="<<column<<"\n";


	simplexMatrix= new double*[row];

	for (int i = 0; i < row; ++i)
	{
		simplexMatrix[i]= new double[column];
		for (int j = 0; j < column; ++j)
		{
			fin>>simplexMatrix[i][j];
			cout<<"\t"<<simplexMatrix[i][j];

		}	
		cout<<"\n";
	}
	fin.close();
}

/*Simplex :: Simplex(char str[20])
{

	ifstream fin;
	
	fin.open(str);
	fin>>row>>column;
	cout<<"\nIn the matrx Rows = "<<row<<" columnS ="<<column<<"\n";


	simplexMatrix= new double*[row];

	for (int i = 0; i < row; ++i)
	{
		simplexMatrix[i]= new double[column];
		for (int j = 0; j < column; ++j)
		{
			fin>>simplexMatrix[i][j];
			cout<<"\t"<<simplexMatrix[i][j];

		}	
		cout<<"\n";
	}
	cout<<"\n Enter the demand values";
	for (int i = 0; i < column; ++i)
	{
		fin>>demand[i];
	}

	cout<<"\n Enter the capacity values";
	for (int i = 0; i < row; ++i)
	{
		fin>>capacity[i];
	}


	fin.close();
}*/


void Simplex:: display()
{
	cout<<"\n";
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			cout<<"\t"<<simplexMatrix[i][j];
		}
		cout<<"\n";
	}
	
}

void Simplex:: simplexOperation()
{

		double sum=0, mostNegativeElement, flag=0;

		cout<<"\n Enter the Cj values";
		for (int i = 0; i < column-1; ++i)
		{
			cin>>Cj[i];
		}

		
		do{

			flag=0;
			cout<<"\n Now calculating Zj: as\n";
			for(int i=0; i< column-1 ; ++i)
			{
				sum=0;
				for (int j = 0; j < row; ++j)
				{
					sum=sum+(Cb[j]*simplexMatrix[j][i]);
				}
				Zj[i]=sum;
				Zj_Cj[i]=Zj[i]-Cj[i];

				if(Zj_Cj[i]>=0)
				{
					flag++;
				}
				cout<<"\t"<<Zj_Cj[i];
			}

			if(flag==(column-1))
			{
				cout<<"\nvalue of Cb:\n";
				for(int i=0;i<row;++i)
				{
					cout<<"\t"<<Cb[i];
				}
				exit(0);
			}

			int k=0;
			mostNegativeElement = Zj_Cj[0];
			for (int i = 0; i < column-1; ++i)
			{
				if((Zj_Cj[i]<0) && (Zj_Cj[i]<mostNegativeElement))
				{
					mostNegativeElement=Zj_Cj[i];
					k=i;
				}
			}
			cout<<"\nmost negative"<<mostNegativeElement<<" k "<<k;

			int m=calculatingRatio(k);
			cout<<"\t pivot :"<<simplexMatrix[m][k];

		//error here

			if(simplexMatrix[m][k]!=1)
			{
				double pivot= simplexMatrix[m][k];
				for (int i = 0; i<column; ++i)
				{
					simplexMatrix[m][i]=simplexMatrix[m][i] / pivot;
				}
			}
			display();
			cout<<"After row reduce";
			reduceRow(m ,k);
			Cb[m]=Cj[k];
			flag++;

			for(int i=0;i<row;++i)
			{
				cout<<"\t"<<Cb[i];
			}
		}while(flag<50);

}

//void Simplex:: calculatingRatio(int k, double **simplexMatrix, double *ratio)
int Simplex:: calculatingRatio(int k)
{
	int m;
	for(int i=0;i< row;++i)
	{ 
        if(simplexMatrix[i][k]<=0)
        {
        	ratio[i] = 9999;
        }
        else
        {
            ratio[i]=simplexMatrix[i][column-1]/simplexMatrix[i][k];
        }   
	}

	double minRatio=ratio[0];
	for (int i = 0; i < row; ++i)
	{
		cout<<" \nratio "<<ratio[i];
		if(ratio[i]<minRatio)
		{
			minRatio=ratio[i];
			m=i;
		}	
	}
	return m;
}

void Simplex:: reduceRow(int m, int k)
{
	double temp;
	for(int i=0;i<row;++i)
	{
		temp=simplexMatrix[i][k]*1;
		
		for (int j = 0; j < column; ++j)
		{
			if(m!=i)
			{
			
				simplexMatrix[i][j] = simplexMatrix[i][j] +(-1)*(temp*(simplexMatrix[m][j]));
				
			}
		}
	}
	display();
}


