/*******************************
Author: Garrett Fechter
Purpose: Header file for Row
Date Created: 4/6/2018
Modifications:
		4/9/2018 Documented
*****************************/
#ifndef ROW
#define ROW

template<typename T>
class Array2D;

/****************************
Class: Row
Purpose: An ADT 2-dimensional array that uses Array1D
Manager Functions:
	Row(Array2D<T> & in_array, int row)
		Ctor that takes a 2DArray as well as which row# this is
	Row(const Array2D<T> & in_array, int row)
		Ctor that takes a const 2DArray as well as which row# this is
Methods:
	T & operator[](int column)
		Calls Array2D's Select method to get T& at column in this row
		specified
	const T & operator[](int column) const
		Calls Array2D's const Select method to get const T& at column 
		in this row specified
**********************/
template<typename T>
class Row
{
public:
	Row(Array2D<T> & in_array, int row);
	Row(const Array2D<T> & in_array, int row);
	T & operator[](int column);
	const T & operator[](int column) const;
private:
	const Array2D<T> & m_array2D; //the Array2D this row is part of
	const int m_row; //the number row this is inside Array2D
};

/******************************
Method: Row(Array2D<T> & in_array, int row)
Purpose: Ctor that takes a 2DArray as well as which row# this is
Precondition: Takes positive and inbounds row, and existing Array2D
Postcondition: Creates an instance of Row
*******************************/
template<typename T>
inline Row<T>::Row(Array2D<T> & in_array, int row) : m_array2D(in_array), m_row(row)
{
	if (row < 0)
	{
		throw Exception("Rows specified can't be negative");
	}
	if (row > in_array.GetRow())
	{
		throw Exception("Out of bounds");
	}
}

/******************************
Method: Row(const Array2D<T> & in_array, int row)
Purpose: Ctor that takes a const 2DArray as well as which row# this is
Precondition: Takes positive and inbounds row, and existing Array2D
Postcondition: Creates an instance of Row
*******************************/
template<typename T>
inline Row<T>::Row(const Array2D<T> & in_array, int row) : m_array2D(in_array), m_row(row)
{
	if (row < 0)
	{
		throw Exception("Rows specified can't be negative");
	}
	if (row > in_array.GetRow())
	{
		throw Exception("Out of bounds");
	}
}

/******************************
Method: operator[](int column)
Purpose: Subscript operator that calls Array2D's Select method to get T& at 
column in this row specified
Precondition: Takes inbounds and non-negative column
Postcondition: Returns T& to T specified by this row and column
*******************************/
template<typename T>
inline T & Row<T>::operator[](int column)
{
	if (column >= m_array2D.GetColumn())
		throw Exception("Out of bounds");
	if (column < 0)
		throw Exception("Out of bounds");
	//return const_cast <T &>(m_array2D.Select(m_row, column));
	return m_array2D.Select(m_row, column);
}

/******************************
Method: const operator[](int column)
Purpose: Subscript operator that calls Array2D's const Select method to get 
const T& at column in this row specified
Precondition: Takes inbounds and non-negative column
Postcondition: Returns const T& to T specified by this row and column
*******************************/
template<typename T>
inline const T & Row<T>::operator[](int column) const
{
	if (column >= m_array2D.GetColumn())
		throw Exception("Out of bounds");
	return m_array2D.Select(m_row, column);
}

#endif
