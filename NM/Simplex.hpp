class Simplex
{

public:
	int row, column;
	double **simplexMatrix, *ratio, *Cj, *Zj, *Cb, *Zj_Cj, *Xb;

	double *demand, *capacity;


	Simplex();
	void simplexOperation();
	//void calculatingRatio(int k, double **simplexMatrix, double *ratio);
	int calculatingRatio(int k);
	void display();
	void reduceRow(int m, int k);


	//Transportation

	//void northWestCorner();
	//void LeastCostMethod();
	//void displayMatrix(double **temp);




};
