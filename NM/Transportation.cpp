#include<iostream>
#include<fstream>
#include"Transportation.hpp"
#include<stdlib.h>
#define maxx 99999
using namespace std;

Transportation:: Transportation()
{
	char filename[10];
	occupiedCells=0;

	ifstream fin;
	cout<<"\nEnter the Transportation matrix file name:";
	cin>>filename;
	fin.open(filename);

	fin>>row>>column;
	cout<<"\nIn the matrx Rows = "<<row<<" columnS ="<<column<<"\n";

	matrix= new double*[row];
	initialSolution=new double*[row];
	demand=new double[column];
	capacity=new double[row];


	for (int i = 0; i < row; ++i)
	{
		matrix[i]= new double[column];
		initialSolution[i]=new double[column];
		for (int j = 0; j < column; ++j)
		{
			fin>>matrix[i][j];
			cout<<"\t"<<matrix[i][j];
		}	
		cout<<"\n";
	}

	cout<<"\n demand values are:";
	for (int i = 0; i < column; ++i)
	{
		fin>>demand[i];
		cout<<"\t"<<demand[i];

	}

	cout<<"\n capacity values are:";
	for (int i = 0; i < row; ++i)
	{
		fin>>capacity[i];
		cout<<"\t"<<capacity[i];
	}
	fin.close();
}

void Transportation:: northWestCorner()
{

	int i=0,j=0;

	while(i<row || j< column)
	{
		if(capacity[i]<demand[j])
		{
			initialSolution[i][j]=capacity[i];
			demand[j]=demand[j]-capacity[i];
			capacity[i]=0;
			i++;
		}
		else
		{
			initialSolution[i][j]=demand[j];
			capacity[i]=capacity[i]-demand[j];
			demand[j]=0;
			j++;

		}
	}

	cout<<"\n Initial solution:\n";
	for(int i=0;i<row;++i)
	{
		for (int j = 0; j < column; ++j)
		{
			cout<<"\t"<<initialSolution[i][j];
			cost=cost+(initialSolution[i][j]* matrix[i][j]);
		}
		cout<<"\n";
	}
	cout<<"\n total cost="<<cost<<"\n";
}

int Transportation :: checkingForAllZero()
{
	int demo=0;
	for (int j = 0; j < column; ++j)
	{
		if(demand[j]==0)
		{
			demo++;
		}
	}

	for (int j = 0; j < row; ++j)
	{
		if(capacity[j]==0)
		{
			demo++;
		}
	}
	return demo;
}
void Transportation :: initialSolutionCalculation(int c, int r)
{
	if(demand[c] < capacity[r])
	{
		
		initialSolution[r][c]=demand[c];//(matrix[r][c] * demand[c]);
		capacity[r]=capacity[r]-demand[c];
		demand[c]=0;
	}
	else
	{
		
		initialSolution[r][c]=capacity[r];//(matrix[r][c] * capacity[r]);
		demand[c]=demand[c]-capacity[r];
		capacity[r]=0;
	}
}


void Transportation :: leastCost()
{
	int i=0,j=0, large=0;

	int min=matrix[0][0];
	int minCol=0;
	int minRow=0;

	int temp=0, temp1;
	temp1=row+column;

	while(temp<temp1)
	{
		temp=0;
		for(int i=0;i<row;++i)
		{
			for (int j = 0; j < column; ++j)
			{
				if(capacity[i]>0 && demand[j]>0) 
				{
					if(matrix[i][j] < min)
					{
						minRow=i;
						minCol=j;
						min = matrix[i][j];
					}
				}
			
			}
		}

		initialSolutionCalculation(minCol, minRow);
		temp = checkingForAllZero();
		min=maxx;
	}

	cout<<"\n Initial Solution:\n";
	for(int i=0; i < row ;++i)
	{
		for (int j = 0; j < column; ++j)
		{
			cost=cost+(initialSolution[i][j]* matrix[i][j]);
			cout<<"\t"<<initialSolution[i][j];
		}
		cout<<"\n";
	}
	cout<<"\n total cost="<<cost<<"\n";
}

