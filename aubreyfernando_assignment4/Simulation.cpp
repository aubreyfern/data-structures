#include  "Simulation.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std; 
Simulation::Simulation()
{

}

//set global variables, make new queue, call to read the file
Simulation::Simulation(string fileName)
{
	file = fileName; 
	numWindows = 0; 
	totalStudents = 0; 
	type = 1;
	theQueue = new Queue<Student>(); 
	timeArrived=0;
	clock =0; 
	emptyWin=0; 
	readInFile();
	
	
}

//delete the arrays
Simulation::~Simulation()
{
	delete[] windowsOpen; 
	delete[] studentWait;
	delete[] idleTime;

}

//reads in the file entered
void Simulation::readInFile()
{
	ifstream infile(file.c_str()); 
	if((infile.is_open())&&(infile.good()))
	{ 
		string lines; 
		getline(infile,lines); 

		//first line is number of windows
		numWindows = atoi(lines.c_str()); 

		//if number of windows is 0 exit
		if(numWindows==0)
		{
			cout<<"ERROR: Number of Windows cannot be 0"<<endl;
			throw exception();
		}
		
		emptyWin = numWindows; 
 
		//helps keep track of decrementing student time needed
		windowsOpen = new int[numWindows]; 
		for(int i=0; i<numWindows; ++i)
		{ 
			windowsOpen[i] = 0; 
		}

		//read til the end of the file
		while(getline(infile,lines))
		{
			switch(type)
			{
				//read in only time students enter
				case(1):
				{
					timeArrived = atoi(lines.c_str()); 
					type = 2; 
					break;

				}

				//read in student info
				case(2):
				{
					//how many students enter at specific time
					int numStudentsAtTime = atoi(lines.c_str()); 
					totalStudents+=numStudentsAtTime;

					//read in timeNeeded and add students to queue
					for(int i=0; i<numStudentsAtTime; ++i)
					{
						//check if line is 
						getline(infile,lines);

						Student s = Student(timeArrived,atoi(lines.c_str()));
						theQueue->enQueue(s); 
					}
					type = 1;
					break; 
				}
			}			
			
		}

		//array keeping track student wait times
		studentWait = new int[totalStudents]; 
		for(int i=0; i<totalStudents; ++i)
		{
			studentWait[i]=0; 
		}

		//array keeping track of window idle time
		idleTime = new int[numWindows]; 
		for(int i=0; i<numWindows; ++i)
		{
			idleTime[i]=0; 
		}
	}

	infile.close();
	sim();
}

//goes through queue and tracks info using arrays
void Simulation::sim()
{
	int studentsAtWindow=-1; 
	bool complete = false; 
	while(complete==false)
	{
		while(!theQueue->isEmpty())
		{
			{
			//only dequeue if windows are available
			if(emptyWin>0)
			{
				for(int i=0; i<numWindows;++i)
				{
					//if there are elements in queue, windows are open and students arrive at their time
					if((theQueue->getSize()!=0)&&(windowsOpen[i]==0)&&(theQueue->getFront().timeArrived<=clock))
					{
						Student studTemp = theQueue->deQueue(); 
						windowsOpen[i]=studTemp.timeNeeded+1; 
						emptyWin--; 
						studentsAtWindow++; 
						if(clock!=0)
							studentWait[studentsAtWindow]=(clock- studTemp.timeArrived); 
					}
				}
			}
		}
		IncAndDecTimes();
		clock++;
		}
		//to complete idle times 
		IncAndDecTimes();

		if(emptyWin==numWindows)
			complete = true;
	}

	//printWait();
	//printIdle();
	//printWindowsOpen();


	//print statistics
	cout<<endl<<"Statistics"<<endl;

	cout<<"Mean Student Wait Time:"<<Mean(studentWait,totalStudents)<<endl;
	cout<<"Median Student Wait Time:"<<Median(studentWait,totalStudents)<<endl;
	cout<<"Longest Student Wait Time:"<<LongestTime(studentWait,totalStudents)<<endl; 
	cout<<"Students Waiting Over 10 Mins:"<<OverTime(studentWait,totalStudents,10)<<endl; 
	cout<<endl;
	cout<<"Mean Window Idle Time:"<<Mean(idleTime,numWindows)<<endl;
	cout<<"Longest Idle Time:"<<LongestTime(idleTime,numWindows)<<endl;
	cout<<"Number of Windows Idle Over 5 Mins:"<<OverTime(idleTime,numWindows,5)<<endl;
}

//increments idle windows if they are open 
//decrements window for amount of time students are there
void Simulation::IncAndDecTimes()
{
	for(int i=0; i<numWindows; ++i)
	{
		if(windowsOpen[i]!=0)
		{
			windowsOpen[i]--;
			if(windowsOpen[i]==0)
			{
				emptyWin++; 
			}
		}
		else{
			idleTime[i]++; 
		}
	}
}

//calcualte the mean using array and size 
float Simulation::Mean(int arr[], int total)
{
	float time=0; 
	for(int i=0; i<total; ++i)
	{
		time+=arr[i];
	}
	float tempMean=0; 
	tempMean = time/total; 
	return tempMean; 
}

//calcualte longest time 
int Simulation::LongestTime(int arr[], int size)
{
	int longest=0; 
	for(int i=0;i<size; ++i)
	{
		if(longest<arr[i])
		{
			longest = arr[i]; 
		}

	}
	return longest; 
}

//calcualte # of something over a certain time
int Simulation::OverTime(int arr[], int total, int time)
{
	int count=0; 
	for(int i=0; i<total; ++i)
	{
		if(time<=arr[i])
		{
			count++; 
		}
	}
	return count; 
}

//calcualte median
double Simulation::Median(int arr[],int total)
{
	int temp; 
	int temp2; 
	double median=0; 
	sort(arr, arr+total); 

	//if odd
	if(total%2==1)
	{
		temp = (total/2)+1; 
		median = arr[temp-1]; 

	}
	//if even
	else{
		temp = (total/2); 
		temp2 = (total/2)+1; 
		if(arr[temp2-1]!=0)
			median = ((arr[temp-1])/arr[temp2-1]); 

	}

	return median; 
}


//print arrays ...helps me see whats going on 
void Simulation::printIdle()
{
	cout<<"Idle Times:"<<endl;
	for(int i=0; i<numWindows; ++i)
	{
		cout<<idleTime[i]<<endl;
	}
}

void Simulation::printWindowsOpen()
{
	cout<<"Service Open"<<endl;
	for(int i=0; i<numWindows;++i)
	{
		cout<<windowsOpen[i]<<endl;
	}
}
void Simulation::printWait()
{
	cout<<"WaitTimes:"<<endl;
	for(int i=0; i<totalStudents; ++i)
	{
		cout<<studentWait[i]<<endl;
	}
}

