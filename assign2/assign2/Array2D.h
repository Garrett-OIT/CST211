#include "Array1D.h"
#include "Row.h"

#ifndef ARRAY2D
#define ARRAY2D

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
	int getRow() const;
	void setRow(int rows);
	int getColumn() const;
	void setColumn(int columns);
	T & Select(int row, int column);
	const T & Select(int row, int column) const;
private:
	Array1D<T> m_array; //array of 1D arrays
	int m_row; //number of rows
	int m_col; //number of columns
};

template<typename T>
inline Array2D<T>::Array2D() : m_array(), m_row(0), m_col(0)
{ }

template<typename T>
inline Array2D<T>::Array2D(int row, int col) : m_array(row*col), m_row(row), m_col(col)
{
	if (row < 0 || col < 0)
		throw Exception("Tried to set negative row or col");
}

template<typename T>
inline Array2D<T>::Array2D(const Array2D & copy) : m_array(copy.m_array), m_row(copy.m_row), m_col(copy.m_col)
{ }

template<typename T>
inline Array2D<T>::~Array2D()
{
	m_array.~Array1D();
	m_row = 0;
	m_col = 0;
}

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

template<typename T>
inline Row<T> Array2D<T>::operator[](int index)
{
	return Row<T>(*this, index);
}

template<typename T>
inline const Row<T> Array2D<T>::operator[](int index) const
{
	return Row<T>(*this, index);
}

template<typename T>
inline int Array2D<T>::getRow() const
{
	return m_row;
}

template<typename T>
inline void Array2D<T>::setRow(int rows)
{
	if (rows < 0)
		throw Exception("Tried to set rows negative");
	m_array.SetLength(rows * m_col);
	m_row = rows;
}

template<typename T>
inline int Array2D<T>::getColumn() const
{
	return m_col;
}

template<typename T>
inline void Array2D<T>::setColumn(int columns)
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
	m_array.~Array1D();
	m_array = newArray;
	m_col = columns;
}

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
	return m_array[(m_col*row) + column];
}

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
	return m_array[(m_col*row) + column];
}

#endif