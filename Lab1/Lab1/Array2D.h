/*******************************
Author: Garrett Fechter
Purpose: Header file for Array2D
Date Created: 4/6/2018
Modifications:
		4/9/2018 Ensured any exceptions from Row were caught
				 Documented
		4/10/2018 Minor linting
*****************************/

#include "Array1D.h"
#include "Row.h"

#ifndef ARRAY2D
#define ARRAY2D


/****************************
Class: Array2D
Purpose: An ADT 2-dimensional array that uses Array1D
Manager Functions:
	Array2D();
	Array2D(int row, int col);
	Array2D(const Array2D<T> & copy);
	~Array2D();
	Array2D<T> & operator=(const Array2D<T> & rhs);
Methods:
	Row<T> operator[](int index);
		A subscript operator that returns a row of data
	const Row<T> operator[](int index) const;
		A subscript operator that returns a const row of data
	int getRow() const;
		Getter for m_row
	void setRow(int rows);
		Setter for m_row. If longer, allocates & initializes new data. 
		If shorter, deallocates that extra stuff. Reallocates either way
	int getColumn() const;
		Getter for m_col
	void setColumn(int columns);
		Setter for m_col. If longer, allocates & initializes new data.
		If shorter, deallocates that extra stuff. Reallocates either way
	T & Select(int row, int column);
		Gets a T & from the 2D array
	const T & Select(int row, int column) const;
		Gets a const T & from the 2D array
**********************/
template<typename T>
class Array2D
{
public:
	Array2D();
	Array2D(int row, int col);
	Array2D(const Array2D<T> & copy);
	~Array2D();
	Array2D<T> & operator=(const Array2D<T> & rhs);
	Row<T> operator[](int index);
	const Row<T> operator[](int index) const;
	int GetRow() const;
	void SetRow(int rows);
	int GetColumn() const;
	void SetColumn(int columns);
	T & Select(int row, int column);
	const T & Select(int row, int column) const;
private:
	Array1D<T> m_array; //array of 1D arrays
	int m_row; //number of rows
	int m_col; //number of columns
};

/******************************
Method: Array2D
Purpose: A default constructor for Array2D
Precondition: -
Postcondition: Creates an instance of Array2D with nullptr m_array,
m_row = 0, m_col = 0
*******************************/
template<typename T>
inline Array2D<T>::Array2D() : m_array(), m_row(0), m_col(0)
{ }

/******************************
Method: Array2D(int row, int col)
Purpose: A constructor for Array2D that specifies rows and cols
Precondition: -
Postcondition: Creates an instance of Array2D with m_array of the size 
specified by row and col, m_row = row, m_col = col. Throws exception if
try to specify negative col or row
*******************************/
template<typename T>
inline Array2D<T>::Array2D(int row, int col) : m_array(row * col), m_row(row), m_col(col)
{
	if (row < 0 || col < 0)
		throw Exception("Tried to set negative row or col");
}

/******************************
Method: Array2D(int row, int col)
Purpose: A copy constructor for Array2D 
Precondition: Copies an existing Array2D
Postcondition: Creates a new (deep) copy of copy, with same data
and row and column. Uses Array1D's copy ctor for m_array
*******************************/
template<typename T>
inline Array2D<T>::Array2D(const Array2D & copy) : m_array(copy.m_array), m_row(copy.m_row), m_col(copy.m_col)
{ }

/******************************
Method: ~Array2D
Purpose: A destructor for Array2D
Precondition: Deallocates the memory of m_array
Postcondition: Deallocates memory (using Array1D's dtor) and 
resets other data members to 0
*******************************/
template<typename T>
inline Array2D<T>::~Array2D()
{
	m_row = 0;
	m_col = 0;
}

