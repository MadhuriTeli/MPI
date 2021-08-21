#include<stdio.h>

int num[25];

void quickSort(int number[25],int p, int first, int last)
{
	int i,j , pivot, temp, m, n;
	if(first<last)
	{
		//pivot=first;
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

		/*while(i<j)
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
		
				temp=number[pivot];
				number[pivot]=number[j];
				number[j]=temp;*/
		
	}

}

int main()
{

	int i, count, number[25], pivot, flag=0, pivotIndex, index;
	printf("\nhow many elements do you want in array:");
	scanf("\n%d", &count);

	printf("\nEnter %d elemets in array:", count);
	for(i=0;i<count;++i)
	{
		scanf("%d", &number[i]);
	}
	
	printf("\nEnter the Pivot element:");
	scanf("\n%d", &pivot);

	for(i=0;i<count;++i)
	{
		if(pivot==number[i])
		{
			//flag++;
			pivotIndex=i;
			
		}
	}
	
	/*if(flag==0)
	{
		printf("\nInvalid pivot value.\n");
		return 0;
	}*/

	quickSort(number, pivot, 0, count-1);

	printf("\n sorted elements :\n");
	for(i=0;i<count;++i)
	{
		/*if(number[i]==number[pivotIndex])
		{
			flag=i;
		}*/
		printf("%d\t", num[i]);
		
		
	}
	printf("\nIndex of pivot is %d :\n",flag);

	

return 0;
}
