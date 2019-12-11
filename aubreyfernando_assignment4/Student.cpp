#include <iostream>
#include "Student.h"
using namespace std; 

//initialize new student 
Student::Student()
{
	timeNeeded = 0; 
	timeArrived=0; 
}

//initialize new student with specificed time of arrival
//and time they need
Student::Student(int ta, int tn)
{
	timeNeeded = tn;
	timeArrived = ta;

}

Student::~Student()
{

}

