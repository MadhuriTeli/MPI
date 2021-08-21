#include<stdio.h> 
#include<math.h> 
#include<stdlib.h> 

float **m,x,n,*f; 

float value(float x)
{ 
	int i; 
	float v=0; 
	for(i=0;i<=n;i++) 
	{ 
		v=v+m[i][0]*pow(x,m[i][1]); 
	} 
	return v; 
}  

float sum(float h)
{ 
	int i; 
	float s=0; 
	for(i=0;i<=n;i++) 
	{ 
		s=s+pow(h,i)*f[i]/fact(i); 
	} 
	return s; 
} 

float deri()
{ 
	float v=0; 
	int i,t; 
	for(i=0;i<=n;i++) 
	{ 
		t=m[i][1]; 
		m[i][1]--; 
		m[i][0]=m[i][0]*t; 
		if(m[i][1]<0) 
		break; 
		v=v+m[i][0]*pow(x,m[i][1]); 
	} 
	return v; 
} 

int fact(int i)
{
	int j,fact=1; 
	for(j=i;j>0;j--) 
	{ 
		fact=fact*j; 
	} 
	return fact; 
} 

int main() 
{ 
	int i,p; 
	float h;
	printf("Enter the Degree of the Equation"); 
	scanf("%f",&n); 

	m=(float**)malloc((n+1)*2*sizeof(float*)); 
	for (i=0; i<(n+1); i++)
	{ 
        m[i] = (float *)malloc((n+1)*2* sizeof(float));
	 }
	f=(float*)malloc(n*sizeof(float)); 
	printf("Enter the value of coefficient\n"); 
	p=n; 

	for(i=0;i<=n;++i) 
	{ 
		scanf("%f",&m[i][0]); 
		m[i][1]=p; 
		p--; 
	}

	
	printf("Enter value of x\n"); 
	scanf("%f",&x); 


	printf("Enter value of h\n"); 
	scanf("%f",&h); 

	for(i=0;i<=n;i++) 
	{ 
		if(i==0)
		{
			f[i]=value(x);
		} 
		else
		{
			f[i]=deri(); 
		}
		printf("\nf%d(x)=%f",i,f[i]);
	} 

	printf("\n\nResult=f(x+h)=%f",sum(h)); 

	return 0;
} 


































/*#include<stdio>

double func(dounble x)
{
	return ((3*x^3) + (4*x^2) + (6*x^1)+10));
}

double firstDerivatiove(dounble x)
{
	return ((9*x^2) + (8*x^2) + (6x^1) + (89x^0));
}*/