void Transportation :: VAM()
{
	int minRow[row], temp1;
	int minCol[column],min, rupa;
	int min1, min2, maxPenulty, minR,minC, temp, k, rowPos;

	temp1=row+column;
	//cout<<"temp1="<<temp1;
	rupa=0;
	while(rupa<temp1) // while loop for terminate
	{
		rupa=0;
		minR=maxx, minC=maxx;
		min1=0; min2=0;
		maxPenulty=-1;

		//calculating Row penulty
		for(int i=0;i<row;++i) 
		{
			
			int k1;

			for( k1=0;k1<column;++k1)
			{
				if((capacity[i]!=0) && (demand[k1]!=0))
				{
					min1=matrix[i][k1];
					++k1;
					break;
				}
			}
			for(k=k1;k<column;++k)
			{
				if((capacity[i]!=0) && (demand[k]!=0))
				{
					min2=matrix[i][k];
					break;
				}
			}



			if(capacity[i]!=0)
			{
				for (int j = k; j < column; ++j)
				{
					if(capacity[i]>0 && demand[j]>0) 
					{	
						if( matrix[i][j]<min1)
						{

							min2=min1;
							min1=matrix[i][j];
						}
						else
						{
							if(min2 > matrix[i][j] && min1< matrix[i][j] )
							{
								min2=matrix[i][j];
							}
						}
					}
				}

				minRow[i]=abs(min2-min1);
				//cout<<"\nmin2="<<min2<<"\tmin1="<<min1<<"\tminRow[i]="<<minRow[i];	

				//Calculating finding Maximum penulty
				if(maxPenulty==-1)
				{
					maxPenulty=minRow[i];
					temp=i;
					rowPos=1;
				}
				else
				{
					if(minRow[i]>maxPenulty)
					{
						maxPenulty=minRow[i];
						temp=i;
						rowPos=1;
					}
					else
					{
						if(minRow[i]==maxPenulty)
						{
							//if(rowPos=1)
							if(capacity[temp]<capacity[i])
							{
								maxPenulty=minRow[i];
								temp=i;
								rowPos=1;
							}
						}
					}
				}
			}	
		}


		//calculating Column penulty
		for(int i=0;i<column;++i)
		{
			
			int k1;
			for(k1=0;k1<row;++k1)
			{
				if((capacity[k1]!=0) && (demand[i]!=0))
				{
					min1=matrix[k1][i];
					++k1;
					break;
				}
			}
			for(k=k1;k<row;++k)
			{
				if((capacity[k]!=0) && (demand[i]!=0))
				{
					min2=matrix[k][i];
					break;
				}
			}

			if(demand[i]!=0){
				for (int j = k; j < row; ++j)
				{
					if(capacity[j]>0 && demand[i]>0) 
					{	
						if(min1>= matrix[j][i])
						{

							min2=min1;
							min1=matrix[j][i];

						}
						else
						{
							if(min2 > matrix[j][i] && min1< matrix[j][i] )
							{
								min2=matrix[j][i];
							}
						}
					}
				}
				minCol[i]=abs(min2-min1);
				

				//cout<<"\n\nminCol[i]="<<minCol[i]<<"\tmin2="<<min2<<"\tmin1="<<min1;	

				//Calculating finding Maximum penulty
				if(maxPenulty==-1)
				{
					maxPenulty=minCol[i];
					temp=i;
					rowPos=0;
				}
				else
				{
					if(minCol[i]>maxPenulty)
					{
						maxPenulty=minCol[i];
						temp=i;
						rowPos=0;
					}
					else
					{
						if(minCol[i]==maxPenulty)
						{
						if(rowPos==1)
						{
							if(capacity[temp]< demand[i])
							{
								maxPenulty=minCol[i];
								temp=i;
								rowPos=0;
							}
						}
						else
						{
							if(demand[temp]< demand[i])
							{
								maxPenulty=minCol[i];
								temp=i;
								rowPos=0;
							}
						}
						}

					}
				}
		
			}	
		}
		
		cout<<"\n\nPenulty= "<<maxPenulty<<"\trowPos= "<<rowPos<<"\ttemp= "<<temp;
	
		min=maxx;
		if(rowPos==1)
		{
			int i=temp;
			for (int j = 0; j < column; ++j)
			{
				if(capacity[i]>0 && demand[j]>0) 
				{
	
					if(matrix[i][j] < min)
					{
						minR=i;
						minC=j;
						min = matrix[i][j];
					}
				}
			
			}
		}
		else
		{
			int i=temp;
			for (int j = 0; j < row; ++j)
			{
				if(capacity[j]>0 && demand[i]>0) 
				{
	
					if(matrix[j][i] < min)
					{
						minR=j;
						minC=i;
						min = matrix[j][i];
					}
				}
			
			}
		}

		initialSolutionCalculation(minC, minR);
	
		rupa=checkingForAllZero();
		min=maxx;

	}
	cout<<"\n Initial Solution:\n";
	maxOccupiedCells=0;
	int occupiedtemp=0
	for(int i=0; i < row ;++i)
	{
		for (int j = 0; j < column; ++j)
		{

			cost=cost+(initialSolution[i][j]* matrix[i][j]);
			cout<<"\t"<<initialSolution[i][j];
			if(initialSolution[i][j]!=0)
			{
				occupiedCells++;
			}
		}
		cout<<"\n";
	}
	cout<<"\n total cost="<<cost<<"\n";
	cout<<"\n occupiedCells="<<occupiedCells<<"\n";
}

