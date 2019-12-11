#include<iostream>
#include "Input.h"
#include "Game.h"

using namespace std;
int main()
{
	cout<<"Welcome to the Game of Life!"<<endl; 
	Input i; 
	//get rows and columns from input to use in game.cpp
	int rows = i.getRow(); 
	int columns = i.getColumns(); 
	//make theArray map passed into game.cpp
	i.makeMap();
	//generate map from file sets the array and when generate map from input is called the array is still itself
	char** myArray= i.GenerateMapFromFile(); 
	//if file is not read in the array is generating from input
	i.GenerateMapFromInput(); 

	//pass the  array, rows and columns into game.cpp
	Game g; 
	g.getAll(myArray,rows,columns);
	//make new array for new data to be entered into
	g.MakeMap2();
	//prompt user for mode and where to output results
	g.Navigate();	
}