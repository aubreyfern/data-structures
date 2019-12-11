#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <stdlib.h>
#include <sstream>
#include <string>
#include "Game.h"
using namespace std;
/*
Game.cpp prompts the user whether to print results to a file or 
to the console with the option of pausing between generations or 
outputting all generations at the same time. 
Completes classic mode simulation.
*/
Game::Game()
{
	//initialize generation count to 0
	genCount=0;
}
Game::~Game()
{
}

//get all values from input.cpp
void Game::getAll(char** array,int r, int c)
{
	theArray = array; 
	rows=r;
	columns=c; 
}

//prompts user for mode, print to file or output with pauses or continously
void Game::Navigate()
{
	char mode; 
	char printType; 
	char ans; 
	cout<<"Choose a mode to run (a)Classic (b)Donut (c)Mirror"<<endl; 
	cin>>mode; 
	if((mode=='a')||(mode=='A')||(mode=='B')||(mode=='b')||(mode=='c')||(mode=='C'))
	{
	}
	else{
		Navigate(); 
	}
	cout<<"Would you like to (a)Write to a file or (b)Output to console"<<endl; 
	cin>>ans; 
	if((ans=='A')||(ans=='a'))
	{
		printType='a'; 
		outFile.open("GenFile.out");
		GameSimulation(mode,printType);
		outFile.close();
	}
	else if((ans=='b')||(ans=='B'))
	{
		cout<<"Would you like to pause between generations? :(Y/N)"<<endl; 
		cin>>printType; 

		if((printType=='y')||(printType=='Y'))
		{
			GameSimulation(mode,printType);
		}
		else if((printType=='n')||(printType=='N'))
		{
			GameSimulation(mode, printType);
		}

		else{
			cout<<"Invalid Entry"<<endl;
			Navigate(); 
		}
	}

	else {
		cout<<"Invalid Entry"<<endl;
		Navigate();
	}
}

//prints array for GameSim continous printing
void Game::Print()
{
	cout<<endl<<"Generation:"<<genCount<<endl; 
	for(int p = 0; p < rows; ++p)
	{
		for(int m = 0; m< columns; ++m)
		{
			cout<<theArray[p][m];
		}
		cout<<"\n";	
	}
}

//prints array for pause simulation
void Game::PrintPause()
{
	//cin.gets waits til key is entered before printing
	cin.get();
	cout<<endl<<"Generation:"<<genCount<<endl; 
	for(int p = 0; p < rows; ++p)
	{
		for(int m = 0; m< columns; ++m)
		{
			cout<<theArray[p][m];
		}
		cout<<"\n";	
	}
}

//collects neighbor information for all locations
void Game::CollectNewArrayClassic()
{
	cout<<endl;
	CheckCorners(); 
	CheckMiddleTopBottom(); 
	CheckMiddleSides();
	CheckMiddle();
}

//collects neighbors for mirror mode
void Game::CollectNewArrayMirror()
{
	cout<<endl;
	CheckCornersMirror(); 
	CheckMiddleTopBottomMirror(); 
	CheckMiddleSidesMirror(); 
	CheckMiddle();

}

//collects neighbors for donut mode
void Game::CollectNewArrayDonut()
{
	CheckCornersDonut(); 
	CheckMiddleTopBottomDonut();
	CheckMiddleSidesDonut();
	CheckMiddle(); 
}

//make second array to pput new generation in 
void Game::MakeMap2()
{
	newArray = new char*[rows]; 
	for(int i=0; i<rows;++i)
	{
		newArray[i]= new char[columns]; 
	}

	for(int i=0; i<rows; ++i)
	{
		for(int j=0;j<columns;++j)
		{
			newArray[i][j]='-';
		}
	}
}

//assign x or - depending on neighbors taking in current status
char Game::NewVal(int neighbors,char current)
{
	char newValue; 
	if(neighbors<=1)
		newValue='-';
	else if(neighbors==2)
		newValue=current; 
	else if(neighbors==3)
		newValue='x';
	else if(neighbors>=4)
		newValue='-'; 

	return newValue; 
}

//swap newArray to theArray
void Game::SwapArrays()
{
	char **temp = theArray; 
	theArray = newArray; 
	newArray= temp; 
}


