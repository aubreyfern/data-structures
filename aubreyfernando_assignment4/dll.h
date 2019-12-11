#include <iostream>
#include "list.h"
using namespace std;
template <class T>
class ListNode
{
public:
	ListNode(); 
	ListNode(T d); 
	~ListNode(); 
	T data;  
	ListNode<T> *prev; 
	ListNode<T> *next; 
};

template <class T>
ListNode<T>::ListNode()
{
	data=0; 
	next=NULL; 
	prev=NULL; 
}

template<class T>
ListNode<T>::~ListNode()
{
}

template<class T>
ListNode<T>::ListNode(T d)
{
	data=d; 
	next=NULL; 
}




template <class T>
class DoublyLinkedList: List<T>
{
private:
	ListNode<T> *front; 
	ListNode<T> *back; 
	unsigned int size; 

public:
	DoublyLinkedList(); 
	~DoublyLinkedList(); 

	virtual void insertFront(T* data); 
	virtual void insertBack(T* data); 
	virtual T* removeFront(); 
	virtual T* removeBack(); 
	virtual int find(T* data); 

	virtual T* remove(int val); 
	virtual void printList(); 

	
	virtual unsigned int getSize(); 
	virtual bool isEmpty();
};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	front = new ListNode<T>; 
	back = new ListNode<T>; 
	size=0;  

	front->next = back; 
	back->prev = front; 
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	while(!isEmpty()) removeFront(); 
	delete front; 
	delete back; 
}


template <class T>
void DoublyLinkedList<T>::insertFront(T* data)
{
	ListNode<T> *node = new ListNode<T>(data); 

	if(isEmpty())
	{
		back = node; 
	}
	else{
		front->prev = node; 
		node->next = front; 
	}

	front = node; 
	size++; 
}

template<class T>
void DoublyLinkedList<T>::insertBack(T* data)
{
	ListNode<T> *node = new ListNode<T>(data); 

	if(isEmpty())
	{
		front = node; 
	}
	else{
		back->next = node; 
		node->prev = back; 
	}

	back = node; 
	size++; 
}

template <class T>
T* DoublyLinkedList<T>::removeFront()
{
	ListNode<T> *node = front; 
	if(front->next==NULL)
	{
		back = NULL; 
	}

	else{
		front->next->prev = NULL; 
	}
	front = front->next; 
	--size; 

	node->next = NULL; 
	T temp = node->data; 
	delete node; 
	return temp; 
}

template <class T>
T* DoublyLinkedList<T>::removeBack()
{
	ListNode<T> *node = back; 
	if(front->next==NULL)
	{
		front = NULL;
	}
	else
	{
		back->prev->next = NULL; 
	}
	back = back->prev;
	--size; 
	node->prev = NULL; 
	T temp = node->data; 
	delete node; 
	return temp; 
}

template <class T>
T* DoublyLinkedList<T>::remove(int key)
{
	ListNode<T> *curr = front; 
	while(curr->data!=key)
	{
		curr = curr->next; 
		if(curr==NULL)
		{
			cout<<"Not Found"<<endl;
			return 0; 
		}
	}

	if(curr==front)
	{
		front = curr->next; 
	}
	else{
		curr->prev->next = curr->next; 
	}

	if(curr==back)
	{
		back = curr->prev;
	}

	else {
		curr->next->prev = curr->prev; 
	}

	curr->next = NULL;  
	curr->prev = NULL; 
	--size; 
	T temp = curr->data; 
	delete curr; 
	return temp; 
}

template<class T>
void DoublyLinkedList<T>::printList()
{
	ListNode<T> *curr = front; 
	while(curr!=NULL)
	{
		cout<<curr->data<<endl;; 
		curr = curr->next; 
	}
}

template<class T>
int DoublyLinkedList<T>::find(T* value)
{
	int index = -1; 
	ListNode<T> *curr = front; 

	while(curr!=NULL)
	{
		++index; 
		if(curr->data==value)
		{
			break; 
			
		}

		else
		{
			curr = curr->next; 
		}
	}
	//not found
	if(curr==NULL)
	{
		index = -1;
		cout<<"Not found"<<endl;
	}
	return index; 
}

template <class T>
bool DoublyLinkedList<T>::isEmpty()
{
	return (size==0);
}


template<class T>
unsigned int DoublyLinkedList<T>::getSize()
{
	return size; 
}
