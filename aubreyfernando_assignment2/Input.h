#include <iostream>
#include <string>
using namespace std; 
class Input
{
public:
	Input(); 
    void makeMap();
	~Input(); 

	void Choice(); 
	void ReadFile(); 
	void GetMapData(); 
	int CorrectInput();
	double CorrectDensity();  
	char** GenerateMapFromFile(); 
	void GenerateMapFromInput(); 


	string getFile(); 
	int getRow(); 
	int getColumns(); 
	double getDensity(); 
private:
	string fileName; 
	int rows; 
	int columns; 
	double density; 
	char** theArray;


}; 
