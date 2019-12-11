#include <iostream>
#include <cstdlib>
#include "checkFile.h"
#include "checkDelimiters.h"
#include <string>
using namespace std;
int main(int argc, char* argv[])
{  
	//variable declaration
	string fileName; 
	char ans;
	bool repeat = false; 

	//do this first before inquiring to repeat
	do{
		//if file was entered in commandline
		if(argc>1)
		{
			CheckFile f(argv[1]);
			f.fileExists();
			fileName  = f.getFile(); 
		}
		else {
			CheckFile f; 
			fileName = f.getFile();
		}

		//when user wants to check another file 
		if(repeat==true)
		{
			CheckFile f; 
			fileName = f.getFile();
		}

		//syntax checking
		CheckDelimiters d(fileName); 

		//prompting user to check another file
		cout<<"Would you like to check another file? (Y/N)"<<endl;
		cin>>ans;
		if((ans=='y')||(ans=='Y'))
			repeat=true;
	}
	
	//continue while loop while user enters yes
	while((ans=='y')||(ans=='Y'));
	cout<<"Processing complete"<<endl;
	return 0;
}