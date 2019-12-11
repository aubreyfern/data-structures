#include "ListQueue.h"
#include "Student.h"
#include <string>
#include <iostream>
#include <string>
using namespace std;
/*Simulation.cpp takes in the file name from the main and reads taking in number and then begins to 
reads in the time or student time infor using a switch statement. Students are added to queue with 
the time they arrive and time they need stored with the students. Sim() then runs the simulation 
until the queue is empty. Students are dequeued according to amount of windows open. Once dequeued 
the amount of time they need is decremented and windows open are incremented keeping track of idle time, per clock tick.
Once all the students are dequeued the statistics are calculated and printed out
*/

class Simulation
{
public:
	Simulation(); 
	Simulation(string fileName);
	~Simulation(); 

	void readInFile(); 
	void sim();

	Queue<Student> *theQueue; 
	string file;
	int numWindows; 
	int totalStudents; 
	int timeArrived;

	int *windowsOpen;
	int *studentWait; 
	int *idleTime;  

	int clock;
	int type; 

	int emptyWin; 

	float Mean(int arr[], int total);
	int LongestTime(int arr[], int size);
	int OverTime(int arr[], int total, int time);
	double Median(int arr[],int total);
	
	void IncAndDecTimes(); 

	void printWait(); 
	void printIdle();
	void printWindowsOpen();

}; 