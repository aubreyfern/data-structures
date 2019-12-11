#include <cstdlib>
#include <iostream>
#include "dll.h"
using namespace std;
template <class T>
class Queue 
{
public:
	Queue(); 
	~Queue(); 

	void enQueue(T data); 
	T deQueue(); 
	T getFront(); 
	T getBack();
 
	bool isEmpty(); 
	int getSize(); 
	void printQueue();

	ListNode<T> *front; 
	ListNode<T> *back; 
	unsigned int size; 

}; 

template <class T>
Queue<T>::Queue()
{
	size=0; 
	front=NULL;
	back=NULL;
}

template<class T>
Queue<T>::~Queue(){

}

//adding to Queue
template<class T>
void Queue<T>::enQueue(T data)
{
	ListNode<T> *node  = new ListNode<T>(data);
	if(size==0)
	{
		front = node; 
	}
	else{
		back->next = node; 
		node->prev = back; 
	}

	back = node; 
	++size; 
}

template<class T>
T Queue<T>::deQueue()
{
	//only remove if queue has elements
	if(!isEmpty())
	{
		ListNode<T> *tempFront = front; 
		T tempData = tempFront->data; 

		if(front->next==NULL)
		{
			front=NULL; 
			back = NULL; 
		}

		else{
			front->next->prev = NULL; 
			front = front->next; 
		}

		delete tempFront; 
		--size; 
		return tempData; 
	}

}

template<class T>
T Queue<T>::getFront()
{
	return (front->data); 
}

template<class T>
T Queue<T>::getBack()
{
	return (back->data);
}

template <class T>
bool Queue<T>::isEmpty()
{
	return (size==0);
}

template <class T>
int Queue<T>::getSize()
{
	return size;
}

template<class T>
void Queue<T>::printQueue()
{
	ListNode<T> *curr = front;

	while (true)
	{
		if (curr == NULL)
		{
			break;
		}

		cout << curr->data << endl;
		curr = curr->next;
	}
}



