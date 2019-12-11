#include <string>
using namespace std; 
/* checks if the file exists and if not inquires
for a new file.
*/
class fileCheck
{
public:
	string fileName; 
	fileCheck(); 
	fileCheck(string fileN); 
	~fileCheck(); 

	void fileExists(); 
	void requestFile(); 
	string getFileName(); 
};