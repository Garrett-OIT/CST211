#ifndef BST_H
#define BST_H

#include "TreeNode.h"

template <typename T>
class BST
{
public:
	BST();
	BST(const BST & copy);
	//BST & operator = (const BST & rhs);
	~BST();
	void Insert(T ins);
	void Delete(T del);
	//void Purge();
	//int Height();
	void InOrder(void(*visit) (const T & data));
private:
	void InOrder(void(*visit) (const T & data), TreeNode<T> *root);
	TreeNode<T> *m_root;
};

template<typename T>
inline BST<T>::BST() : m_root(nullptr)
{ }

template<typename T>
inline BST<T>::BST(const BST & copy)
{
}

template<typename T>
inline BST<T>::~BST()
{
	//just in order with delete
}

template<typename T>
inline void BST<T>::Insert(T ins)
{
	TreeNode<T> *trail = m_root;
	TreeNode<T> *curr = m_root;
	while (nullptr != curr) 
	{
		if (ins >= curr->getData()) 
		{
			trail = curr;
			curr = curr->getRight();
		}
		else 
		{
			trail = curr;
			curr = curr->getLeft();
		}
	}
	if (trail == nullptr) 
	{
		//empty BST
		m_root = new TreeNode<T>(ins);
	}
	else
	{
		if (ins >= trail->getData()) //insert right
		{
			trail->setRight(new TreeNode<T>(ins));
		}
		else //insert left
		{
			trail->setLeft(new TreeNode<T>(ins));
		}
	}
}

template<typename T>
inline void BST<T>::Delete(T del)
{
	TreeNode<T> *curr = m_root;
	TreeNode<T> *trail = nullptr;
	while (curr != nullptr) 
	{
		if (curr.getData() == del)
		{
			//delete
		}
		else if (curr.getData() > del) 
		{
			trail = curr;
			curr = curr.getRight();
		}
		else if (curr.getData() < del) 
		{
			trail = curr;
			curr = curr.getLeft();
		}
	}
}

template<typename T>
inline void BST<T>::InOrder(void(*visit)(const T & data))
{
	if (m_root != nullptr)
		InOrder(visit, m_root);
}

template<typename T>
inline void BST<T>::InOrder(void(*visit)(const T &data), TreeNode<T>* root)
{
	//traverse left
	if (root->getLeft() != nullptr) 
		InOrder(visit, root->getLeft());
	//visit 
	visit(root->getData());
	//traverse right
	if (root->getRight() != nullptr)
		InOrder(visit, root->getRight());
}

#endif