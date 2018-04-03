/*******************************
Author: Garrett Fechter
Purpose: Header file for OneDimArray
Date Created: 4/2/2018
Modifications:

*****************************/

#ifndef ONE_DIM_ARRAY
#define ONE_DIM_ARRAY

#define NegativeLength -1
#define outOfBounds -1

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
 Methods:
	int getStartIndex()
		Returns m_start_index by value
	int getLength()
		Returns m_length by value
	operator[](int index)
		Returns the T specified by index
********************************************************/
public:
	OneDimArray<T>();//default ctor, m_array is nullptr, m_length = 0, m_start_index = 0
	OneDimArray<T>(int length, int start_index); //a convenient empty ctor
	T & operator[](int index);//overloaded [] operator
	int getStartIndex();//returns m_start_index by value
	int getLength();//returns m_length by value
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
OneDimArray<T>::OneDimArray(int length, int start_index = 0) : m_array(nullptr), m_length(length), m_start_index(start_index)
{
	if (length < 0)
		throw NegativeLength;
	if (length == 0) 
	{
		m_array = nullptr; //empty array
	}
	else //not empty
	{
		m_array = new T[length]; //make enough room for the length of T's
		for (int i = 0; i < length; i++) 
		{
			m_array = T(); //each entry of length is default ctor of T
		}
	}
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
	if (index < m_start_index)
		throw outOfBounds;
	int absolute_index = index - m_start_index; //gets the absolute index of wanted element
	if (absolute_index > (length - 1))
		throw outOfBounds; //tried to return element beyond length
	return m_array[absolute_index];
}

/********************************
 Method: getStartIndex
 Purpose: A getter for m_start_index
 Precondition: -
 Postcondition: -
***********************************/
template <typename T>
int OneDimArray<T>::getStartIndex() 
{
	return m_start_index;
}

/********************************
Method: getLength
Purpose: A getter for m_length
Precondition: -
Postcondition: -
***********************************/
template <typename T>
int OneDimArray<T>::getLength()
{
	return m_length;
}

#endif