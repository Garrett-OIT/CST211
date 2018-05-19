#ifndef BST_H
#define BST_H

#include "TreeNode.h"
#include "Exception.h"

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
	void DeleteFromTree(TreeNode<T> * parent, T del);
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
	if (m_root == nullptr)
		throw Exception("Can't delete from empty tree\n");
	TreeNode<T> *curr = m_root;
	TreeNode<T> *trail = m_root;
	bool found = false;
	while (curr != nullptr && !found) 
	{
		if (curr->getData() == del)
			found = true;
		else 
		{
			trail = curr;
			if (curr->getData() > del)
				curr = curr->getLeft();
			else
				curr = curr->getRight();
		}
	}
	if (curr == nullptr)
		throw Exception("Tried to delete non-existent node\n");
	if (found) 
	{
		if (m_root == curr)
			DeleteFromTree(m_root, del);
		else 
			DeleteFromTree(trail, del);
	}
}

template<typename T>
inline void BST<T>::DeleteFromTree(TreeNode<T> * parent, T del)
{
	TreeNode<T> *curr = parent;
	int kid = 0;
	if (parent == nullptr)
		throw Exception("Tried to DeleteFromTree on nullptr\n");
	if (parent->getData() == del) 
		curr = parent;//deleting root
	else if (parent->getRight() != nullptr && parent->getRight()->getData() == del) 
	{
		curr = parent->getRight();
		kid = 1;
	}
	else if (parent->getLeft() != nullptr && parent->getLeft()->getData() == del) 
	{
		curr = parent->getLeft();
		kid = -1;
	}

	TreeNode<T> *trail = nullptr;

	if (curr->getRight() == nullptr && curr->getLeft() == nullptr)  //case 1
	{
		if (kid == 1)
			parent->setRight(nullptr);
		else if (kid == -1)
			parent->setLeft(nullptr);
	}
	else if (curr->getLeft() == nullptr) //case 2
	{
		if (kid == 1)
			parent->setRight(curr->getRight());
		if (kid == -1)
			parent->setLeft(curr->getRight());
	}
	else if (curr->getRight() == nullptr) //case 3 
	{
		if (kid == 1)
			parent->setRight(curr->getLeft());
		if (kid == -1)
			parent->setLeft(curr->getLeft());
	}
	else //has 2 kids
	{
		TreeNode<T> *deleting = curr;
		trail = nullptr;
		curr = curr->getLeft();
		while (curr->getRight() != nullptr) 
		{
			trail = curr;
			curr = curr->getRight();
		}
		deleting->setData(curr->getData());
		if (trail == nullptr) 
		{
			deleting->setLeft(curr->getLeft());
		}
		else
			trail->setRight(curr->getLeft());
	}
	delete curr;
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