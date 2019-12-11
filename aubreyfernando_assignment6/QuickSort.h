#include <iostream>
#include <string>
using namespace std; 

class QuickSort
{
public:
	string fileName;
	int size;  
	double *theArray;
	QuickSort(); 
	QuickSort(string file); 
	~QuickSort(); 
	void readInFile();
	void Sort(int left, int right); 
	void Print(); 

};