//game simulation taking in mode and where sim results will go
void Game::GameSimulation(char mode,char printType)
{
	int same=0; 
	int empty=0; 
	int stable=0;
	int total=rows*columns; 
	//print generation based on location chosen by user
	switch(printType)
	{
		case 'a':
		case 'A':
		outFile<<PrintFile(); 
		break;

		case 'y':
		case'Y': 
		PrintPause(); 
		break;

		case 'n':
		case 'N':
		Print(); 
		break;

	}
	//collect all information making new generation based on mode
	switch(mode)
	{
		case 'a':
		case'A':
		CollectNewArrayClassic(); 
		break;

		case 'c':
		case'C':
		CollectNewArrayMirror();
		break; 

		case 'b':
		case'B':
		CollectNewArrayDonut();
		break; 
	}
	genCount++;  
	//keeps track if entire board is the same, empty or stable
	for(int i=0; i<rows; ++i)
	{
		for(int j=0; j<columns; ++j)
		{
			if(theArray[i][j]==newArray[i][j])
				same++; 
			
		 	if(newArray[i][j]=='-')
				empty++;
			
			if(newArray[i][j]=='x')
				stable++; 
		}
	}
	//if same board (infinite loop) end and print
	if(same==total)
	{
		SwapArrays(); 
		switch(printType)
		{
		case 'a':
		case 'A':
		outFile<<PrintFile(); 
		outFile<<endl<<"Complete! Previous generations equals new generation"<<endl;
		cout<<"Generations written to 'GenFile.out'"<<endl;
		break;

		case 'y':
		case'Y': 
		PrintPause(); 
		cout<<endl<<"Complete! Previous generations equals new generation"<<endl;
		break;

		case 'n':
		case 'N':
		Print(); 
		cout<<endl<<"Complete! Previous generations equals new generation"<<endl;
		break;
		}
	}
	//if board empty end 
	else if(empty==total)
	{
		SwapArrays(); 
		switch(printType)
		{
			case 'a':
			case'A':
			outFile<<PrintFile();
			outFile<<endl<<"Complete! World has become empty"<<endl;
			cout<<"Generations written to 'GenFile.out'"<<endl;
			break; 

			case'y':
			case 'Y':
			PrintPause(); 
			cout<<endl<<"Complete! World has become empty"<<endl;
			break; 

			case 'n':
			case'N':
			Print(); 
			cout<<endl<<"Complete! World has become empty"<<endl;
			break;
		}
		
	}
	//if board stable end
	else if(stable==total)
	{
		SwapArrays(); 

		switch(printType)
		{
			case'a':
			case'A':
			outFile<<PrintFile();
			outFile<<endl<<"Complete! World has stabilized"<<endl;
			cout<<"Generations written to 'GenFile.out'"<<endl;
			break; 

			case'y':
			case'Y':
			PrintPause();
			cout<<endl<<"Complete! World has stabilized"<<endl; 
			break;

			case 'n':
			case'N':
			Print();
			cout<<endl<<"Complete! World has stabilized"<<endl;
			break;
		}
	}
	//if generation count exceeds 100 (infinite loop) end
	else if(genCount>100)
	{
		SwapArrays(); 
		switch(printType)
		{
			case 'a':
			case 'A':
			outFile<<PrintFile(); 
			outFile<<"100 Generations exceeded.Infinite cycle. Simulation Terminated."<<endl;	
			cout<<"Generations written to 'GenFile.out'"<<endl;
			break;

			case 'y':
			case 'Y':
			PrintPause(); 
			cout<<"100 Generations exceeded.Infinite cycle. Simulation Terminated."<<endl;	
			break;

			case'n':
			case'N':
			Print(); 
			cout<<"100 Generations exceeded.Infinite cycle. Simulation Terminated."<<endl;	
			break;

		}
	}
	//if else continue simulation
	else{
		SwapArrays();
		GameSimulation(mode, printType); 
		}
}

//printing board to file using stringstream
string Game::PrintFile()
{
	stringstream write; 
	if(genCount==0)
	{
		write<<"Aubrey Fernando"<<endl<<"2271086"<<endl<<"CPSC 350-2"<<endl;
	}
	write<<endl<<"Generation:"<<genCount<<endl; 
	for(int p = 0; p < rows; ++p)
	{
		for(int m = 0; m< columns; ++m)
		{
			write<<theArray[p][m];
		}
		write<<endl;	
	}
	return write.str();

}

