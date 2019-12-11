#include <iostream>
#include "fileCheck.h"
#include <cstdlib>
#include <string>
#include "Simulation.h"

using namespace std;
 
 int main(int argc, char* argv[])
 {
 	string fileName2; 
 	
 	//if file name entered after .out
 	if(argc>1)
 	{
 		fileCheck f(argv[1]);
 		f.fileExists(); 
 		fileName2 = f.getFileName(); 
 	}
 	//if not ask for file
 	else{
 		fileCheck f; 
		fileName2 = f.getFileName();
 	}

 	//send file name to simulation
 	Simulation s(fileName2);

 	return 0;

 }