#include "Row.h"
#include "Exception.h"

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
	T** m_array; 
	int m_row; //number of rows
	int m_col; //number of columns
};

template<typename T>
inline Array2D<T>::Array2D() : m_array(nullptr), m_row(0), m_col(0)
{ }

template<typename T>
inline Array2D<T>::Array2D(int row, int col) : m_array(nullptr), m_row(row), m_col(col)
{
	if (row < 0 || col < 0)
		throw Exception("Tried to set negative row or col");
	if (row != 0 && col != 0) 
	{
		//allocate
		m_array = new T*[row];
		for (int i = 0; i < row; i++) 
		{
			m_array[i] = new T[col];
		}
		//initialize
		for (int i = 0; i < row; i++) 
		{
			for (int j = 0; j < col; j++) 
			{
				m_array[i][j] = T();
			}
		}
	}
}

template<typename T>
inline Array2D<T>::Array2D(const Array2D & copy) : m_array(nullptr), m_row(copy.m_row), m_col(copy.m_col)
{ 
	if (m_row != 0 && m_col != 0)
	{
		//allocate
		m_array = new T*[m_row];
		for (int i = 0; i < m_row; i++)
		{
			m_array[i] = new T[m_col];
		}
		//copy memory
		for (int i = 0; i < m_row; i++)
		{
			for (int j = 0; j < m_col; j++)
			{
				m_array[i][j] = copy[i][j];
			}
		}
	}
}

template<typename T>
inline Array2D<T>::~Array2D()
{
	if (m_array != nullptr)
	{
		for (int i = 0; i < m_row; i++)
		{
			delete[] m_array[i];//ok to not check for nullptr, col will always exist
		}
		delete[] m_array;
	}
	m_array = nullptr;
	m_row = 0;
	m_col = 0;
}

template<typename T>
inline Array2D<T> & Array2D<T>::operator=(const Array2D<T> & rhs)
{
	if (this != *rhs) //check for self assignment
	{
		//delete lhs
		if (m_array != nullptr)
		{
			for (int i = 0; i < m_row; i++)
			{
				delete[] m_array[i];
			}
			delete[] m_array;
		}
		m_array = nullptr;
		m_row = rhs.m_row;
		m_col = rhs.m_col;
		if (row != 0 && col != 0)
		{
			//allocate
			m_array = new T*[row];
			for (int i = 0; i < row; i++)
			{
				m_array[i] = new T[col];
			}
			//copy memory
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					m_array[i][j] = rhs[i][j];
				}
			}
		}
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
	T** newArray = new T*[rows];
	for (int i = 0; i < rows; i++) 
	{
		newArray[i] = new T[m_col];
	}
	int shorterRows = (rows > m_row) ? m_row : rows;
	for (int i = 0; i < shorterRows; i++) //copy data
	{
		for (int j = 0; j < m_col; j++) 
		{
			newArray[i][j] = m_array[i][j];
		}
	}
	for (int i = shorterRows; i < rows; i++) 
	{
		for (int j = 0; j < m_col; j++)
		{
			newArray[i][j] = T(); //potentially initialize new data
		}
	}
	for (int i = 0; i < m_row; i++) 
	{
		delete[] m_array[i];
	}
	delete[] m_array;
	m_array = newArray;
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
	int shorterCol = (columns > m_col) ? m_col : columns;
	T** newArray = new T*[m_row];
	//initialize
	for (int i = 0; i < m_row; i++) 
	{
		newArray[i] = new T[columns];
	}
	//copy old data and potentially initialize new data
	for (int i  = 0; i < m_row; i++) 
	{
		for (int j = 0; j < shorterCol; j++) 
		{
			newArray[i][j] = m_array[i][j];
		}
		for (int j = shorterCol; j < columns; j++)
		{
			newArray[i][j] = T();
		}
	}
	//delete old data
	for (int i = 0; i < m_row; i++)
	{
		delete[] m_array[i];
	}
	delete[] m_array;	
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
	return m_array[row][column];
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
	return m_array[row][column];
}

#endif