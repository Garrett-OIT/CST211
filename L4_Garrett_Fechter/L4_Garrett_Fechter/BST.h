#ifndef BST_H
#define BST_H

#include "TreeNode.h"
#include "Exception.h"
#include "Queue_LL.h"

template <typename T>
class BST
{
public:
	BST();
	BST(const BST & copy);//copy side to side top to bottom
	BST & operator = (const BST & rhs); //copy side to side top to bottom
	~BST();
	void Insert(T ins);
	void Delete(T del);
	void Purge(); //destroy side to side bottom to top
	int Height();
	void InOrder(void(*visit) (const T & data));
	void Preorder(void(*visit) (const T & data));
	void Postorder(void(*visit) (const T & data));
	void BreadthFirst(void(*visit) (const T & data));
private:
	void Insert(TreeNode<T> *& root, T data, bool & taller);
	void Purge(TreeNode<T> *root);
	TreeNode<T> * Copy(TreeNode<T>* root);
	int Height(TreeNode<T> * node);
	void DeleteFromTree(TreeNode<T> * parent, T del);
	void InOrder(void(*visit) (const T & data), TreeNode<T> *root);
	void Preorder(void(*visit) (const T & data), TreeNode<T> *root);
	void Postorder(void(*visit) (const T & data), TreeNode<T> *root);
	TreeNode<T> *m_root;
};

template<typename T>
inline BST<T>::BST() : m_root(nullptr)
{ }

template<typename T>
inline BST<T>::BST(const BST & copy) : m_root(nullptr)
{
	m_root = Copy(copy.m_root);
}

template<typename T>
inline BST<T> & BST<T>::operator=(const BST & rhs)
{
	if (this != &rhs)
	{
		Purge();
		m_root = Copy(rhs.m_root);
	}
	return *this;
}

template<typename T>
inline BST<T>::~BST()
{
	Purge();
	m_root = nullptr;
}

template<typename T>
inline void BST<T>::Insert(T ins)
{
	bool taller = false;
	Insert(m_root, ins, taller);
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
inline void BST<T>::Purge()
{
	if (m_root != nullptr)
		Purge(m_root);
	m_root = nullptr;
}

template<typename T>
inline TreeNode<T> * BST<T>::Copy(TreeNode<T>* root)
{
	TreeNode<T> * newTree = nullptr;
	if (root != nullptr)
	{
		newTree = new TreeNode<T>(root->getData());
		newTree->setLeft(Copy(root->getLeft()));
		newTree->setRight(Copy(root->getRight()));
	}
	return newTree;
}

template<typename T>
inline int BST<T>::Height(TreeNode<T>* node)
{
	int ret = 0;
	if (node != nullptr)
	{
		int right = Height(node->getRight());
		int left = Height(node->getLeft());
		if (left > right)
			ret = left + 1;
		else
			ret = right + 1;
	}
	return ret;
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
inline int BST<T>::Height()
{
	return Height(m_root);
}

template<typename T>
inline void BST<T>::InOrder(void(*visit)(const T & data))
{
	if (m_root != nullptr)
		InOrder(visit, m_root);
}

template<typename T>
inline void BST<T>::Preorder(void(*visit)(const T &data))
{
	if (m_root != nullptr)
		Preorder(visit, m_root);
}

template<typename T>
inline void BST<T>::Postorder(void(*visit)(const T &data))
{
	if (m_root != nullptr)
		Postorder(visit, m_root);
}

template<typename T>
inline void BST<T>::BreadthFirst(void(*visit)(const T &data))
{
	if (m_root != nullptr)
	{
		Queue_LL<TreeNode<T> *> nodes;
		nodes.Enqueue(m_root);
		while (!nodes.isEmpty())
		{
			TreeNode<T> * curr = nodes.Dequeue();
			visit(curr->getData());
			if (curr->getLeft() != nullptr)
				nodes.Enqueue(curr->getLeft());
			if (curr->getRight() != nullptr)
				nodes.Enqueue(curr->getRight());
		}
	}
}

template<typename T>
inline void BST<T>::Insert(TreeNode<T>*& root, T data, bool & taller)
{
	if (root == nullptr)
	{
		root = new TreeNode<T>(data);
		taller = true;
	}
	else if (data < root->getData()) 
	{
		//left
		Insert(root->getLeft(), data, taller);
		if (taller) 
		{
			switch (root->getBal()) 
			{
			case LH:
				LeftBalance(root, taller);
				break;
			case EH:
				root->setBal(LH);
				break;
			case RH:
				root->setBal(EH);
				taller = false;
				break;
			}
		}
	}
	else if (data >= root->getData()) 
	{
		//right
		Insert(root->getRight(), data, taller);
		if (taller) 
		{
			switch (root->getBal()) 
			{
			case LH:
				root->setBal(EH);
				taller = false;
				break;
			case EH:
				root->setBal(RH);
				break;
			case RH:
				RightBalance(root, taller);
				break;
			}
		}
	}
}

//Right balance: the problem is in the root's right child, call height to figure out which kind of rotation
	//taller = false after rotation
//Left balance

template<typename T>
inline void BST<T>::Purge(TreeNode<T>* root)
{
	if (root == nullptr)
		throw Exception("Tried to purge on empty\n");
	//destroy right to left bottom to top
	//similar to post order
	//traverse left
	if (root->getLeft() != nullptr)
		Purge(root->getLeft());
	//traverse right
	if (root->getRight() != nullptr)
		Purge(root->getRight());
	//visit 
	delete root;
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

template<typename T>
inline void BST<T>::Preorder(void(*visit)(const T &data), TreeNode<T>* root)
{
	//visit 
	visit(root->getData());
	//traverse left
	if (root->getLeft() != nullptr)
		Preorder(visit, root->getLeft());
	//traverse right
	if (root->getRight() != nullptr)
		Preorder(visit, root->getRight());
}

template<typename T>
inline void BST<T>::Postorder(void(*visit)(const T &data), TreeNode<T>* root)
{
	//traverse left
	if (root->getLeft() != nullptr)
		Postorder(visit, root->getLeft());
	//traverse right
	if (root->getRight() != nullptr)
		Postorder(visit, root->getRight());
	//visit 
	visit(root->getData());
}

#endif