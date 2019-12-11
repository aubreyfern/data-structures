#include<iostream>
#include <ctime>
#include <cstdio>
#include "time.h"
#include "checkFile.h"
#include "BubbleSort.h"
#include "InsertionSort.h"
#include "QuickSort.h"
#include "ShellSort.h"

using namespace std;


int main(int argc, char* argv[])
{
	string fileName; 
	//if filename was entered in command line
	if(argc>1)
	{
		CheckFile f(argv[1]);
		f.fileExists();
		fileName  = f.getFile(); 
	}
	//if not prompt for file
	else {
		CheckFile f; 
		fileName = f.getFile();
	}

	cout<<"SORTING TIMES:"<<endl;

	//bubble sort
	std::clock_t start;
	start =  clock(); 
	BubbleSort bs(fileName); 
	double duration = (std::clock()-start)/(double)CLOCKS_PER_SEC; 
	cout<<"Bubble Sort:"<<duration<<endl;

	//insert sort
	start = std::clock();  
	InsertionSort is(fileName); 
	duration = (std::clock()-start)/(double)CLOCKS_PER_SEC; 
	cout<<"Insertion Sort:"<<duration<<endl;
	
	//quick sort
	start = clock(); 
	QuickSort qs(fileName); 
	duration = (std::clock()-start)/(double)CLOCKS_PER_SEC; 
	cout<<"Quick Sort:"<<duration<<endl;

	//selection sort
	start = clock(); 
	ShellSort ss(fileName);
	duration = (std::clock()-start)/(double)CLOCKS_PER_SEC; 
	cout<<"Shell Sort:"<<duration<<endl;
} 
