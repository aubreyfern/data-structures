#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "checkFile.h"
using namespace std;


//default constructor
CheckFile::CheckFile()
{
	requestFile();
}

//overload constructor
CheckFile::CheckFile(string file)
{
	fileName = file; 
}

//destructor
CheckFile::~CheckFile()
{

}

//check if file entered exists, if doesn't call requestFile
void CheckFile:: fileExists()
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

//prompt user to enter a file, fileExists is called
void CheckFile::requestFile()
{
	cout<<"Enter in a file name: "<<endl;
	cin>>fileName; 
	fileExists(); 
}

//return name of file 
string CheckFile::getFile()
{
	return fileName;
}


