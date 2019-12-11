#include<iostream>
#include "GenStack.h"
using namespace std; 
/*
CheckDelimiters reads in the file name from main and uses the amount of lines for the 
size of the stack. The file is opened again read line by line, if chars in the line equal any of 
opening delimiters it is added to the stack. If closing delimiters are found it is 
1. checked that the stack is empty, if it is this means a opening delimiter is missing
2. if the stack is not empty .peek() is called, if closing delimiter matches .peek opening 
.pop is called
3. if the stack is not empty and .peek is not the openign delimiters, it is missing an opening delimiter
problems and reported back with expected/missing delimiters and what was found instead on what line. 
After the file is closed, the stack is checked whether it is empty. 
If it's not empty theres a missing closing delimiter.
*/

class CheckDelimiters 
{
	string file; 
 public:
 	CheckDelimiters();
	CheckDelimiters(string fileName); 
	~CheckDelimiters();

	int readStackSize();  
	char returnComplement(char c);
	void CheckSyntax();

};

