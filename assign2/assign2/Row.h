#include "Exception.h"

#ifndef ROW
#define ROW

class Array2D;

template<typename T>
class Row 
{
	public:
		Row<T>(Array2D & in_array, int row);
		T & operator[](int column) const;
	private:
		Array2D & m_array2D; //the Array2D this row is part of
		int m_row; //the number row this is inside Array2D
};

template<typename T>
inline Row<T>::Row(Array2D & in_array, int row) : m_array2D<T>(in_array), m_row(row)
{ }

template<typename T>
inline T & Row<>::operator[](int column) const
{
	if (column >= m_array2D.GetColumn()) 
		throw Exception("Out of bounds")
	return m_array2D.Select(m_row, column);
}

#endif