//begin checking for neighbors for classic mode

//checking corners of the board for classic mode
void Game::CheckCorners()
{
	//setting neighbors to 0
	int neighbors=0; 
	for(int i=0; i<rows;++i)
	{
		for(int j=0; j<columns;++j)
		{
			//top left corner
			if((i==0)&&(j==0))
			{
				neighbors=0;
				if(theArray[i][j+1]=='x')
					neighbors++; 
				
				 if(theArray[i+1][j]=='x')
					neighbors++; 
				
				if(theArray[i+1][j+1]=='x')
					neighbors++; 

				char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue; 
			}

			//top right corner
			else if((i==0)&&(j==columns-1))
			{
				neighbors=0;
				if(theArray[i][j-1]=='x')
					neighbors++; 
				
				 if(theArray[i+1][j]=='x')
					neighbors++; 
				
				if(theArray[i+1][j-1]=='x')
					neighbors++; 

				char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue; 		
			}

			//bottom left corner
			else if((i==rows-1)&&(j==0))
			{
				neighbors=0;
				if(theArray[i][j+1]=='x')
					neighbors++; 
				
				 if(theArray[i-1][j]=='x')
					neighbors++; 
				
				if(theArray[i-1][j+1]=='x')
					neighbors++; 

				char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue; 
			}

			//bottom right corner
			else if((i==rows-1)&&(j==columns-1))
			{
				neighbors=0;
				if(theArray[i][j-1]=='x')
					neighbors++; 
				
				 if(theArray[i-1][j]=='x')
					neighbors++; 
				
				if(theArray[i-1][j-1]=='x')
					neighbors++; 

				char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue; 
			}

		}
	}
}


//check neighbors of locations in the middle middle of board all modes
void Game::CheckMiddle()
{
	int neighbors=0; 
	//i and j start at 1 to void corners and border of board
	for(int i=1;i<rows; ++i)
	{
		for(int j=1; j<columns; ++j)
		{
			if((j<columns-1)&&(i<rows-1))
			{
				neighbors=0;
				if(theArray[i-1][j-1]=='x')
					neighbors++; 
				if(theArray[i-1][j]=='x')
					neighbors++; 
				if(theArray[i-1][j+1]=='x')
					neighbors++;
				if(theArray[i+1][j-1]=='x')
					neighbors++;
				if(theArray[i+1][j]=='x')
					neighbors++; 
				if(theArray[i+1][j+1]=='x')
					neighbors++;
				if(theArray[i][j-1]=='x')
					neighbors++;
				if(theArray[i][j+1]=='x')
					neighbors++; 

				char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue; 
			}
		}
	}
}

//check middle top and bottom of the border of the board classic mode
void Game::CheckMiddleTopBottom()
{
	int neighbors=0;
	for(int i =0; i<rows; ++i)
	{
		for(int j =0; j<columns;++j)
		{

		//top middle
		 if((!j==0)&&(j<columns-1)&&(i==0))
			{
				neighbors=0; 
				if(theArray[i][j-1]=='x')
					neighbors++;
				if(theArray[i][j+1]=='x')
					neighbors++;
				if(theArray[i+1][j-1]=='x')
					neighbors++;
				if(theArray[i+1][j]=='x')
					neighbors++;
				if(theArray[i+1][j+1]=='x')
					neighbors++;

				char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue; 

			}

			//bottom middle
			else if((i==rows-1)&&(!j==0)&&(j<columns-1))
			{
				neighbors=0;
				if(theArray[i][j-1]=='x')
					neighbors++; 
				if(theArray[i][j+1]=='x')
					neighbors++;
				if(theArray[i-1][j-1]=='x')
					neighbors++; 
				if(theArray[i-1][j]=='x')
					neighbors++;
				if(theArray[i-1][j+1]=='x')
					neighbors++; 

				char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue; 
			}
		}
	}
}

