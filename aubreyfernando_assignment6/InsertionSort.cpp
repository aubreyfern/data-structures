#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "InsertionSort.h"
using namespace std; 

InsertionSort::InsertionSort()
{

}

InsertionSort::InsertionSort(string file)
{
	fileName = file; 
	readInFile(); 
}

InsertionSort::~InsertionSort()
{
	delete[] theArray; 
}

void InsertionSort::readInFile()
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
		Sort(); 
	}
	
	infile.close(); 
}

void InsertionSort::Sort()
{
	for(int j=0; j<size; ++j)
	{
		double temp = theArray[j]; 
		int k = j; 
		while(k>0&&theArray[k-1]>=temp)
		{
			theArray[k]=theArray[k-1]; 
			--k; 
		}
		theArray[k] =temp; 
	}
}

void InsertionSort::Print()
{
	cout<<"InsertionSort:"<<endl;
	for(int i=0; i<size;++i)
	{
		cout<<theArray[i]<<endl; 
	}
}