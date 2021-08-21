#include<iostream>
#include"ODE.hpp"
 using namespace std;

 int main()
 {
 	ODE o1;

 	//o1.Euler();
 	//o1.Taylors();
   //o1.TaylorNew();
 	//o1.RungeKulta_2();
 	//o1.RungeKulta_3();
 	//o1.RungeKulta_4();
 	//o1.Adams_Bashforth_1();
 	//o1.Adams_Bashforth_2();
 	o1.Adams_Bashforth_3();

	return 0;
	
 }