//check middle of sides of the board classic mode
void Game::CheckMiddleSides()
{
	int neighbors=0;
	for(int f= 0; f<rows; ++f)
	{
		for(int g=0; g<columns; ++g)

		{
			//middle left 
			if((!f==0)&&(f<rows-1)&&(g==0))
			{
				neighbors=0; 
				if(theArray[f-1][g]=='x')
					neighbors++;
				if(theArray[f+1][g]=='x')
					neighbors++;
				if(theArray[f-1][g+1]=='x')
					neighbors++;
				if(theArray[f][g+1]=='x')
					neighbors++;
				if(theArray[f+1][g+1]=='x')
					neighbors++;
				char oldVal = theArray[f][g];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[f][g]=newValue; 
			}

			//middle right
			else if((!f==0)&&(f<rows-1)&&(g==columns-1))
			{
				neighbors=0; 
				if(theArray[f-1][g]=='x')
					neighbors++;
				if(theArray[f+1][g]=='x')
					neighbors++;
				if(theArray[f-1][g-1]=='x')
					neighbors++;
				if(theArray[f][g-1]=='x')
					neighbors++;
				if(theArray[f+1][g-1]=='x')
					neighbors++; 

				char oldVal = theArray[f][g];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[f][g]=newValue; 			}
		}
	}

}

//begin neighbor checking for mirror mode

//checks neighbors for corners of board mirror mode
void Game::CheckCornersMirror()
{
	int neighbors=0;
	for(int i =0; i<rows; ++i)
	{
		for(int j =0; j<columns;++j)
		{
			//top left corner
			if((i==0)&&(j==0))
			{
				neighbors=0; 
				//corner mirrored 3 times
				if(theArray[i][j]=='x')
					neighbors+=3; 
				if(theArray[i+1][j]=='x')
					neighbors+=2; 
				if(theArray[i][j+1]=='x')
					neighbors+=2; 
				if(theArray[i+1][j+1]=='x')
					neighbors++;

				char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue; 	
			}	

			//top right corner
			else if((i==0)&&(j==columns-1))
			{
				neighbors=0; 
				if(theArray[i][j]=='x')
					neighbors+=3; 
				if(theArray[i+1][j]=='x')
					neighbors+=2; 
				if(theArray[i][j-1]=='x')
					neighbors+=2;
				if(theArray[i+1][j-1]=='x')
					neighbors++; 

				char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue; 
			}

			//bottom left corner
			else if((i==rows-1)&&(j==0))
			{
				neighbors=0; 

				if(theArray[i][j]=='x')
					neighbors+=3; 

				if(theArray[i-1][j]=='x')
					neighbors+=2; 
				if(theArray[i][j+1]=='x')
					neighbors+=2; 
				if(theArray[i-1][j+1]=='x')
					neighbors++; 

				char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue; 
			}

			//bottom right corner
			else if((i==rows-1)&&(j==columns-1))
			{
				neighbors=0; 

				if(theArray[i][j]=='x')
					neighbors+=3; 

				if(theArray[i-1][j]=='x')
					neighbors+=2; 
				if(theArray[i][j-1]=='x')
					neighbors+=2; 
				if(theArray[i-1][j-1]=='x')
					neighbors++; 

				char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue; 
			}
		}
	}	
}


void Game::CheckMiddleTopBottomMirror()
{
	int neighbors=0;
	for(int i =0; i<rows; ++i)
	{
		for(int j =0; j<columns;++j)
		{
			neighbors=0; 
			//top middle
			 if((!j==0)&&(j<columns-1)&&(i==0))
			 {
			 	neighbors=0; 
			 	if(theArray[i][j]=='x')
			 		neighbors++; 
			 	if(theArray[i][j-1]=='x')
			 		neighbors+=2; 
			 	if(theArray[i][j+1]=='x')
			 		neighbors+=2; 
			 	if(theArray[i+1][j-1]=='x')
			 		neighbors++; 
			 	if(theArray[i+1][j]=='x')
			 		neighbors++; 
			 	if(theArray[i+1][j+1]=='x')
			 		neighbors++; 

			 	char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue; 
			 }
			 //bottom middle
			 else if((i==rows-1)&&(!j==0)&&(j<columns-1))
			 {
			 	neighbors=0; 
			 	if(theArray[i][j]=='x')
			 		neighbors++; 
			 	if(theArray[i][j-1]=='x')
			 		neighbors+=2; 
			 	if(theArray[i][j+1]=='x')
			 		neighbors+=2; 
			 	if(theArray[i-1][j-1]=='x')
			 		neighbors++; 
			 	if(theArray[i-1][j]=='x')
			 		neighbors++; 
			 	if(theArray[i-1][j+1]=='x')
			 		neighbors++; 

			 	char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue; 

			 }

		}
	}

}

