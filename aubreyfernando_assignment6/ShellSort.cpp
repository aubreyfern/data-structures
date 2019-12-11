#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "math.h"
#include "ShellSort.h"
using namespace std; 

ShellSort::ShellSort()
{

}

ShellSort::ShellSort(string file)
{
	fileName = file; 
	readInFile(); 
}

ShellSort::~ShellSort()
{
	delete[] theArray; 
}

void ShellSort::readInFile()
{
	ifstream infile(fileName.c_str());
	if(infile.is_open()&&infile.good())
	{
		string lines; 
		getline(infile,lines); 
		size = atoi(lines.c_str()); 
		if(size==0)
		{
			cout<<"ERROR:File has no elements"<<endl; 
			throw exception(); 
		}
		theArray = new double[size]; 
		for (int i=0; i<size; ++i)
		{
			getline(infile,lines); 
			theArray[i] = atof(lines.c_str()); 
		}
		int exp = sqrt(size);
		if(exp%2==1)
		{
			exp = exp+4; 
		} 
		Sort(size); 
	}
	
	infile.close(); 
}

void ShellSort::Print()
{
	cout<<"CountSort:"<<endl;
	for(int i=0; i<size;++i)
	{
		cout<<theArray[i]<<endl; 
	}
}

void ShellSort::Sort(int n)
{

	for (int gap = n/2; gap > 0; gap /= 2)
	{
		 for (int i = gap; i < n; i += 1)
		 {
		 	 double temp = theArray[i];
		 	 int j;            
            for (j = i; j >= gap && theArray[j - gap] > temp; j -= gap)
                theArray[j] = theArray[j - gap];
             theArray[j] = temp;
		 }
	}

}