void Transportation:: modi()
{
	// we can apply modi test on only non-degenrate solution
	double demand1[column], capacity1[row];
	double u[row]={0}, v[column]={0}, c[row][column];

	for(int i=0;i<column;++i)
	{
		demand1[i]=demand[i];
	}
	for(int i=0;i<row;++i)
	{
		capacity1[i]=capacity[i];
	}

	VAM();

	for(int i=0;i<column;++i)
	{
		demand[i]=demand1[i];
	}
	for(int i=0;i<row;++i)
	{
		capacity[i]=capacity1[i];
	}
	if(occupiedCells<(column+row-1))
	{
		cout<<"\nBasic Initial feasible solution is Degenerated";
	}
	else
	{
		if(occupiedCells==(column+row-1))
		{
			//cout<<"\nBasic Initial feasible solution is non-Degenerated";
			for(int i=0;i<row;++i)
			{
				for (int j = 0; j < column; ++j)
				{
					c[i][j]=matrix[i][j];
					//cout<<"\t"<<c[i][j];
				}
				//cout<<"\n";
			}
			//put u1==0;

		/*	for(int j=0;j<column;++j)
			{
				if(initialSolution[0][j]!=0)
				{
					v[j]=c[0][j]-u[0];
					cout<<"\t"<<v[j];
				}
				else
				{
					v[j]=0;
					cout<<"\t"<<v[j];
				}
			}*/
			
		}
		
	}
}


















//cout<<"\t\t min= "<<min<<"\t row= "<<minR<<"\t col= "<<minC;

		/*if(demand[minC] < capacity[minR])
		{
			initialSolution[minR][minC]=(matrix[minR][minC] * demand[minC]);
			capacity[minR] = capacity[minR]-demand[minC];
			demand[minC]=0;
		}
		else
		{
			initialSolution[minR][minC]=(matrix[minR][minC] * capacity[minR]);
			demand[minC]=demand[minC]-capacity[minR];
			capacity[minR]=0;
		}*/
/*if(demand[minCol] < capacity[minRow])
	{
		//cout<<"\nmin ="<<matrix[minRow][minCol];
		//cout<<"\ncost assign="<<demand[minCol];
		initialSolution[minRow][minCol]=(matrix[minRow][minCol] * demand[minCol]);
		capacity[minRow]=capacity[minRow]-demand[minCol];
		demand[minCol]=0;
	}
	else
	{
		//cout<<"\nmin ="<<matrix[minRow][minCol];
		//cout<<"\ncost assign="<<capacity[minRow];

		initialSolution[minRow][minCol]=(matrix[minRow][minCol] * capacity[minRow]);
		demand[minCol]=demand[minCol]-capacity[minRow];
		capacity[minRow]=0;
	}*/