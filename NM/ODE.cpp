#include<iostream>
#include"ODE.hpp"
#include<math.h> 
#include<stdlib.h> 
#include <fstream>
using namespace std;

void ODE::Euler()
{
	//double x0,y0,x,y,h,xn;
   	cout<<"\nEnter x0,y0,h,xn: ";
    cin>>x0>>y0>>h>>xn;
    x=x0;
    y=y0;
    cout<<"\nx\t\ty\n";
    while(x<xn)
    {
        y=y+(h*fun(x,y));
        x=x+h;
        cout<<x<<"\t\t"<<y<<"\n";
    }

}

double ODE:: fun(double x, double y)
{
	 return x+y;
}

void ODE::Taylors()
{
	//float x0, y0, h, xn;
	cout<<"\nTaylors solution is:\n";
	cout<<"Enter x0 y0 h Xn:\n";
	cin>>x0>>y0>>h>>xn;
	 cout<<x0<<"\t\t"<<y0<<"\n";

    while(x0<xn)
    {
        y0=y0+h*fun(x0,y0)+2*h*h*fun(x0,y0);
        x0=x0+h;
        cout<<x0<<"\t\t"<<y0<<endl;
    }
}

void ODE :: TaylorNew()
{

	int i,p; 
	float h;
	cout<<"Enter the Degree of the Equation"; 
	cin>>n;

	//m=(float**)malloc((n+1)*2*sizeof(float*)); 
	//m= new float*[(n+1)*2];
		m= new float*[(n+1)];

	for(i=0; i<(n+1); i++)
	{ 
        //m[i]=new float[(n+1)*2];
        m[i]=new float[(n+1)];
	}
	f= new float[n];
	cout<<"Enter the value of coefficient\n"; 
	p=n; 

	for(i=0;i<=n;++i) 
	{ 
		cin>>m[i][0];
		m[i][1]=p; 
		p--; 
	}

	
	cout<<"Enter value of x\n"; 
	cin>>x;


	cout<<"Enter value of h\n"; 
	cin>>h; 

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
		//printf("\nf%d(x)=%f",i,f[i]);
		cout<<"\nf"<<i<<"(x)"<<f[i];
	} 
	cout<<"\n\nResult=f(x+h)="<<sum(h); 

}

float ODE:: deri()
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
float ODE:: value(float x)
{
	int i; 
	float v=0; 
	for(i=0;i<=n;i++) 
	{ 
		v=v+m[i][0]*pow(x,m[i][1]); 
	} 
	return v; 
}

int ODE:: fact(int i)
{
	int j,fact=1; 
	for(j=i;j>0;j--) 
	{ 
		fact=fact*j; 
	} 
	return fact;
}

float ODE:: sum(float h)
{
	int i; 
	float s=0; 
	for(i=0;i<=n;i++) 
	{ 
		s=s+pow(h,i)*f[i]/fact(i); 
	} 
	return s; 
}



void ODE::RungeKulta_2()
{
	//double x0,y0,x,y,h,xn, k1, k2;
   	cout<<"\nEnter x0,y0,h,xn: ";
    cin>>x0>>y0>>h>>xn;
    x=x0;
    y=y0;
    cout<<"\nx\t\ty\n";
    while(x<xn)
    {

    	k1=h*fun(x,y);
    	k2=h*fun((x+h/2), (y+k1/2));
    	y=y+k2;
		x=x+h;
		cout<<x<<"\t\t"<<y<<"\n";
    	
    }

}


void ODE::RungeKulta_3()
{
	//double x0,y0,x,y,h,xn, k1, k2, k3;
   	cout<<"\nEnter x0,y0,h,xn: ";
    cin>>x0>>y0>>h>>xn;
    x=x0;
    y=y0;
    cout<<"\nx\t\ty\n";
    while(x<xn)
    {
      
    	k1=h*fun(x,y);
    	k2=h*fun((x+h/2), (y+k1/2));
    	k3=h*fun((x+h), (y-k1+(2*k2)));
    	y=y+(k1+(4*k2)+k3)/6;
		x=x+h;
		cout<<x<<"\t\t"<<y<<"\n";
    	
    }
}

void ODE::RungeKulta_4()
{
   	cout<<"\nEnter x0,y0,h,xn: ";
    cin>>x0>>y0>>h>>xn;
    x=x0;
    y=y0;
    cout<<"\nx\t\ty\n";
    while(x<xn)
    {
      
    	k1=h*fun(x,y);
    	k2=h*fun((x+h/3), (y+k1/3));
    	k3=h*fun((x+(2*h)/3), (y-(k1+k2)/3));
    	k4=h*fun((x+h), (y+k1-k2+k3));
    	y=y+(k1+(3*k2)+(3*k3)+k4)/8;
		x=x+h;
		cout<<x<<"\t\t"<<y<<"\n";
    	
    }
}

double ODE:: derivative(double x, double y)
{
	 	 //return (x*x)-y;
	return((x+y)/2);

}
void ODE::Adams_Bashforth_1()
{
	//double x0,y0,x,y,h,xn;
   	cout<<"\nEnter x0,y0,h,xn: ";
    cin>>x0>>y0>>h>>xn;
    x=x0;
    y=y0;
    cout<<"\nx\t\ty\n";
    while(x<xn)
    {
        y=y+(h*derivative(x,y));
        x=x+h;
        cout<<x<<"\t\t"<<y<<"\n";
    }
}

