#include <iostream>
#include <string>
#include <fstream>
#include "fileCheck.h"

//if no file passed ask for one
fileCheck::fileCheck()
{
	requestFile(); 
}

fileCheck::fileCheck(string fileN)
{
	fileName = fileN; 
}

fileCheck::~fileCheck()
{

}

//check if file can open 
void fileCheck::fileExists()
{
	ifstream file; 
	file.open(fileName.c_str()); 
	if(file.fail())
	{
		cout<<"File doesn't exist!!"<<endl; 
		requestFile(); 
	}
	else{
		file.close();
	}
}

//ask for file 
void fileCheck::requestFile()
{
	cout<<"Enter in a file name: "<<endl;
	cin>>fileName; 
	fileExists(); 
}

//return file name
string fileCheck::getFileName()
{
	return fileName; 
}
