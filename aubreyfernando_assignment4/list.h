using namespace std;
template <class T>
class List{
public:
	virtual void insertFront(T* data)=0; 
	virtual void insertBack(T* data)=0; 
	virtual T* removeFront()=0; 
	virtual T* removeBack()=0; 
	virtual bool find(T value)=0; 
	virtual T* remove(int key)=0;
	virtual void printList()=0; 
	virtual unsigned int getSize()=0;
	virtual bool isEmpty()=0; 

}; 