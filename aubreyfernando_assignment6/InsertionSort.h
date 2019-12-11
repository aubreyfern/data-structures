#include <iostream>
using namespace std; 
class InsertionSort
{
public:
	string fileName; 
	double *theArray; 
	int size; 

	InsertionSort(); 
	InsertionSort(string file); 
	~InsertionSort(); 

	void readInFile(); 
	void Sort(); 
	void Print(); 


}; 