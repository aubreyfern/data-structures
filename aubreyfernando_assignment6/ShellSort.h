#include <iostream>
#include <string>
using namespace std; 
class ShellSort
{
public:
	string fileName; 
	double *theArray; 
	int size; 
	ShellSort(); 
	ShellSort(string file); 
	~ShellSort(); 

	void readInFile(); 
	void Sort(int n); 
	void Print(); 
};