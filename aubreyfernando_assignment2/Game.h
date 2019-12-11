#include <iostream>
#include <fstream>
using namespace std; 
class Game
{
public:
	Game(); 
	~Game(); 

	void getAll(char** array,int r, int c);
	void MakeMap2(); 
	void Navigate(); 

	void GameSimulation(char mode, char printType);

	void CollectNewArrayClassic(); 
	void CollectNewArrayMirror();
	void CollectNewArrayDonut(); 

	void SwapArrays(); 
	char NewVal(int neighbors,char current);
 
	void PrintPause();
	void Print();
	string PrintFile();

	void CheckCorners(); 
	void CheckMiddleTopBottom(); 
	void CheckMiddleSides(); 
	void CheckMiddle(); 

	void CheckCornersMirror(); 
	void CheckMiddleTopBottomMirror();
	void CheckMiddleSidesMirror(); 

	void CheckCornersDonut(); 
	void CheckMiddleTopBottomDonut();
	void CheckMiddleSidesDonut();


	
private:
	char** theArray; 
	char** newArray;
	int rows; 
	int columns;
	int genCount; 
	ofstream outFile;


};
