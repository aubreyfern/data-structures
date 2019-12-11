#include <iostream>
#include <cstdlib>
using namespace std; 
#define SIZE 10
using namespace std;

template <class T>
class GenStack {
    int top;
    int size;
    T *theArray;

public:
    GenStack();
    GenStack(int maxSize = SIZE);
    ~GenStack();

    void push(T);
    int sizeOfArray();
    bool isEmpty();
    bool isFull();
    T pop();
    T peek();
    void expandCapacity(); 

};

//default constructor
template <class T>
GenStack<T>::GenStack() 
{
    top = -1;
}

//overload constructor
template <class T>
GenStack<T>::GenStack(int maxSize)
{
    theArray = new T[maxSize];
    size = maxSize;
    top = -1;
}

//destructor
template <class T>
GenStack<T>::~GenStack() {
    delete[] theArray;
}

//inserting to stack
template <class T>
void GenStack<T>::push(T item) {

    if (!isFull()) {
        theArray[++top] = item;
    } else {
        cout << "Stack is full" << endl;
        //if full allocate new
        expandCapacity(); 
        theArray[++top]=item;
    }
}

//return size 
template <class T>
int GenStack<T>::sizeOfArray()
{
    return(size + 1);
}

//returns if stack is empty
template <class T>
bool GenStack<T>::isEmpty()
{

    return top == -1;
}

//returns if stack is full
template <class T>
bool GenStack<T>::isFull()
{
 
    return top == size - 1;
}

//removes from stack 
template <class T>
T GenStack<T>::pop(){
    if(isEmpty()) {
        cout<<"Popping from an empty stack"<<endl;
    }
    return theArray[top--];
}

//returns the top item on stack
template <class T>
T GenStack<T>::peek(){
    if(isEmpty()) {
        cout<<"Peeking from an empty stack"<<endl;
    }
    return theArray[top];
}

//allocate new space on stack by doubling size of the array making a new array, 
//moving contents over, and delete temporary array
template <class T>
void GenStack<T>::expandCapacity()
{
	T *oldArray = theArray; 
	size =size*2; 
	theArray = new T[size];

	for(int i=0; i<sizeOfArray(); ++i)
	{
		theArray[i] = oldArray[i];
	}
	delete[] oldArray; 
}