void Game::CheckMiddleSidesMirror()
{
	int neighbors=0;
	for(int i=0; i<rows; ++i)
	{
		for(int j=0; j<columns;++j)
		{
			neighbors=0; 
			//middle left
			if((!i==0)&&(i<rows-1)&&(j==0))
			{
				neighbors=0; 
				if(theArray[i][j]=='x')
					neighbors++;
				if(theArray[i-1][j]=='x')
					neighbors+=2; 
				if(theArray[i+1][j]=='x')
					neighbors+=2; 
				if(theArray[i-1][j+1]=='x')
					neighbors++; 
				if(theArray[i][j+1]=='x')
					neighbors++; 
				if(theArray[i+1][j+1]=='x')
					neighbors++; 

				char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue; 
			}

			//middle right
			else if((!i==0)&&(i<rows-1)&&(j==columns-1))
			{
				neighbors=0; 
				if(theArray[i][j]=='x')
					neighbors++; 
				if(theArray[i-1][j]=='x')
					neighbors+=2; 
				if(theArray[i+1][j]=='x')
					neighbors+=2; 
				if(theArray[i-1][j-1]=='x')
					neighbors++; 
				if(theArray[i][j-1]=='x')
					neighbors++; 
				if(theArray[i+1][j-1]=='x')
					neighbors++;

				char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue; 
			}

		}
	}
}


//begin checking neighbors donut mode
void Game::CheckCornersDonut()
{
	int neighbors=0;
	for(int i=0; i<rows; ++i)
	{
		for(int j=0; j<columns;++j)
		{
			neighbors=0; 

			//top left corner
			if((i==0)&&(j==0))
			{
				neighbors=0; 

				if(theArray[rows-1][columns-1]=='x')
					neighbors++; 
				if(theArray[i][columns-1]=='x')
					neighbors++; 
				if(theArray[i+1][columns-1]=='x')
					neighbors++;
				if(theArray[rows-1][j]=='x')
					neighbors++;
				if(theArray[i+1][j]=='x')
					neighbors++; 
				if(theArray[rows-1][j+1]=='x')
					neighbors++; 
				if(theArray[i][j+1]=='x')
					neighbors++; 
				if(theArray[i+1][j+1]=='x')
					neighbors++; 

				char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue; 

			}

			//top right corner
			else if((i==0)&&(j==columns-1))
			{
				neighbors=0; 

				if(theArray[rows-1][0]=='x')
					neighbors++;
				if(theArray[i][0]=='x')
					neighbors++; 
				if(theArray[i+1][0]=='x')
					neighbors++; 
				if(theArray[rows-1][j]=='x')
					neighbors++; 
				if(theArray[i+1][j]=='x')
					neighbors++; 
				if(theArray[rows-1][j-1]=='x')
					neighbors++; 
				if(theArray[i][j-1]=='x')
					neighbors++; 
				if(theArray[i+1][j-1]=='x')
					neighbors++; 

				char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue;
			}

			//bottom left corner
			else if((i==rows-1)&&(j==0))
			{
				neighbors=0; 

				if(theArray[0][columns-1]=='x')
					neighbors++; 
				if(theArray[i][columns-1]=='x')
					neighbors++; 
				if(theArray[i-1][columns-1]=='x')
					neighbors++; 
				if(theArray[0][j]=='x')
					neighbors++; 
				if(theArray[i-1][j]=='x')
					neighbors++; 
				if(theArray[0][j+1]=='x')
					neighbors++; 
				if(theArray[i][j+1]=='x')
					neighbors++; 
				if(theArray[i-1][j+1]=='x')
					neighbors++; 

				char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue;

			}

			//bottom right corner
			else if((i==rows-1)&&(j==columns-1))
			{
				neighbors=0; 

				if(theArray[0][0]=='x')
					neighbors++; 
				if(theArray[i][0]=='x')
					neighbors++; 
				if(theArray[i-1][0]=='x')
					neighbors++; 
				if(theArray[0][j]=='x')
					neighbors++; 
				if(theArray[i-1][j]=='x')
					neighbors++; 
				if(theArray[0][j-1]=='x')
					neighbors++; 
				if(theArray[i][j-1]=='x')
					neighbors++; 
				if(theArray[i-1][j-1]=='x')
					neighbors++; 

				char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue;
			}

		}
	}
}


