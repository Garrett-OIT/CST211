#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>
#include "Exception.h"
#define DEBUG_TESTING

#include "AbstractIterator.h"

using std::cout;

template<typename T>
class LL
{
private:
	Node<T> *m_head;
	Node<T> *m_tail;
public:
	LL();
	LL(const LL & copy);
	LL<T> & operator = (const LL & rhs);
	void Append(T data);
	void Prepend(T data);
	bool isEmpty() const;
	const T & First() const;
	const T & Last() const;
	void Extract(const T & data);
	void InsertBefore(T newData, const T & oldData);
	void InsertAfter(T newData, const T & oldData);
	void Purge();
	~LL();
	class ListIterator : public AbstractIterator<T>
	{
	public:
		T GetCurrent();
	protected:
		Node<T> *m_current;
		const LL<T> * m_list;
	};
	class ForwardsIterator : public ListIterator 
	{
	public:
		ForwardsIterator(const LL<T> &list);
		~ForwardsIterator();
		void MoveNext();
		void Reset();
		bool isDone();
	};
	class BackwardsIterator : public ListIterator 
	{
	public:
		BackwardsIterator(const LL<T> &list);
		~BackwardsIterator();
		void MoveNext();
		void Reset();
		bool isDone();
	};
#ifdef DEBUG_TESTING
	void PrintForwards();
	void PrintBackwards();
	Node<T> * getHead();
	Node<T> * getTail();
#endif
};


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
		this->Purge(); //delete
		m_head = nullptr;
		m_tail = nullptr;
		Node<T> *copyPointer = rhs.m_head;
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

template<typename T>
inline void LL<T>::Prepend(T data)
{
	Node<T> *oldHead = m_head;
	Node<T> *newHead = new Node<T>;
	newHead->setData(data);
	if (m_tail == nullptr)
		m_tail = newHead;
	m_head = newHead;
	newHead->setNext(oldHead);
	if (nullptr != oldHead)
		oldHead->setPrev(newHead);
}

template<typename T>
inline bool LL<T>::isEmpty() const
{
	bool empty = false;
	if (m_head == nullptr)
		empty = true;
	return empty;
}

template<typename T>
inline const T & LL<T>::First() const
{
	if (m_head == nullptr)
		throw Exception("Tried to call First on empty list\n");
	return m_head->getData();
}

template<typename T>
inline const T & LL<T>::Last() const
{
	if (m_tail == nullptr)
		throw Exception("Tried to call Last on empty list\n");
	return m_tail->getData();
}

template<typename T>
inline void LL<T>::Extract(const T & data)
{
	Node<T> * current = m_head;
	Node<T> * trail = nullptr;
	bool found = false;
	while (!found)
	{
		if (current == nullptr)
			throw Exception("Did not find data to Extract\n");
		if (current->getData() == data) 
		{
			found = true;
			if (current->getNext() == nullptr) //extract tail
			{
				if (m_head == m_tail) //only element
					m_head = nullptr;
				m_tail = current->getPrev();
			}
			else
				current->getNext()->setPrev(trail);
			if (trail == nullptr) //extract head
			{
				if (m_head == m_tail) //only element
					m_tail = nullptr;
				m_head = current->getNext();
			}
			else
				trail->setNext(current->getNext());
			delete current;
		}
		else 
		{
			trail = current;
			current = current->getNext();
		}
	}
}

template<typename T>
inline void LL<T>::InsertBefore(T newData, const T & oldData)
{
	Node<T> * current = m_head;
	Node<T> * trail = nullptr;
	bool found = false;
	while (!found)
	{
		if (current == nullptr)
			throw Exception("Did not find data to Insert Before\n");
		if (current->getData() == oldData) 
		{
			found = true;
			Node<T> *newNode = new Node<T>;
			newNode->setData(newData);
			newNode->setNext(current);
			newNode->setPrev(trail);
			if (trail == nullptr) //inserting before head
				m_head = newNode;
			else
				trail->setNext(newNode);
			current->setPrev(newNode);
		}
		else 
		{
			trail = current;
			current = current->getNext();
		}
	}
}

template<typename T>
inline void LL<T>::InsertAfter(T newData, const T & oldData)
{
	Node<T> * current = m_head;
	bool found = false;
	while (!found)
	{
		if (current == nullptr)
			throw Exception("Did not find data to Insert After\n");
		if (current->getData() == oldData) 
		{
			found = true;
			Node<T> *newNode = new Node<T>;
			newNode->setData(newData);
			newNode->setPrev(current);
			if (current->getNext() == nullptr) //inserting after tail 
				m_tail = newNode;
			else
				current->getNext()->setPrev(newNode);
			newNode->setNext(current->getNext());
			current->setNext(newNode);
		}
		else 
		{
			current = current->getNext();
		}
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
inline void LL<T>::Purge()
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


template<typename T>
inline T LL<T>::ListIterator::GetCurrent()
{
	if (ListIterator::m_current == nullptr)
		throw Exception("Called GetCurrent on nullptr");
	return ListIterator::m_current->getData();
}


template<typename T>
inline LL<T>::ForwardsIterator::~ForwardsIterator()
{
	ListIterator::m_current = nullptr;
	ListIterator::m_list = nullptr;
}

template<typename T>
inline void LL<T>::ForwardsIterator::MoveNext()
{
	if (ListIterator::m_current != nullptr)
		ListIterator::m_current = ListIterator::m_current->getNext();
}

template<typename T>
inline void LL<T>::ForwardsIterator::Reset()
{
	ListIterator::m_current = ListIterator::m_list->m_head;
}

template<typename T>
inline bool LL<T>::ForwardsIterator::isDone()
{
	return (nullptr == ListIterator::m_current);
}

template<typename T>
inline LL<T>::ForwardsIterator::ForwardsIterator(const LL<T> &list) 
{
	ListIterator::m_list = &list;
	ListIterator::m_current = list.m_head;
}
		
template<typename T>
inline LL<T>::BackwardsIterator::~BackwardsIterator()
{
	ListIterator::m_current = ListIterator::m_list->m_tail;
}

template<typename T>
inline void LL<T>::BackwardsIterator::MoveNext()
{
	if (ListIterator::m_current != nullptr)
		ListIterator::m_current = ListIterator::m_current->getPrev();
}

template<typename T>
inline void LL<T>::BackwardsIterator::Reset()
{
	ListIterator::m_current = ListIterator::m_list->m_tail;
}

template<typename T>
inline bool LL<T>::BackwardsIterator::isDone()
{
	return (nullptr == ListIterator::m_current);
}

template<typename T>
inline LL<T>::BackwardsIterator::BackwardsIterator(const LL<T> &list) 
{
	ListIterator::m_list = &list;
	ListIterator::m_current = list.m_tail;
}
#endif