void ODE::Adams_Bashforth_2()
{
	//double x0,y0,x,y,h,xn;
	double y[2], x[2];
   	//cout<<"\nEnter x0,y0, x1, y1,h,xn: ";
    //cin>>x0>>y0>>h>>xn;
    for(int i=0; i<2;++i)
    {
    	cout<<"\nEnter x["<<i<<"] and y["<<i<<"]";
    	cin>>x[i]>>y[i];
    }
    cout<<"\nEnter h,xn: ";
    cin>>h>>xn;

    this->x=x[1];
    this->y=y[1];
    cout<<"\nx\t\ty\n";
    while((this->x)<xn)
    {
        this->y=(this->y)+(h/2)*((3*derivative(this->x,this->y))- derivative(x[0],y[0]));
        y[0]=y[1];
		x[0]=x[1];
		y[1]=this->y;
		this->x+=h;
	        cout<<this->x<<"\t\t"<<this->y<<"\n";
    }
}

void ODE::Adams_Bashforth_3()
{
	//double x0,y0,x,y,h,xn;
	double y[3], x[3];
   	//cout<<"\nEnter x0,y0, x1, y1,h,xn: ";
    //cin>>x0>>y0>>h>>xn;
    for(int i=0; i<3;++i)
    {
    	cout<<"\nEnter x["<<i<<"] and y["<<i<<"]";
    	cin>>x[i]>>y[i];
    }
    cout<<"\nEnter h,xn: ";
    cin>>h>>xn;

    this->x=x[2];
    this->y=y[2];
    cout<<"\nx\t\ty\n";
    while((this->x)<xn)
    {
        this->y=(this->y)+(h/12)*((23*derivative(this->x,this->y))-(16*derivative(x[1],y[1]))-(5*derivative(x[0],y[0])));
        y[0]=y[1];
		x[0]=x[1];

		y[1]=y[2];
		x[1]=x[2];
		y[2]=this->y;

		this->x+=h;
	    cout<<this->x<<"\t\t"<<this->y<<"\n";
    }
}


// belowed two function not working correctly
void ODE::void Nystrom_2()
{
	double y[2], x[2];
    for(int i=0; i<2;++i)
    {
    	cout<<"\nEnter x["<<i<<"] and y["<<i<<"]";
    	cin>>x[i]>>y[i];
    }
    cout<<"\nEnter h,xn: ";
    cin>>h>>xn;

    this->x=x[0];
    this->y=y[0];
    cout<<"\nx\t\ty\n";
    while((this->x)<xn)
    {
        this->y=(this->y)+ (2*h*y[1]);
        this->y=y[1];
		this->x=x[1];
		y[1]=this->y;
		this->x+=h;
	    cout<<this->x<<"\t\t"<<this->y<<"\n";
    }
}

void ODE::void Nystrom_2()
{
	double y[3], x[3];
   	//cout<<"\nEnter x0,y0, x1, y1,h,xn: ";
    //cin>>x0>>y0>>h>>xn;
    for(int i=0; i<3;++i)
    {
    	cout<<"\nEnter x["<<i<<"] and y["<<i<<"]";
    	cin>>x[i]>>y[i];
    }
    cout<<"\nEnter h,xn: ";
    cin>>h>>xn;

    this->x=x[1];
    this->y=y[1];
    cout<<"\nx\t\ty\n";
    while((this->x)<xn)
    {
        this->y=(this->y)+(h/3)*((7*derivative(x[2],y[2]))-(2*derivative(this->x,this->y))-(derivative(x[0],y[0])));
        this->y[0]=y[1];
		x[0]=x[1];

		y[1]=y[2];
		x[1]=x[2];
		y[2]=this->y;

		this->x+=h;
	    cout<<this->x<<"\t\t"<<this->y<<"\n";
}









































/*float ODE:: value(float x)
{
	int i; 
	float v=0; 
	for(i=0;i<=n;i++) 
	{ 
		v=v+m[i][0]*pow(x,m[i][1]); 
	} 
	return v; 
}
float ODE:: sum(float h)
{
	int i; 
	float s=0; 
	for(i=0;i<=n;i++) 
	{ 
		s=s+pow(h,i)*f[i]/fact(i); 
	} 
	return s; 
}
float ODE:: deri()
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
int ODE:: fact(int i)
{
	int j,fact=1; 
	for(j=i;j>0;j--) 
	{ 
		fact=fact*j; 
	} 
	return fact;
}
int ODE:: Taylor()
{
	int i,p; 
	float h;
	cout<<"Enter the Degree of the Equation"; 
	cin>>n;

	//m=(float**)malloc((n+1)*2*sizeof(float*)); 
	//m= new float*[(n+1)*2];
		m= new float*[(n+1)];

	for(i=0; i<(n+1); i++)
	{ 
        //m[i]=new float[(n+1)*2];
        m[i]=new float[(n+1)];
	}
	f= new float[n];
	cout<<"Enter the value of coefficient\n"; 
	p=n; 

	for(i=0;i<=n;++i) 
	{ 
		cin>>m[i][0];
		m[i][1]=p; 
		p--; 
	}

	
	cout<<"Enter value of x\n"; 
	cin>>x;


	cout<<"Enter value of h\n"; 
	cin>>h; 

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
		//printf("\nf%d(x)=%f",i,f[i]);
		cout<<"\nf"<<i<<"(x)"<<f[i];
	} 

	cout<<"\n\nResult=f(x+h)="<<sum(h); 

}*/