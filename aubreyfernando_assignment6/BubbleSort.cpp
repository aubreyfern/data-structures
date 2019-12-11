#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include "BubbleSort.h"
using namespace std; 

BubbleSort::BubbleSort()
{

}

BubbleSort::BubbleSort(string file)
{
	fileName = file; 
	readInFile(); 
}

BubbleSort::~BubbleSort()
{
	delete[] theArray; 
}

void BubbleSort::readInFile()
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
		//Print(); 
	}
	infile.close(); 
}


void BubbleSort::Sort()
{
	for(int i=0; i<size-1; ++i)
	{
		double temp=0; 
		for(int j=0;j<size-i-1;++j)
		{
			if(theArray[j]>theArray[j+1])
			{
				temp = theArray[j+1]; 
				theArray[j+1] = theArray[j]; 
				theArray[j]=temp; 
			}
		}
	}
}


void BubbleSort::Print()
{
	cout<<"BubbleSort:"<<endl;
	for(int i=0; i<size;++i)
	{
		cout<<theArray[i]<<endl; 
	}
}