#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <ctype.h>
#include "Input.h"
using namespace std; 

/*
Input.cpp prompts user to enter in a file or generate a cell map.
If they want to enter a file they are prompted for the name of file and the file is read in first 
get dimensions of the array, the array is then made using MakeMap() and then the file is read in again 
to read in the contents of the array and store it in the array made. 
If the user wants to generate a map they are asked to enter in the dimensions for rows
and columns. Correct Input() is used if the entry is not an int and the user is prompted to enter
in a number again. CorrectDensity() does the same thing.
*/


Input::Input() 
{
	//begin with choice
	Input::Choice();
}


Input::~Input()
{

}

//prompts for user input if they want to enter or generate a file
void Input::Choice()
{
	char choice;
	
	cout<<"Would you like to (a)read in a file or (b)generate a cell map?"<<endl; 
	cin>>choice; 
	if((choice=='a')||(choice=='A'))
	{
		Input::ReadFile(); 
	}
	else if((choice=='b')||(choice=='B'))
	{
		Input::GetMapData(); 
	}

	else
	{
		Input::Choice(); 
	}

}

//Reads in amount of rows and columns from file
void Input::ReadFile()
{
	string line; 
	int countLines=0; 
	cout<<"Enter in the name of your file cell map:"<<endl;
	cin>>fileName; 


	ifstream infile(fileName.c_str());
	if((infile.is_open())&&(infile.good()))
	{
		while(getline(infile,line))
		{
			countLines++; 
			if(countLines==1)
			{
				rows = atoi(line.c_str()); 	
			}
			else if(countLines==2)
			{
				columns =atoi(line.c_str()); 
			}
		}
	}
	else{
		Input::Choice(); 
	}
	infile.close(); 
}


int Input::CorrectInput()
{
	int integer; 

	cout<<"Invalid Entry.Please Enter a Number Greater than 1:"<<endl; 
	cin>>integer; 
	if(cin.good())
	{
		if(integer>1)
		{
			return integer; 
		}
		//return integer; 
		else{
			cin.clear();
			CorrectInput();
		}
	}
	else{
		cin.clear();
		cin.ignore(1,' ');
		CorrectInput(); 
	}
}

double Input::CorrectDensity()
{
	cout<<"Enter a density (decimal value 0<x<=1):"<<endl;
	cin>>density; 
	if(cin.good())
	{
		if((density>1)||(density==0)||(density<0))
		{
			cout<<"Invalid number."<<endl;
			cin.clear();
			cin.ignore(1,' ');
			CorrectDensity(); 
		}
		else{
			return density; 
		}
	}

	else{
		cout<<"Invalid Entry."<<endl;
		cin.clear();
		cin.ignore(1,' ');; 
		CorrectDensity(); 
	}
}
//if user wants to generate map prompt for dimensions and density
void Input::GetMapData()
{
	cout<<"Enter an amount of rows:"<<endl; 
	cin>>rows;
	if((!(cin.good())))
	{
		cin.clear();
		cin.ignore(1,' ');
		rows = CorrectInput(); 
	}
	else if(rows<2)
	{
		cin.clear();
		rows=CorrectInput();
	}
	cout<<"Enter an amount of columns:"<<endl; 
	cin>>columns; 
	if((!(cin.good())))
	{
		cin.clear();
		cin.ignore(1,' ');
		columns = CorrectInput(); 
	}
	else if(columns<2)
	{
		cin.clear();
		columns=CorrectInput();	
	}

	density = CorrectDensity(); 
	
}

//set up grid 
void Input::makeMap()
{
	theArray = new char*[rows]; 
	for(int i=0; i<rows;++i)
	{
		theArray[i]= new char[columns]; 
	}

	for(int i=0; i<rows; ++i)
	{
		for(int j=0;j<columns;++j)
		{
			theArray[i][j]='-';
		}
	}
}

//read in file and make array from it

 char** Input::GenerateMapFromFile()
{
	int countLines=0; 
	string line; 
	ifstream infile(fileName.c_str());
	if((infile.is_open())&&(infile.good()))
	{
		while(getline(infile,line))
		{
		countLines++; 
			if(countLines>2)
			{
				for(int i=0; i<rows;++i)
				{
					if((line[i]=='X')||(line[i]=='x'))
					{

						theArray[countLines-3][i]='x';
					}
					else{
						theArray[countLines-3][i]='-';
					}
				}
			}
		}
	}

	infile.close(); 
	return theArray; 
}

void Input::GenerateMapFromInput()
{
	int total = rows*columns; 
	int cellXProb = density*total; 
	for(int i=0; i<rows; ++i)
	{
		for(int j=0; j<columns;++j)
		{
			//generate random number with ranges
			int num  = rand()%total+1; 
			if(num<=cellXProb)
			{
				theArray[i][j]='x'; 
			}
		}
	}

}

string Input::getFile()
{
	return fileName; 
}

int Input::getRow()
{
	return rows; 
}

int Input::getColumns()
{
	return columns; 
}

double Input::getDensity()
{
	return density; 
}


