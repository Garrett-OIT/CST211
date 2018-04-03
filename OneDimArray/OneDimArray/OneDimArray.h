/*******************************
Author: Garrett Fechter
Purpose: Header file for OneDimArray
Date Created: 4/2/2018
Modifications:

*****************************/

#include "Exception.h"

#ifndef ONE_DIM_ARRAY
#define ONE_DIM_ARRAY

template <typename T>
class OneDimArray 
{
/*******************************************************
 Class: OneDimArray
 Purpose: A single dimensional dynamic array ADT (templated)
 Manager Functions:
	OneDimArray()
		Creates an empty array with length of 0 and a start_index of 0
	OneDimArray(int length, int start_index)
		Creates an array of m_length length and m_start_index start_index
	OneDimArray(const Array & copy)
		Copy ctor
	~OneDimArray()
		A dtor
	 OneDimArray & operator=(const OneDimArray & rhs)
		Overloaded assignment operator
 Methods:
	int getStartIndex()
		Returns m_start_index by value
	void setStartIndex(int start_index)
		sets m_start_index to start_index
	int getLength()
		Returns m_length by value
	void setLength(int length)
		changes the m_length. This will delete/initialize data
	operator[](int index)
		Returns the T specified by index
********************************************************/
public:
	OneDimArray<T>();//default ctor, m_array is nullptr, m_length = 0, m_start_index = 0
	OneDimArray<T>(int length, int start_index = 0); //a convenient empty ctor
	~OneDimArray<T>(); //dtor
	OneDimArray(const OneDimArray & copy); //a copy ctor
	OneDimArray<T> & operator=(const OneDimArray<T> & rhs); //assignment operator
	T & operator[](int index);//overloaded [] operator
	int GetStartIndex();//returns m_start_index by value
	void SetStartIndex(int start_index);//setter for m_start_index
	int GetLength();//returns m_length by value
	void SetLength(int length);//sets m_length, deletes/initializes data
private:
	T* m_array;		//pointer to first element
	int m_length;		//number of elements
	int m_start_index;	//the starting index
};

/******************************
 Method: OneDimArray
 Purpose: A default constructor for OneDimArray
 Precondition: -
 Postcondition: Creates an instance of OneDimArray with nullptr m_array,
	m_lenght = 0, m_start_index = 0
*******************************/
template <typename T>
OneDimArray<T>::OneDimArray() : m_array(nullptr), m_length(0), m_start_index(0)
{}

/******************************
Method: OneDimArray
Purpose: A convenient constructor for OneDimArray
Precondition: Takes a unsigned int length and int start_index
Postcondition: Creates an instance of OneDimArray empty m_array,
m_length = length, m_start_index = start_index, based on passed args
*******************************/
template <typename T>
OneDimArray<T>::OneDimArray(int length, int start_index) : m_array(nullptr), m_length(length), m_start_index(start_index)
{
	if (length < 0) 
	{
		char err[] = "Length specified in ctor was negative";
		throw new Exception(err);
	}
	if (length == 0) 
	{
		m_array = nullptr; //empty array
	}
	else //not empty
	{
		m_array = new T[length]; //make enough room for the length of T's
		for (int i = 0; i < length; i++) 
		{
			m_array[i] = T(); //each entry of length is default ctor of T
		}
	}
}

/********************************
Method: ~OneDimArray()
Purpose: A destructor
Precondition: -
Postcondition: Frees m_array memory, sets length to 0
***********************************/
template<typename T>
OneDimArray<T>::~OneDimArray()
{
	delete[] m_array;
	m_length = 0;
}

/********************************
Method: OneDimArray(const OneDimArray & copy)
Purpose: A (deep) copy ctor
Precondition: -
Postcondition: Creates a new OneDimArray, copying copy
***********************************/
template<typename T>
OneDimArray<T>::OneDimArray(const OneDimArray & copy)
{
	m_length = copy.m_length;
	m_start_index = copy.m_start_index;
	m_array = nullptr;
	if (copy.m_array) //if not null 
	{
		m_array = new T[copy.m_length];
		for (int i = 0; i < m_length; i++) 
		{
			m_array[i] = copy.m_array[i];
		}
	}
}

/********************************
Method: operator=
Purpose: Overloaded assignment operator
Precondition: -
Postcondition: Sets lhs values to rhs values
***********************************/
template<typename T>
OneDimArray<T> & OneDimArray<T>::operator=(const OneDimArray<T> & rhs)
{
	if (this != &rhs) //check for self assignment 
	{
		//isn't self assignment
		delete[] m_array;//delete lhs data
		m_length = rhs.m_length;
		m_start_index = rhs.m_start_index;
		m_array = nullptr;
		if (rhs.m_array) //if not null 
		{
			m_array = new T[rhs.m_length];
			for (int i = 0; i < m_length; i++)
			{
				m_array[i] = rhs.m_array[i];
			}
		}
	}
	return *this;
}

/********************************
Method: operator[]
Purpose: Gets the element specified at index
Precondition: Takes an int index, which is element in relation to start_index
Postcondition: Returns element T passed by reference
***********************************/
template <typename T>
T & OneDimArray<T>::operator[](int index)
{
	if (m_array == nullptr)
	{
		char err_msg[] = "[] operator used when no data present";//array is nullptr still
		Exception error(err_msg);
		throw error;
	}
	if (index < m_start_index)
	{
		char err_msg[] = "Tried to access below bounds in [] operator"; //tried to access element before starting index
		Exception error(err_msg);
		throw error;
	}
	int absolute_index = index - m_start_index; //gets the absolute index of wanted element
	if (absolute_index > (m_length - 1))
	{
		char err_msg[] = "Tried to access beyond bounds in [] operator";//tried to return element beyond length
		Exception error(err_msg);
		throw error;
	}
	return m_array[absolute_index];
}

/********************************
 Method: getStartIndex
 Purpose: A getter for m_start_index
 Precondition: -
 Postcondition: -
***********************************/
template <typename T>
int OneDimArray<T>::GetStartIndex() 
{
	return m_start_index;
}

/********************************
Method: setStartIndex
Purpose: A setter for m_start_index
Precondition: -
Postcondition: -
***********************************/
template<typename T>
inline void OneDimArray<T>::SetStartIndex(int start_index)
{
	m_start_index = start_index;
}

/********************************
Method: getLength
Purpose: A getter for m_length
Precondition: -
Postcondition: -
***********************************/
template <typename T>
int OneDimArray<T>::GetLength()
{
	return m_length;
}

/********************************
Method: setLength
Purpose: A setter for m_length
Precondition: -
Postcondition: Copies data into new array of specified length, truncating
	data if new length is shorter
***********************************/
template<typename T>
inline void OneDimArray<T>::SetLength(int length)
{
	if (length < 0) 
	{
		char err[] = "Invalid length specified";
		Exception error(err);
		throw error;
	}
	if (length < m_length) //length is shorter- losing some data
	{
		T* new_array = new T[length]; //allocate smaller space
		for (int i = 0; i < length; i++) 
		{
			new_array[i] = m_array[i]; //copy entries
		}
		delete[] m_array;//get rid of old data
		m_array = new_array;//save new data
		m_length = length;//update length
	}
	else if (length > m_length) //longer length
	{
		T* new_array = new T[length];
		for (int i = 0; i < m_length; i++) 
		{
			new_array[i] = m_array[i]; //copy 
		}
		for (int i = m_length; i < length; i++) 
		{
			new_array[i] = T(); //initialize new elements
		}
		delete[] m_array; //get rid of old data
		m_array = new_array; //save new data
		m_length = length; //update length
	}
}

#endif