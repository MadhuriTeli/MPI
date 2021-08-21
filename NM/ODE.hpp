class ODE
{ 
 
	public : 
	float **m,*f; //x for Taylor
		double x0,y0,x,y,h,xn, k1, k2, k3, k4;


	int n;
	double fun(double x, double y);
	void Euler();
	
	void Taylors();

	void TaylorNew();
	float deri();
	float value(float x);
	int fact(int i);
	float sum(float h);

	void RungeKulta_2();
	void RungeKulta_3();
	void RungeKulta_4();

	double derivative(double x, double y);
	void Adams_Bashforth_1();
	void Adams_Bashforth_2();
	void Adams_Bashforth_3();

	void Nystrom_2();
	void Nystrom_3();

};
















































/*float value(float x);
	float sum(float h);
	float deri();
	int fact(int i);
	int Taylor();*/