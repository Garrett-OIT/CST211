//Garrett Fechter
//Purpose: a node for a LL, ADT
//Created 2018
//Modified: 
#ifndef NODE_H
#define NODE_H

/*
 Class: Node
 Purpose: Generic ADT node for a linked list
 canoncial funcS:
	Node();//default ctor
	Node(const Node & copy);
		copy ctor
	Node & operator = (const Node & rhs);
		overload assigmnet operator
	~Node();
		dtor. m_data empty, nullptr prev/next
 Funcs:
	Node<T> * getNext();
		get the node pointed to by m_next
	void setNext(Node * next);
		set the node pointed to by m_next
	Node<T> * getPrev();
		getter for m_prev
	void setPrev(Node * prev);
		setter for m_prev
	T & getData();
		return the data in a node
	void setData(T data);
		set the data in a node
*/

template<typename T>
class Node 
{
public:
	Node();//default ctor
	Node(const Node & copy);
	Node & operator = (const Node & rhs);
	Node<T> * getNext();
	void setNext(Node * next);
	Node<T> * getPrev();
	void setPrev(Node * prev);
	T & getData();
	void setData(T data);
	~Node();
private:
	T m_data;
	Node<T> *m_next;
	Node<T> *m_prev;
};

template<typename T>
inline Node<T>::Node() : m_data(), m_next(nullptr), m_prev(nullptr)
{ }

template<typename T>
inline Node<T>::Node(const Node & copy) : m_data(copy.m_data), m_next(copy.m_next), m_prev(copy.m_prev)
{ }

template<typename T>
inline Node<T> & Node<T>::operator=(const Node & rhs)
{
	if (this != &rhs) 
	{
		m_data = rhs.m_data;
		m_next = rhs.m_next;
		m_prev = rhs.m_prev;
	}
	return *this;
}

template<typename T>
inline  Node<T> * Node<T>::getNext() 
{
	return m_next;
}

template<typename T>
inline void Node<T>::setNext(Node * next)
{
	m_next = next;
}

template<typename T>
inline  Node<T> * Node<T>::getPrev() 
{
	return m_prev;
}

template<typename T>
inline void Node<T>::setPrev(Node * prev)
{
	m_prev = prev;
}

template<typename T>
inline  T & Node<T>::getData() 
{
	return m_data;
}

template<typename T>
inline void Node<T>::setData(T data)
{
	m_data = data;
}

template<typename T>
inline Node<T>::~Node()
{
	m_data = T();
	m_next = nullptr;
	m_prev = nullptr;
}

#endif