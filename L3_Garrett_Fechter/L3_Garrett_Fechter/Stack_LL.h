//Garrett Fechter
//Purpose: a stack implementation using a linked list
//Created 2018
//Modified: 
#ifndef STACK_LL_H
#define STACK_LL_H

#include "LinkedList.h"

/*
	Stack_LL();
		a default ctor. m_heigth of 0, empty LL
	Stack_LL(const Stack_LL<T> & copy);
		copy ctor
	Stack_LL<T> & operator = (const Stack_LL<T> & rhs);
		overaloaded assignment operator
	~Stack_LL();
		destructor. resets ll
	void Push(const T data);
		put something on stack
	T Pop();
		take top element off and return it
	T Peek();
		just return top element of stack
	int Size();//getter for height
	bool isEmpty();
		true if 0 elements
*/
template<typename T>
class Stack_LL 
{
public:
	Stack_LL();
	Stack_LL(const Stack_LL<T> & copy);
	Stack_LL<T> & operator = (const Stack_LL<T> & rhs);
	~Stack_LL();
	void Push(const T data);
	T Pop();
	T Peek();
	int Size();//getter for height
	bool isEmpty();
private:
	int m_height;//# of elements in LL
	LL<T> m_stack;//the stack
};

#endif

template<typename T>
inline Stack_LL<T>::Stack_LL() : m_stack(), m_height(0)
{ }

template<typename T>
inline Stack_LL<T>::Stack_LL(const Stack_LL<T>& copy) : m_stack(copy.m_stack), m_height(copy.m_height)
{ }

template<typename T>
inline Stack_LL<T>& Stack_LL<T>::operator=(const Stack_LL<T>& rhs)
{
	m_stack = rhs.m_stack;
	m_height = rhs.m_height;
	return *this;
}

template<typename T>
inline Stack_LL<T>::~Stack_LL()
{
	m_height = 0;
}

template<typename T>
inline void Stack_LL<T>::Push(const T data)
{
	m_stack.Prepend(data);
	m_height++;
}

template<typename T>
inline T Stack_LL<T>::Pop()
{
	if (m_stack.isEmpty())
		throw Exception("Tried to Pop on empty\n");
	T data = m_stack.First();
	m_stack.Extract(data);
	m_height--;
	return data;
}

template<typename T>
inline T Stack_LL<T>::Peek()
{
	if (m_stack.isEmpty())
		throw Exception("Tried to Pop on empty\n");
	T data = m_stack.First();
	return data;
}

template<typename T>
inline int Stack_LL<T>::Size()
{
	return m_height;
}

template<typename T>
inline bool Stack_LL<T>::isEmpty()
{
	return m_stack.isEmpty();
}