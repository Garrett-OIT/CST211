#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>

#define DEBUG_TESTING

using std::cout;

template<typename T>
class LL
{
public:
	LL();
	LL(const LL & copy);
	LL<T> & operator = (const LL & rhs);
	void Append(T data);
#ifdef DEBUG_TESTING
	void PrintForwards();
	void PrintBackwards();
	Node<T> * getHead();
	Node<T> * getTail();
#endif
	~LL();
private:
	Node<T> *m_head;
	Node<T> *m_tail;
};

#endif

template<typename T>
inline LL<T>::LL() : m_head(nullptr), m_tail(nullptr)
{ }

template<typename T>
inline LL<T>::LL(const LL & copy)
{
	Node<T> *copyPointer = copy.m_head;
	if (copyPointer != nullptr)
	{
		m_head = new Node<T>;
		m_tail = m_head;
		Node<T> *copyingTo = m_head;
		copyingTo->setData(copyPointer->getData());
		copyPointer = copyPointer->getNext();
		while (copyPointer != nullptr)
		{
			copyingTo->setNext(new Node<T>);
			copyingTo = copyingTo->getNext();
			copyingTo->setPrev(m_tail);
			m_tail = copyingTo;
			copyingTo->setData(copyPointer->getData());
			copyPointer = copyPointer->getNext();
		}
	}
}

template<typename T>
inline LL<T> & LL<T>::operator=(const LL & rhs)
{
	if (this != &rhs) 
	{
		~*this; //delete
		m_head = nullptr;
		m_tail = nullptr;
		Node *copyPointer = rhs.m_head;
		if (copyPointer != nullptr)
		{
			m_head = new Node;
			m_tail = m_head;
			Node *copyingTo = m_head;
			copyingTo->setData(copyPointer->getData());
			copyPointer = copyPointer->getNext();
			while (copyPointer != nullptr)
			{
				copyingTo->setNext(new Node);
				copyingTo = copyingTo->getNext();
				m_tail = copyingTo;
				copyingTo->setData(copyPointer->getData());
				copyPointer = copyPointer->getNext();
			}
		}
	}
	return *this;
}

template<typename T>
inline void LL<T>::Append(T data)
{
	if (m_tail != nullptr)
	{
		m_tail->setNext(new Node<T>);
		m_tail->getNext()->setData(data);
		m_tail->getNext()->setPrev(m_tail);
		m_tail = m_tail->getNext();
	}
	else 
	{
		Node<T> *newHeadTail = new Node<T>;
		newHeadTail->setData(data);
		m_head = newHeadTail;
		m_tail = newHeadTail;
	}
}

#ifdef DEBUG_TESTING
template<typename T>
inline void LL<T>::PrintForwards()
{
	Node<T> *current = m_head;
	while (current != nullptr)
	{
		cout << current->getData() << " ";
		current = current->getNext();
	}
	cout << "\n";
}
template<typename T>
inline void LL<T>::PrintBackwards()
{
	Node<T> *current = m_tail;
	while (current != nullptr)
	{
		cout << current->getData() << " ";
		current = current->getPrev();
	}
	cout << "\n";
}

template<typename T>
inline Node<T> * LL<T>::getHead()
{
	return m_head;
}
template<typename T>
inline Node<T>* LL<T>::getTail()
{
	return m_tail;
}
#endif

template<typename T>
inline LL<T>::~LL()
{
	Node<T> * deleteMe = m_head;
	Node<T> * current = m_head;
	while (current != nullptr) 
	{
		deleteMe = current;
		current = deleteMe->getNext();
		delete deleteMe;
	}
	m_head = nullptr;
	m_tail = nullptr;
}
