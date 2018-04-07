#ifndef ROW
#define ROW

template<typename T>
class Array2D;

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

template<typename T>
inline Row<T>::Row(Array2D<T> & in_array, int row) : m_array2D(in_array), m_row(row)
{
	if (row < 0)
	{
		throw Exception("Rows specified can't be negative");
	}
	if (row > in_array.getRow())
	{
		throw Exception("Out of bounds");
	}
}

template<typename T>
inline Row<T>::Row(const Array2D<T> & in_array, int row) : m_array2D(in_array), m_row(row)
{
	if (row < 0)
	{
		throw Exception("Rows specified can't be negative");
	}
	if (row > in_array.getRow())
	{
		throw Exception("Out of bounds");
	}
}

template<typename T>
inline T & Row<T>::operator[](int column)
{
	if (column >= m_array2D.getColumn())
		throw Exception("Out of bounds");
	return const_cast <T &>(m_array2D.Select(m_row, column));
}

template<typename T>
inline const T & Row<T>::operator[](int column) const
{
	if (column >= m_array2D.getColumn())
		throw Exception("Out of bounds");
	return m_array2D.Select(m_row, column);
}

#endif
