#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "checkDelimiters.h"
using namespace std; 

//default construtor
CheckDelimiters::CheckDelimiters()
{

}

//overload constructor
CheckDelimiters::CheckDelimiters(string fileName)
{
	file = fileName;
	CheckSyntax();
}

//deconstructor
CheckDelimiters::~CheckDelimiters()
{

}

//reads file to count amount of lines in file to use this value as stack size
int CheckDelimiters::readStackSize()
{
	int count=0;
	ifstream infile(file.c_str());
	if(infile.is_open()&&infile.good())
	{
		string lines; 
		while(getline(infile,lines))
		{
			count++; 
		}	
	}
	infile.close();
	return count;

}

//return closing or opening delimiters used for expected/missing report
char CheckDelimiters::returnComplement(char c)
{
	char lpar = '('; char rpar = ')';
	char lbrac = '['; char rbrac = ']'; 
	char lcurl = '{'; char rcurl = '}'; 

	if(c==lpar)
		return rpar; 
	else if(c==rpar)
		return  lpar; 
	else if(c==lbrac)
		return rbrac; 
	else if(c==rbrac)
		return lbrac; 
	else if(c==lcurl)
		return rcurl; 
	else if(c==rcurl)
		return lcurl;
}

//read file and pushes opening delimiters onto stack and checks for closing delimiters
void CheckDelimiters::CheckSyntax()
{
	int stackSize = readStackSize(); 
	//return location of problem
	int countlines = 0; 
	bool issue = false; 

	GenStack<char> myStack(stackSize);

	ifstream infile(file.c_str());
	if(infile.is_open()&&infile.good())
	{
		string lines;
		while(getline(infile,lines))
		{
			countlines++; 
			for(int i=0; i<lines.length(); ++i)
			{
				//if { push onto stack
				if(lines[i]=='{')
				{
					myStack.push('{');
				}
				//if }
				if(lines[i]=='}')
				{
					//if empty thers a missing opening delimiter {
					if(myStack.isEmpty())
					{
						cout<<"Line "<<countlines<<": Missing opening delimiter:{"<<endl;
						issue=true;
					}

					else{
						//check if opening is on top of stack
						if(myStack.peek()=='{')
						{
							myStack.pop(); 
						}
						//if not report missing complmennt for .peek() and found closing delimiter } instead
						else{
							cout<<"Line "<<countlines<<": Missing/Expected:"<<returnComplement(myStack.peek())<<" Found:}"<<endl;
							issue=true; 
						}
					}
				}
				if(lines[i]=='(')
				{
					myStack.push('(');
				}
				if(lines[i]==')')
				{
					if(myStack.isEmpty())
					{
					cout<<"Line "<<countlines<<": Missing opening delimiter:("<<endl;	
					issue=true;
					}
					else{
						if(myStack.peek()=='(')
						{
							myStack.pop(); 
						}
						else{
							cout<<"Line "<<countlines<<": Missing/Expected:"<<returnComplement(myStack.peek())<<" Found:)"<<endl;
							issue=true;
						}
					}
				}
				if(lines[i]=='[')
				{
					myStack.push('[');
				}
				if(lines[i]==']')
				{
					if(myStack.isEmpty())
					{
						cout<<"Line "<<countlines<<": Missing opening delimiter:["<<endl;
						issue=true;
					}
					else{
						if(myStack.peek()=='[')
						{
							myStack.pop(); 
						}
						else{
							cout<<"Line "<<countlines<<": Missing/Expected:"<<returnComplement(myStack.peek())<<" Found:]"<<endl;
							issue=true;
						}
					}
				}
			}
		}
	}
	infile.close(); 
	//if stack is not empty, missing closing delimiter
	if(!myStack.isEmpty())
	{
		cout<<"Reached end of file. Missing:"<<returnComplement(myStack.peek())<<endl;
	}
	//if stack is empty there are no delimiter syntax errors
	if(myStack.isEmpty()&&issue==false)
	{
		cout<<"No errors. Delimiter Syntax is correct"<<endl;
	}
}

