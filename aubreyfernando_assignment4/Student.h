using namespace std;
/* 
Student is the type that is later added to queue.
These variables are stored within student in the queue
*/
class Student
{
public:
	Student(); 
	Student(int ta, int tn);
	~Student();

	int timeNeeded;  
	int timeArrived;
};