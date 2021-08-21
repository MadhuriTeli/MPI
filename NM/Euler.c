#include<stdio.h>

float fun(float x,float y)
{

    return x+y;

}
 int main()
{
    float x0,y0,x,y,h,xn;
    printf("\nEnter x0,y0,h,xn: ");
    scanf("%f%f%f%f",&x0,&y0,&h,&xn);
    x=x0;
    y=y0;
    printf("\n  x\t\t  y\n");
    while(x<xn)
    {
        y=y+(h*fun(x,y));
        x=x+h;
     
         printf("%f\t%f\n",x,y);
    }
    
    return 0;
}







 















/*double function(double a, double b)
{
	return x+y;
}

int main()
{
	double x, y, h, y1, x1, x0;
	printf("\n Enter the value of x:");
	scanf("%f",&x);
	printf("\n Enter the value of x0:");
	scanf("%f",&x0);
	printf("\n Enter the value of y:");
	scanf("%f",&y);
	printf("\n Enter step size:");
	scanf("%f",&h);
	
	y1=y;
	x1=x0;
	while(1)
	{
		if(x1>x)
		{
			return 0;
		}
	}

}*/
