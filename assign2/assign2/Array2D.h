#include "Array1D.h"

#ifndef ARRAY2D
#define ARRAY2D
	
class Row;

template<typename T>
class Array2D
{
	public:
		Array2D();
		Array2D(int row, int col);
		Array2D(const Array2D & copy);
		~Array2D();
		Array2D & operator=(const Array2D & rhs);
		Row<T> operator[](int index) const;
		int getRow() const;
		void setRow(int rows);
		int getColumn() const;
		void setColumn(int columns);
		T & Select(int row, int column) const;
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
{ }

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
inline Array2D & Array2D<T>::operator=(const Array2D & rhs)
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
inline Row<T> Array2D<T>::operator[](int index) const
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
	int shorter = (rows > m_row) ? m_row : rows;
	m_array.SetLength(shorter * m_col);
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
	int shorter = (columns > m_col) ? m_col: columns;
	Array1D<T> newArray(columns * m_row);
	for (int i = 0; i < m_row; i++) //for each row
	{
		for (int j = 0; j < shorter; j++) //for each column
		{
			newArray[(i * shorter) + j] = m_array[(i * shorter) + j];
		}
		for (int j = shorter; j < columns; j++) //empty spaces if longer
		{
			newArray[(i * shorter) + j] = T();
		}
	}
}

template<typename T>
inline T & Array2D<T>::Select(int row, int column) const
{
	if (row > m_row || col > m_col) 
	{
		throw Exception("Out of bounds");
	}
	return m_array[(m_col*row) + m_col];
}

#endif