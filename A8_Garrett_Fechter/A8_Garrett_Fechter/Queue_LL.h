#ifndef QUEUE_LL
#define QUEUE_LL
#include "LinkedList.h"

template<typename T>
class Queue_LL {
public:
	Queue_LL();
	Queue_LL(const Queue_LL<T> & copy);
	~Queue_LL();
	Queue_LL<T> & operator = (const Queue_LL<T> & rhs);
	void Enqueue(T data);
	T Dequeue(void);
	T & Front() const;
	int Size() const;
	bool isEmpty() const;
private:
	LL<T> m_queue;
	int m_size;
};

#endif

template<typename T>
inline Queue_LL<T>::Queue_LL() : m_queue(), m_size(0)
{ }

template<typename T>
inline Queue_LL<T>::Queue_LL(const Queue_LL<T> & copy) : m_queue(copy.m_queue), m_size(copy.m_size)
{ }

template<typename T>
inline Queue_LL<T>::~Queue_LL()
{
	m_queue.Purge();
	m_size = 0;
}

template<typename T>
inline Queue_LL<T> & Queue_LL<T>::operator=(const Queue_LL<T> & rhs)
{
	m_queue = rhs.m_queue;
	m_size = rhs.m_size;
	return *this;
}

template<typename T>
inline void Queue_LL<T>::Enqueue(T data)
{
	m_queue.Append(data);
	m_size++;
}

template<typename T>
inline T Queue_LL<T>::Dequeue(void)
{
	T first = m_queue.First();
	m_queue.Extract(first);
	m_size--;
	return first;
}

template<typename T>
inline T & Queue_LL<T>::Front() const
{
	return m_queue.First();
}

template<typename T>
inline int Queue_LL<T>::Size() const
{
	return m_size;
}

template<typename T>
inline bool Queue_LL<T>::isEmpty() const
{
	return m_queue.isEmpty();
}
