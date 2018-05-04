//Author: Garrett Fechter
//Created 5/2/2018
#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include "Array1D.h"

template<typename T>
class CircularQueue
{
public:
	CircularQueue();
	CircularQueue(int length);
	CircularQueue(const CircularQueue<T> & copy);
	~CircularQueue();
	CircularQueue<T> & operator = (const CircularQueue<T> & rhs);
	void Enqueue(T data);
	T Dequeue();
	T & Front();
	int Size() const;
	bool isEmpty() const;
	bool isFull() const;
private:
	Array1D<T> m_array;
	int m_first; //the index of the first element in line
	int m_last; //the index of the last element in line
};

#endif

template<typename T>
inline CircularQueue<T>::CircularQueue() : m_array(), m_first(-1), m_last(-1)
{ }

template<typename T>
inline CircularQueue<T>::CircularQueue(int length) : m_array(length), m_first(-1), m_last(-1)
{ }

template<typename T>
inline CircularQueue<T>::CircularQueue(const CircularQueue<T>& copy) : m_array(copy.m_array), m_first(copy.m_first), m_last(copy.m_last)
{ }

template<typename T>
inline CircularQueue<T>::~CircularQueue()
{
	m_first = -1;
	m_last = -1;
}

template<typename T>
inline CircularQueue<T>& CircularQueue<T>::operator=(const CircularQueue<T>& rhs)
{
	m_array = rhs.m_array;
	m_first = rhs.m_first;
	m_last = rhs.m_last;
	return *this;
}

template<typename T>
inline void CircularQueue<T>::Enqueue(T data)
{
	if (this->isFull())
		throw Exception("Can't Enqueue with full queue\n");
	if (m_first == -1)
		m_first++;
	m_last++;
	m_last = m_last % m_array.GetLength();
	m_array[m_last] = data;
}

template<typename T>
inline T CircularQueue<T>::Dequeue()
{
	if (m_first < 0)
		throw Exception("Can't Dequeue on empty list\n");
	T returnVal = m_array[m_first];
	if (m_first == m_last) 
	{
		m_last = -1;
		m_first = -1;
	}
	else 
	{
		m_first++;
		m_first = m_first % m_array.GetLength();
	}
	return returnVal;
}

template<typename T>
inline T & CircularQueue<T>::Front()
{
	if (m_first < 0)
		throw Exception("Can't call Front on empty queue\n");
	return m_array[m_first];
}

template<typename T>
inline int CircularQueue<T>::Size() const
{
	int count = 0;
	if (m_first != -1 && m_array.GetLength() != 0) //pesky mod 0 
	{
		count++;//has a first
		for (int i = m_first; i != m_last; i++) 
		{
			count++;
			i = i % m_array.GetLength();
		}
	}
	return count;
}

template<typename T>
inline bool CircularQueue<T>::isEmpty() const
{
	bool empty = false;
	if (m_first == -1)
		empty = true;
	return empty;
}

template<typename T>
inline bool CircularQueue<T>::isFull() const
{
	bool full = false;
	if (m_last == m_first - 1)
		full = true;
	if (m_first == 0 && m_last == (m_array.GetLength() - 1))
		full = true;
	return full;
}
