class Transportation
{
public:
	double *demand, *capacity, **matrix, **initialSolution;
	int row, column;
	double cost, min;
	int occupiedCells, maxOccupiedCells;
	//int minCol, minRow;

	Transportation();

	void northWestCorner();

	void leastCost();
	void VAM();
		int checkingForAllZero();
		void initialSolutionCalculation(int c, int r);
	void modi();
	
};