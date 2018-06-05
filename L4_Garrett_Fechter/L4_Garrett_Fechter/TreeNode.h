//Author: Garrett Fechter
//Date Created: 5/20/2018
//Date Modified: 5/22/2018 - changes to include balance factors
//Purpose: a node for use in avl trees

#ifndef TREENODE_H
#define TREENODE_H

//enum BF (short for balance factor)
//represents all possible states of a nodes balance (LLH and RRH 
//	are only temporary and always get rebalanced)
enum BF 
{
	LLH = -2, LH, EH, RH, RRH
};

/*
 Class: TreeNode
 Purpose: A node for use in an AVL tree
public:
	TreeNode();//default ctor
	TreeNode(const TreeNode & copy);
		copy ctor
	TreeNode(T data, BF balance = EH, TreeNode<T> * left = nullptr, TreeNode<T> * right = nullptr);
		convenient ctor
	TreeNode & operator = (const TreeNode & rhs);
		overloaded assignment operator
	TreeNode<T> *& getRight();
		getter for m_right
	void setRight(TreeNode<T> * right);
		setter for m_right
	TreeNode<T> *& getLeft();
		getter for m_left
	void setLeft(TreeNode<T> * left);
		setter for m_left
	T & getData();
		getter for data
	void setData(T data);
		setter for data
	BF getBal();
		getter for m_balance
	void setBal(BF balance);
		setter for m_balance
	~TreeNode();
		dtor
*/
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
	T m_data;//the data inside a node
	TreeNode<T> *m_left;//pointer to left node
	TreeNode<T> *m_right;//pointer to right node
	BF m_balance;//balance factor of node (used in AVL trees)
};

/*
 Function: TreeNode 
 Purpose: default ctor
 Entry: -
 Exit: nullptr right/left, default data, equal balance
*/
template<typename T>
inline TreeNode<T>::TreeNode() : m_data(T()), m_next(nullptr), m_prev(nullptr), m_balance(EH)
{ }

/*
 Function: TreeNode
 Purpose: copy ctor
 Entry: -
 Exit: -
*/
template<typename T>
inline TreeNode<T>::TreeNode(const TreeNode & copy) : m_data(copy.m_data), m_next(copy.m_next), m_prev(copy.m_prev), m_balance(copy.m_balance)
{ }

/*
 Function: TreeNode
 Purpose: convenient ctor
 Entry: -
 Exit: -
*/
template<typename T>
inline TreeNode<T>::TreeNode(T data, BF balance, TreeNode<T> * left, TreeNode<T> * right) : m_data(data), m_left(left), m_right(right), m_balance(balance)
{ }

/*
 Function: operator=
 Purpose: overloaded assignment operator
 Entry: -
 Exit: -
*/
template<typename T>
inline TreeNode<T> & TreeNode<T>::operator=(const TreeNode & rhs)
{
	if (this != &rhs) 
	{
		m_data = rhs.m_data;
		m_left = rhs.m_left;
		m_right = rhs.m_right;
		m_balance = rhs.m_balance;
	}
	return *this;
}

/*
 Function: getRight
 Purpose: getter for m_right
 Entry: -
 Exit: -
*/
template<typename T>
inline TreeNode<T>*& TreeNode<T>::getRight()
{
	return m_right;
}

/*
 Function: setRight
 Purpose: setter for m_right
 Entry: -
 Exit: changes m_right
*/
template<typename T>
inline void TreeNode<T>::setRight(TreeNode<T>* right)
{
	m_right = right;
}

/*
 Function: getLeft
 Purpose: gett for m_left
 Entry:
 Exit:
*/
template<typename T>
inline TreeNode<T>*& TreeNode<T>::getLeft()
{
	return m_left;
}

/*
 Function: setLeft
 Purpose: setter for m_left
 Entry: -
 Exit: chnages m_left
*/
template<typename T>
inline void TreeNode<T>::setLeft(TreeNode<T>* left)
{
	m_left = left;
}

/*
 Function: getData
 Purpose: getter for m_data
 Entry:
 Exit:
*/
template<typename T>
inline  T & TreeNode<T>::getData() 
{
	return m_data;
}

/*
 Function: setData
 Purpose: setter for m_datat
 Entry:
 Exit:
*/
template<typename T>
inline void TreeNode<T>::setData(T data)
{
	m_data = data;
}

/*
 Function: getBal
 Purpose: geter for m_balance
 Entry:
 Exit:
*/
template<typename T>
inline BF TreeNode<T>::getBal()
{
	return m_balance;
}

/*
 Function: setBal
 Purpose: setter for m_balance
 Entry:
 Exit: changes m_balances
*/
template<typename T>
inline void TreeNode<T>::setBal(BF balance)
{
	m_balance = balance;
}

/*
 Function: ~TreeNode
 Purpose: dtor
 Entry: -
 Exit: sets everything back to default
*/
template<typename T>
inline TreeNode<T>::~TreeNode()
{
	m_data = T();
	m_right = nullptr;
	m_left = nullptr;
	m_balance = EH;
}

#endif