void Game::CheckMiddleTopBottomDonut()
{
	int neighbors=0;
	for(int i=0; i<rows; ++i)
	{
		for(int j=0; j<columns;++j)
		{
			neighbors=0;

			//top middle
			 if((!j==0)&&(j<columns-1)&&(i==0))
			 {
			 	neighbors=0; 
			 	if(theArray[rows-1][j-1]=='x')
			 		neighbors++; 
			 	if(theArray[i][j-1]=='x')
			 		neighbors++; 
			 	if(theArray[i+1][j-1]=='x')
			 		neighbors++; 
			 	if(theArray[rows-1][j]=='x')
			 		neighbors++; 
			 	if(theArray[i+1][j]=='x')
			 		neighbors++; 
			 	if(theArray[rows-1][j+1]=='x')
			 		neighbors++; 
			 	if(theArray[i][j+1]=='x')
			 		neighbors++; 
			 	if(theArray[i+1][j+1]=='x')
			 		neighbors++; 

			 	char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue;

			 }

			 //bottom middle
			 else if((i==rows-1)&&(!j==0)&&(j<columns-1))
			 {
			 	neighbors=0; 
			 	if(theArray[0][j-1]=='x')
			 		neighbors++; 
			 	if(theArray[i][j-1]=='x')
			 		neighbors++; 
			 	if(theArray[i-1][j-1]=='x')
			 		neighbors++; 
			 	if(theArray[0][j]=='x')
			 		neighbors++; 
			 	if(theArray[i-1][j]=='x')
			 		neighbors++; 
			 	if(theArray[0][j+1]=='x')
			 		neighbors++; 
			 	if(theArray[i][j+1]=='x')
			 		neighbors++; 
			 	if(theArray[i-1][j+1]=='x')
			 		neighbors++; 

			 	char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue;

			 }
			 
	 	}
	}
}

void Game::CheckMiddleSidesDonut()
{
	int neighbors=0;
	for(int i=0; i<rows; ++i)
	{
		for(int j=0; j<columns;++j)
		{
			neighbors=0; 

			//middle left
			if((!i==0)&&(i<rows-1)&&(j==0))
			{
				neighbors=0; 

				if(theArray[i+1][columns-1]=='x')
					neighbors++; 
				if(theArray[i][columns-1]=='x')
					neighbors++; 
				if(theArray[i-1][columns-1]=='x')
					neighbors++; 
				if(theArray[i+1][j]=='x')
					neighbors++; 
				if(theArray[i-1][j]=='x')
					neighbors++; 
				if(theArray[i+1][j+1]=='x')
					neighbors++; 
				if(theArray[i][j+1]=='x')
					neighbors++; 
				if(theArray[i-1][j+1]=='x')
					neighbors++; 

				char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue;
			}

			//middle right
			else if((!i==0)&&(i<rows-1)&&(j==columns-1))
			{
				neighbors=0; 

				if(theArray[i+1][0]=='x')
					neighbors++; 
				if(theArray[i][0]=='x')
					neighbors++; 
				if(theArray[i-1][0]=='x')
					neighbors++; 
				if(theArray[i+1][j]=='x')
					neighbors++;
				if(theArray[i-1][j]=='x')
					neighbors++; 
				if(theArray[i+1][j-1]=='x')
					neighbors++;
				if(theArray[i][j-1]=='x')
					neighbors++; 
				if(theArray[i-1][j-1]=='x')
					neighbors++; 

				char oldVal = theArray[i][j];  
				char newValue= NewVal(neighbors,oldVal); 
				newArray[i][j]=newValue;

			}
		}
	}
}
