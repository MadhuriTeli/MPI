#include<stdio.h>

void quickSort(int number[25], int first, int last)
{
	int i,j,pivot, temp;
	if(first<last)
	{
		pivot=first;
		i=first;
		j=last;

		while(i<j)
		{
			while(number[i]<= number[pivot] && i<last)
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
	
		quickSort(number, first, j-1);
		quickSort(number, j+1, last);
	}

}

int main()
{

	int i, count, number[25];
	printf("\nhow many elements do you want in array:");
	scanf("\n%d", &count);

	printf("\nEnter %d elemets in array:", count);
	for(i=0;i<count;++i)
	{
		scanf("%d", &number[i]);
	}
	
	quickSort(number, 0, count-1);

	printf("\n sorted elements :\n");
	for(i=0;i<count;++i)
	{
		printf("%d\t", number[i]);
	}

	

return 0;
}
