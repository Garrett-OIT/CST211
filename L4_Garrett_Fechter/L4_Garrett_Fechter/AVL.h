#ifndef AVL_H
#define AVL_H

#include "TreeNode.h"
#include "Exception.h"
#include "Queue_LL.h"
#include <algorithm> //for min and max

using std::min;
using std::max;

template <typename T>
class AVL
{
public:
	AVL();
	AVL(const AVL & copy);//copy side to side top to bottom
	AVL & operator = (const AVL & rhs); //copy side to side top to bottom
	~AVL();
	void Insert(T ins);
	void Delete(T del);
	void Purge(); //destroy side to side bottom to top
	int Height();
	void InOrder(void(*visit) (const T & data));
	void Preorder(void(*visit) (const T & data));
	void Postorder(void(*visit) (const T & data));
	void BreadthFirst(void(*visit) (const T & data));
private:
	void RightBalance(TreeNode<T>*& root, bool & taller);
	void LeftBalance(TreeNode<T>*& root, bool & taller);
	void RR(TreeNode<T> *& root);
	void LL(TreeNode<T> *& root);
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
inline AVL<T>::AVL() : m_root(nullptr)
{ }

template<typename T>
inline AVL<T>::AVL(const AVL & copy) : m_root(nullptr)
{
	m_root = Copy(copy.m_root);
}

template<typename T>
inline AVL<T> & AVL<T>::operator=(const AVL & rhs)
{
	if (this != &rhs)
	{
		Purge();
		m_root = Copy(rhs.m_root);
	}
	return *this;
}

template<typename T>
inline AVL<T>::~AVL()
{
	Purge();
	m_root = nullptr;
}

template<typename T>
inline void AVL<T>::Insert(T ins)
{
	bool taller = false;
	Insert(m_root, ins, taller);
}

template<typename T>
inline void AVL<T>::Delete(T del)
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
inline void AVL<T>::Purge()
{
	if (m_root != nullptr)
		Purge(m_root);
	m_root = nullptr;
}

template<typename T>
inline TreeNode<T> * AVL<T>::Copy(TreeNode<T>* root)
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
inline int AVL<T>::Height(TreeNode<T>* node)
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
inline void AVL<T>::DeleteFromTree(TreeNode<T> * parent, T del)
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
inline int AVL<T>::Height()
{
	return Height(m_root);
}

template<typename T>
inline void AVL<T>::InOrder(void(*visit)(const T & data))
{
	if (m_root != nullptr)
		InOrder(visit, m_root);
}

template<typename T>
inline void AVL<T>::Preorder(void(*visit)(const T &data))
{
	if (m_root != nullptr)
		Preorder(visit, m_root);
}

template<typename T>
inline void AVL<T>::Postorder(void(*visit)(const T &data))
{
	if (m_root != nullptr)
		Postorder(visit, m_root);
}

template<typename T>
inline void AVL<T>::BreadthFirst(void(*visit)(const T &data))
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
inline void AVL<T>::Insert(TreeNode<T> * &root, T data, bool & taller)
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
				root->setBal(LLH);
				LeftBalance(root, taller);
				break;
			case EH:
				root->setBal(LH);
				break;
			case RH:
				root->setBal(EH);
				taller = false;
				break;
			default:
				throw Exception("Invalid balancing\n");
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
				root->setBal(RRH);
				RightBalance(root, taller);
				break;
			default:
				throw Exception("Invalid balancing\n");
			}
		}
	}
}

template<typename T>
inline void AVL<T>::RightBalance(TreeNode<T>*& root, bool & taller)
{
	//problem is in root's right subtree
	TreeNode<T> *child = root->getRight();
	//if height of right childs right subtree is > , RR
	if (child->getBal() == RH || child->getBal() == EH)
		RR(root);
	//if height of right childs left subtree is > , RL
	else //(child->getBal() == LH)
	{
		LL(child);
		RR(root);
	}
	taller = false;
}

template<typename T>
inline void AVL<T>::LeftBalance(TreeNode<T>*& root, bool & taller)
{
	//problem is in root's left subtree
	TreeNode<T> *child = root->getLeft();
	//if height of left childs left subtree is > , LL
	if (child->getBal() == LH || child->getBal() == EH) 
	{
		LL(root);
	}
	//if height of right childs right subtree is > , LR
	else //(child->getBal() == RH)
	{
		RR(child);
		LL(root);
	}
	taller = false;
}

template<typename T>
inline void AVL<T>::RR(TreeNode<T>*& root)
{
	TreeNode<T> * child = root->getRight();
	TreeNode<T> * T1 = root->getLeft();
	TreeNode<T> * T2 = child->getLeft();
	TreeNode<T> * T3 = child->getRight();
	T rootData = root->getData();
	root->setData(child->getData());
	child->setData(rootData);
	root->setLeft(child);
	root->setRight(T3);
	child->setLeft(T1);
	child->setRight(T2);
	BF oldChild = child->getBal();
	BF bfs[] = { LLH, LH, EH, RH, RRH };
	child->setBal(bfs[(static_cast<int>(root->getBal()) - 1 - max(static_cast<int>(oldChild), 0)) + 2]);
	root->setBal(bfs[(static_cast<int>(oldChild) - 1 + min(static_cast<int>(child->getBal()), 0)) + 2]);
}

template<typename T>
inline void AVL<T>::LL(TreeNode<T>*& root)
{
	TreeNode<T> * child = root->getLeft();
	TreeNode<T> * T1 = child->getLeft();
	TreeNode<T> * T2 = child->getRight();
	TreeNode<T> * T3 = root->getRight();
	T rootData = root->getData();
	root->setData(child->getData());
	child->setData(rootData);
	root->setLeft(T1);
	root->setRight(child);
	child->setLeft(T2);
	child->setRight(T3);
	BF oldChild = child->getBal();
	BF bfs[] = { LLH, LH, EH, RH, RRH };
	child->setBal(bfs[(static_cast<int>(root->getBal()) + 1 - min(static_cast<int>(oldChild), 0)) + 2]);
	root->setBal(bfs[(static_cast<int>(oldChild) + 1 + max(static_cast<int>(child->getBal()), 0)) + 2]);
}

template<typename T>
inline void AVL<T>::Purge(TreeNode<T>* root)
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
inline void AVL<T>::InOrder(void(*visit)(const T &data), TreeNode<T>* root)
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
inline void AVL<T>::Preorder(void(*visit)(const T &data), TreeNode<T>* root)
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
inline void AVL<T>::Postorder(void(*visit)(const T &data), TreeNode<T>* root)
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