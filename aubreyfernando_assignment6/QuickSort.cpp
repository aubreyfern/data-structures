#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "QuickSort.h"
using namespace std; 

QuickSort::QuickSort()
{
}

QuickSort::QuickSort(string file)
{
	fileName =  file; 
	readInFile(); 
}

QuickSort::~QuickSort()
{
	delete[] theArray; 
}
void QuickSort::readInFile()
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
	
		Sort(0,size-1); 
	}
	infile.close(); 

}

void QuickSort::Sort(int left, int right)
{
	int i = left; 
	int j = right; 
	double temp; 
	int pivot = theArray[(left+right)/2]; 

	while(i<=j)
	{
		while((int)theArray[i]<pivot)
			i++; 
		while((int)theArray[j]>pivot)
			j--; 
		if(i<=j)
		{
			temp = theArray[i];
			theArray[i] = theArray[j]; 
			theArray[j] = temp; 
			i++; 
			j--; 
		}
	}

	if(left<j)
		Sort(left,j); 
	if(i<right)
		Sort(i,right); 
}


void QuickSort::Print()
{
	cout<<"QuickSort:"<<endl;
	for(int i=0; i<size;++i)
	{
		cout<<theArray[i]<<endl; 
	}
}