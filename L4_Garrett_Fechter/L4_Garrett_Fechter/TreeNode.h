#ifndef TREENODE_H
#define TREENODE_H

enum BF 
{
	LLH = -2, LH, EH, RH, RRH
};

template<typename T>
class TreeNode 
{
public:
	TreeNode();//default ctor
	TreeNode(const TreeNode & copy);
	TreeNode(T data, BF balance = EH, TreeNode<T> * left = nullptr, TreeNode<T> * right = nullptr);
	TreeNode & operator = (const TreeNode & rhs);
	TreeNode<T> *& getRight();
	void setRight(TreeNode<T> * right);
	TreeNode<T> *& getLeft();
	void setLeft(TreeNode<T> * left);
	T & getData();
	void setData(T data);
	BF getBal();
	void setBal(BF balance);
	~TreeNode();
private:
	T m_data;
	TreeNode<T> *m_left;
	TreeNode<T> *m_right;
	BF m_balance;
};

template<typename T>
inline TreeNode<T>::TreeNode() : m_data(T()), m_next(nullptr), m_prev(nullptr), m_balance(EH)
{ }

template<typename T>
inline TreeNode<T>::TreeNode(const TreeNode & copy) : m_data(copy.m_data), m_next(copy.m_next), m_prev(copy.m_prev), m_balance(copy.m_balance)
{ }

template<typename T>
inline TreeNode<T>::TreeNode(T data, BF balance, TreeNode<T> * left, TreeNode<T> * right) : m_data(data), m_left(left), m_right(right), m_balance(balance)
{ }

template<typename T>
inline TreeNode<T> & TreeNode<T>::operator=(const TreeNode & rhs)
{
	if (this != &rhs) 
	{
		m_data = rhs.m_data;
		m_next = rhs.m_next;
		m_prev = rhs.m_prev;
		m_balance = rhs.m_balance;
	}
	return *this;
}

template<typename T>
inline TreeNode<T>*& TreeNode<T>::getRight()
{
	return m_right;
}

template<typename T>
inline void TreeNode<T>::setRight(TreeNode<T>* right)
{
	m_right = right;
}

template<typename T>
inline TreeNode<T>*& TreeNode<T>::getLeft()
{
	return m_left;
}

template<typename T>
inline void TreeNode<T>::setLeft(TreeNode<T>* left)
{
	m_left = left;
}

template<typename T>
inline  T & TreeNode<T>::getData() 
{
	return m_data;
}

template<typename T>
inline void TreeNode<T>::setData(T data)
{
	m_data = data;
}

template<typename T>
inline BF TreeNode<T>::getBal()
{
	return m_balance;
}

template<typename T>
inline void TreeNode<T>::setBal(BF balance)
{
	m_balance = balance;
}

template<typename T>
inline TreeNode<T>::~TreeNode()
{
	m_data = T();
	m_right = nullptr;
	m_left = nullptr;
	m_balance = EH;
}

#endif