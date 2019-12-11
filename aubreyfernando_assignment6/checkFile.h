#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
/*
CheckFile checks if the file the user entered exists.
If the user doesn't enter in a file they are prompted to enter a file
which is also checked the file exists. The user is prompted to enter in a file
until they enter one that exists
*/
class CheckFile
{
	string fileName;
public:
	CheckFile();
	CheckFile(string file); 
	~CheckFile(); 
	void fileExists();
	void requestFile();
	string getFile();
};
