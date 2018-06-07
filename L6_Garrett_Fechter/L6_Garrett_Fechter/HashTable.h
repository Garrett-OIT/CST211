/*
 Author: Garrett Fechter
 Lab 6 - Hash Table
 Purpose: A header file for a ADT hash table
 Date Created: 6/7/2018
 Date Modified:
*/
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "Exception.h"
#include <list>
using std::list;
#include <vector>
using std::vector;
#include <utility>
using std::pair;

/*
 Class: HashTable
 Purpose: An ADT implementation of a hash table, which is an
	array of lists and handles collisions by chaining.
 Canonical functions:
	HashTable();
		a default constructor, m_buckets is 0 len
	HashTable(size_t len);
		ctor that set m_buckets length to len
	HashTable(const & HashTable copy);
		copy ctor
	HashTable & operator= (const & HashTable rhs);
		overloaded assignment op
	~HashTable();
		dtor
	Member functions:
	void Insert(K key, V value);
		insert a pair, uses hash on key to find correct bucket
		always uses % m_buckets len when determing bucket index
	void setHash(int(*hash(K key));
		sets the hash that's used for determing buckets
	V operator [] (K key);
		returns a value from key
	void Delete(K key);
		removes a pair using key
	void Traverse(void(*visit)(V value));
		traverse the whole hash table calling visit on each value
*/
template <typename K, typename V> 
//K key value, V value data
class HashTable
{
public:
	HashTable();
	HashTable(size_t len);
	HashTable(const HashTable & copy);
	HashTable & operator= (const HashTable & rhs);
	~HashTable();
	size_t getLen();
	void setLen(size_t len);
	void Insert(K key, V value);
	void setHash(int(*hash)(const K & data));
	//store the function ptr in data member, rehash
	V operator [] (K key);
	void Delete(K key);
	void Traverse(void(*visit)(V value));
private:
	vector<list<pair<K, V>>> m_buckets;
	int(*m_hash)(const K &);
};

/*
 Function: HashTable() 
 Purpose: default ctor 
 Entry: -
 Exit: empty buckets, nullptr hash
*/
template<typename K, typename V>
inline HashTable<K, V>::HashTable() : m_buckets(), m_hash(nullptr)
{ }

/*
 Function: HashTable(size_t len)
 Purpose: ctor that speicifes size of buckets
 Entry:  -
 Exit: hash is nullptr 
*/
template<typename K, typename V>
inline HashTable<K, V>::HashTable(size_t len) : m_buckets(len), m_hash(nullptr)
{ }

/*
Function: HashTable(const HashTable & copy)
Purpose: copy ctor
Entry: -
Exit: creates new HashTable with same data as copy
*/
template<typename K, typename V>
inline HashTable<K, V>::HashTable(const HashTable & copy) : m_buckets(copy.m_buckets), m_hash(copy.m_hash)
{ }

/*
Function: operator=(const Hashtable & rhs)
Purpose: overloaded assignment operator
Entry: -
Exit: Returns lhs after assigning all data from rhs
*/
template<typename K, typename V>
inline HashTable<K, V> & HashTable<K, V>::operator=(const HashTable & rhs)
{
	m_buckets = rhs.m_buckets;
	m_hash = rhs.m_hash;
	return *this;
}

/*
Function: ~HashTable
Purpose: dtor
Entry: -
Exit: clears all data and resets members to intial state (empty)
*/
template<typename K, typename V>
inline HashTable<K, V>::~HashTable()
{
	m_buckets.clear();
	m_buckets.resize(0);
	m_hash = nullptr;
}

/*
Function: getLen
Purpose: getter for length of buckets
Entry: -
Exit: returns length of buckets
*/
template<typename K, typename V>
inline size_t HashTable<K, V>::getLen()
{
	return m_buckets.size();
}

/*
Function: setLen(size_t len)
Purpose: Setter for buckets length
Entry: -
Exit: Changes the buckjets length, potentially losing data if any 
	data is stored in at the end of buckets
*/
template<typename K, typename V>
inline void HashTable<K, V>::setLen(size_t len)
{
	m_buckets.resize(len);
}

/*
Function: Insert(K key, V value)
Purpose: Insert a pair into the hashtable 
Entry: -
Exit: Inserts pair into buckets. Uses chaining when collisions occur
*/
template<typename K, typename V>
inline void HashTable<K, V>::Insert(K key, V value)
{
	if (m_hash == nullptr)
		throw Exception("Hash function not set\n");
	if (m_buckets.size() == 0)
		throw Exception("Empty buckets length\n");
	size_t index = m_hash(key) % m_buckets.size();
	pair<K, V> ins(key, value);
	m_buckets[index].push_back(ins);
}

/*
Function: setHash(int(*hash)(const K & data))
Purpose: Change the hash function used to store table
Entry: hash is the new hash to use
Exit: changes the structure of the table using the new hash
*/
template<typename K, typename V>
inline void HashTable<K, V>::setHash(int(*hash)(const K & data))
{
	if (hash == nullptr)
		throw Exception("Hash can't be empty\n");
	vector<list<pair<K, V>>> new_buckets(m_buckets.size());
	for (auto vIter = m_buckets.begin(); vIter != m_buckets.end(); vIter++) 
	{
		for (auto lIter = (*vIter).begin(); lIter != (*vIter).end(); lIter++) 
		{
			//insert 
			size_t index = hash((*lIter).first) % m_buckets.size();
			pair<K, V> ins((*lIter).first, (*lIter).second);
			new_buckets[index].push_back(ins);
		}
	}
	m_buckets = new_buckets;
	m_hash = hash;
}

/*
Function: operator[] (K key)
Purpose: overloaded [] operator which returns the V data at key
Entry: key is the key of a pair inside the table. hash cannot be null in order to find the pair
Exit: returns the V data found matching key otherwise returns empty V
*/
template<typename K, typename V>
inline V HashTable<K, V>::operator[](K key)
{
	V ret;
	if ((m_hash != nullptr) && m_buckets.size() != 0)
	{
		list < pair<K, V>> bucket;
		bucket = m_buckets[m_hash(key) % m_buckets.size()];
		bool found = false;
		while (!found && !bucket.empty())
		{
			ret = bucket.front().second;
			if (bucket.front().first == key)
				found = true;
			bucket.pop_front();
		}
		if (!found)
		{
			V empty;
			ret = empty;
		}
	}
	return ret;
}

/*
Function:Delete(K key)
Purpose: remove a pair with key matching key from the table
Entry: -
Exit: remove a pair with key matching key from the table, if found
*/
template<typename K, typename V>
inline void HashTable<K, V>::Delete(K key)
{
	if (m_hash == nullptr)
		throw Exception("Empty hash function\n");
	if (m_buckets.size() != 0)
	{
		list<pair<K, V>> *bucket = &m_buckets[m_hash(key) % m_buckets.size()];
		auto iter = bucket->begin();
		bool found = false;
		for (; !found && iter != bucket->end();)
		{
			if ((*iter).first == key)
			{
				found = true;
				bucket->remove(*iter);
			}
			else
				iter++;
		}
	}
}

/*
Function: Traverse(void(*visit)(V value))
Purpose: traverse the table, visiting each value inside a pair
Entry: visit is the function to perform on each V data inside a pair
Exit: -
*/
template<typename K, typename V>
inline void HashTable<K, V>::Traverse(void(*visit)(V value))
{
	for (auto vIter = m_buckets.begin(); vIter != m_buckets.end(); vIter++) 
	{
		for (auto lIter = (*vIter).begin(); lIter != (*vIter).end(); lIter++) 
		{
			visit((*lIter).second);
		}
	}
}

#endif
