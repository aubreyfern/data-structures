#include <iostream>
#include <string>
using namespace std; 

class BubbleSort
{
public:
	string fileName; 
	int size; 
	double *theArray; 

	BubbleSort(); 
	BubbleSort(string file); 
	~BubbleSort(); 
	void readInFile(); 
	void Sort(); 
	void Print(); 
}; 
