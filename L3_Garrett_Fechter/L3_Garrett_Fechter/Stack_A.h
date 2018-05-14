//Garrett Fechter
//Purpose: stack using array
//Created 2018
//Modified: 

#ifndef STACK_A
#define STACK_A

#include "Array1D.h"
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
	bool isFull
		true if contains max elements
*/

template<typename T>
class Stack_A
{
public:
	Stack_A();
	Stack_A(int stackSize);
	Stack_A(const Stack_A<T> & copy);
	~Stack_A();
	Stack_A<T> & operator = (const Stack_A<T> & rhs);
	void Push(const T data);
	T Pop();
	T Peek();
	int Size(); //a getter for height
	void SetSize(int length); //setter for max length
	int GetLength(); //a getter for max length
	bool isEmpty();
	bool isFull();
private:
	int m_height;//how many elements stacked
	Array1D<T> m_stack;//the stack
};

#endif

template<typename T>
inline Stack_A<T>::Stack_A() : m_stack(0), m_height(0)
{ }

template<typename T>
inline Stack_A<T>::Stack_A(int stackSize) : m_stack(stackSize), m_height(0)
{ }

template<typename T>
inline Stack_A<T>::Stack_A(const Stack_A & copy) : m_stack(copy.m_stack), m_height(copy.m_height)
{ }

template<typename T>
inline Stack_A<T>::~Stack_A()
{
	m_height = 0;
}

template<typename T>
inline Stack_A<T> & Stack_A<T>::operator=(const Stack_A<T> & rhs)
{
	m_stack = rhs.m_stack;
	m_height = rhs.m_height;
	return *this;
}

template<typename T>
inline void Stack_A<T>::Push(const T data)
{
	if (m_height + 1 > m_stack.GetLength())
		throw Exception("Tried to Push when full\n");
	m_stack[m_height] = data;
	m_height++;
}

template<typename T>
inline T Stack_A<T>::Pop()
{
	if (m_height == 0)
		throw Exception("Tried to Pop on empty");
	T ret = m_stack[m_height - 1];//get last element
	//don't really need to delete, once height lowers it's semantically gone
	m_height--;
	return ret;
}

template<typename T>
inline T Stack_A<T>::Peek()
{
	if (m_height == 0)
		throw Exception("Tried to Peek on empty");
	return m_stack[m_height - 1];
}

template<typename T>
inline int Stack_A<T>::Size()
{
	return m_height;
}

template<typename T>
inline void Stack_A<T>::SetSize(int length)
{
	m_stack.SetLength(length);
}

template<typename T>
inline int Stack_A<T>::GetLength()
{
	return m_stack.GetLength();
}

template<typename T>
inline bool Stack_A<T>::isEmpty()
{
	bool empty = false;
	if (m_height == 0)
		empty = true;
	return empty;
}

template<typename T>
inline bool Stack_A<T>::isFull()
{
	bool full = false;
	if (m_height == m_stack.GetLength())
		full = true;
	return full;
}