/******************************
Method: operator=
Purpose: An assignment operator for Array2D
Precondition: Takes an existing Array2D in rhs
Postcondition: Creates a new (deep) copy of rhs, with same data
and row and column. Uses Array1D's copy ctor for m_array. Returns
reference to new Array2D (or original object if self assinment attempted)
*******************************/
template<typename T>
inline Array2D<T> & Array2D<T>::operator=(const Array2D<T> & rhs)
{
	if (this != *rhs) //check for self assignment
	{
		m_array = rhs.m_array; //should delete m_array
		m_row = rhs.m_row;
		m_col = rhs.m_col;
	}
	return *this;
}

/******************************
Method: operator[]
Purpose: A subscript operator for Array2D
Precondition: -
Postcondition: returns a new row with index specified 
*******************************/
template<typename T>
inline Row<T> Array2D<T>::operator[](int index)
{
	try
	{
		return Row<T>(*this, index);
	}
	catch (Exception e) 
	{
		throw e; //Row threw exception, invalid index
	}
}

/******************************
Method: operator[]
Purpose: A const subscript operator for Array2D
Precondition: -
Postcondition: returns a new const row with index specified
*******************************/
template<typename T>
inline const Row<T> Array2D<T>::operator[](int index) const
{
	return Row<T>(*this, index);
}

/******************************
Method: getRow()
Purpose: A getter for m_row
Precondition: -
Postcondition: Returns m_row
*******************************/
template<typename T>
inline int Array2D<T>::GetRow() const
{
	return m_row;
}

/******************************
Method: setRow()
Purpose: A setter for m_row
Precondition: Takes a positive rows
Postcondition: If longer, allocates & initializes new data. 
	If shorter, deallocates that extra stuff. Reallocates either way
*******************************/
template<typename T>
inline void Array2D<T>::SetRow(int rows)
{
	if (rows < 0)
		throw Exception("Tried to set rows negative");
	m_array.SetLength(rows * m_col);
	m_row = rows;
}

/******************************
Method: getColumn()
Purpose: A getter for m_col
Precondition: -
Postcondition: Returns m_col
*******************************/
template<typename T>
inline int Array2D<T>::GetColumn() const
{
	return m_col;
}

/******************************
Method: setColumn()
Purpose: A setter for m_col
Precondition: Takes a positive columns
Postcondition: If longer, allocates & initializes new data.
If shorter, deallocates that extra stuff. Reallocates either way
*******************************/
template<typename T>
inline void Array2D<T>::SetColumn(int columns)
{
	if (columns < 0)
		throw Exception("Tried to set columns negative");
	int shorter = (columns > m_col) ? m_col : columns;
	Array1D<T> newArray(columns * m_row);
	for (int i = 0; i < m_row; i++) //for each row
	{
		for (int j = 0; j < shorter; j++) //for each column
		{
			newArray[(i * columns) + j] = m_array[(i * m_col) + j];
		}
		for (int j = shorter; j < columns; j++) //empty spaces if longer
		{
			newArray[(i * columns) + j] = T();
		}
	}
	m_array = newArray;
	m_col = columns;
}

/******************************
Method: T& Select()
Purpose: Get a T & from the array
Precondition: Takes row and column within boundaries
Postcondition:Throws exception if out of bounds.
	Otherwise returned T& specifed by row/column
*******************************/
template<typename T>
inline T & Array2D<T>::Select(int row, int column)
{
	if (row >= m_row || column >= m_col)
	{
		throw Exception("Out of bounds, beyond");
	}
	if (row < 0 || column < 0)
	{
		throw Exception("Out of bounds, tried to access <0");
	}
	return m_array[(m_col * row) + column];
}

/******************************
Method: const T & Select()
Purpose: Get a const T & from the array
Precondition: Takes row and column within boundaries
Postcondition:Throws exception if out of bounds.
Otherwise returned const T& specifed by row/column
*******************************/
template<typename T>
inline const T & Array2D<T>::Select(int row, int column) const
{
	if (row >= m_row || column >= m_col)
	{
		throw Exception("Out of bounds, beyond");
	}
	if (row < 0 || column < 0)
	{
		throw Exception("Out of bounds, tried to access <0");
	}
	return m_array[(m_col * row) + column];
}

#endif