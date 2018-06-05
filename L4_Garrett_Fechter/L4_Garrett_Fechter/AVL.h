//Author: Garrett Fechter
//Date Created: 5/22/2018
//Date Modified: 
//Purpose: AVL Tree definition

#ifndef AVL_H
#define AVL_H

#include "TreeNode.h"
#include "Exception.h"
#include "Queue_LL.h"
#include <algorithm> //for min and max

using std::min;
using std::max;

/*
 Class: AVL
 Purpose: AVL ADT
 Functions:
	AVL();
		default ctor. empty (nullptr)
	AVL(const AVL & copy);//copy side to side top to bottom
		copy ctor
	AVL & operator = (const AVL & rhs); //copy side to side top to bottom
		overload operator =
	~AVL();
		destructor
	void Insert(T ins);
		insert a node with data ins
	void Delete(T del);
		delete a node 
	void Purge(); //destroy side to side bottom to top
		purge all of the nodes in the tree
	int Height();
		calculate the height of the avl tree (calls Height(m_root))
	void InOrder(void(*visit) (const T & data));
		an inorder traversal
	void Preorder(void(*visit) (const T & data));
		a preorder traversal
	void Postorder(void(*visit) (const T & data));
		a postorder traversal
	void BreadthFirst(void(*visit) (const T & data));
		a breadth first traversal
private:
	void RightBalance(TreeNode<T>*& root, bool & taller);
		balance for insert, on thr right
	void LeftBalance(TreeNode<T>*& root, bool & taller);
		balance for insert on the left
	TreeNode<T> *& RR(TreeNode<T> *& root);
		rotates to the left
	TreeNode<T> *& LL(TreeNode<T> *& root);
		rotates tot the right
	void Insert(TreeNode<T> *& root, T data, bool & taller);
		insert a node with data data at root
	void Purge(TreeNode<T> *root);
		destroy all nodes below root
	TreeNode<T> * Copy(TreeNode<T>* root);
		copy an avl tree matching root
	int getBalance(TreeNode<T> * root);
		get the left height minus right (used in delete)
	int Height(TreeNode<T> * node);
		get the height of a node
	TreeNode<T> * Delete(TreeNode<T> *& parent, T del);
		delete a node
	void InOrder(void(*visit) (const T & data), TreeNode<T> *root);
		inorder traversal stareting from root
	void Preorder(void(*visit) (const T & data), TreeNode<T> *root);
		preorder traversal stareting from root
	void Postorder(void(*visit) (const T & data), TreeNode<T> *root);
		posterder traversal stareting from root
*/
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
	TreeNode<T> *& RR(TreeNode<T> *& root);
	TreeNode<T> *& LL(TreeNode<T> *& root);
	void Insert(TreeNode<T> *& root, T data, bool & taller);
	void Purge(TreeNode<T> *root);
	TreeNode<T> * Copy(TreeNode<T>* root);
	int getBalance(TreeNode<T> * root);
	int Height(TreeNode<T> * node);
	TreeNode<T> * Delete(TreeNode<T> *& parent, T del);
	void InOrder(void(*visit) (const T & data), TreeNode<T> *root);
	void Preorder(void(*visit) (const T & data), TreeNode<T> *root);
	void Postorder(void(*visit) (const T & data), TreeNode<T> *root);

	TreeNode<T> *m_root;//the root of the tree
};

/*
 Function: AVL()
 Purpose: default ctor
 Entry: -
 Exit: m_root is nullptr
*/
template<typename T>
inline AVL<T>::AVL() : m_root(nullptr)
{ }

/*
 Function: AAVL(const AVL & copy)
 Purpose: copy ctor
 Entry: -
 Exit: creates new avl matching copy
*/
template<typename T>
inline AVL<T>::AVL(const AVL & copy) : m_root(nullptr)
{
	m_root = Copy(copy.m_root);
}

/*
 Function: operator -
 Purpose: overloaded assignment operator
 Entry: -
 Exit: -
*/
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

/*
 Function: ~AVL
 Purpose: dtor
 Entry: -
 Exit: all nodes are deleted, m_root becomes nullptr
*/
template<typename T>
inline AVL<T>::~AVL()
{
	Purge();
	m_root = nullptr;
}

/*
 Function: Insert
 Purpose: insert a node into the avl tree
 Entry: -
 Exit: puts a node in the tree, according to BST rules and then balancing
*/
template<typename T>
inline void AVL<T>::Insert(T ins)
{
	bool taller = false;
	Insert(m_root, ins, taller);
}

/*
 Function: Delete
 Purpose: delete a node matching data del. Throws exception if data isn't found
 Entry: -
 Exit: removes a node from the tree, rebalancing as necessary
*/
template<typename T>
inline void AVL<T>::Delete(T del)
{
	if (m_root == nullptr)
		throw Exception("Can't delete from empty tree\n");
	Delete(m_root, del);
}

/*
 Function: getBalance
 Purpose: get the balance of a node
 Entry: -
 Exit: -
*/
template<typename T>
inline int AVL<T>::getBalance(TreeNode<T> * root) 
{
	int bal = 0;
	if (root != nullptr) 
	{
		bal = Height(root->getLeft()) - Height(root->getRight());
	}
	return bal;
}

/*
 Function: Delete
 Purpose: delete a node matching data del. Throws exception if data isn't found
 Entry: -
 Exit: removes a node from the tree, rebalancing as necessary
*/
template<typename T>
inline TreeNode<T> * AVL<T>::Delete(TreeNode<T>*& root, T del)
{
	TreeNode<T> * ret = nullptr;
	if (root != nullptr)
	{
		if (del < root->getData())
			root->setLeft(Delete(root->getLeft(), del));
		else if (del > root->getData())
			root->setRight(Delete(root->getRight(), del));
		else
		{
			if ((root->getRight() == nullptr) || (root->getLeft() == nullptr))
			{
				TreeNode<T> *temp = (root->getLeft() != nullptr) ? root->getLeft() : root->getRight();
				if (temp == nullptr)
				{
					temp = root;
					root = nullptr;
				}
				else
					*root = *temp;
				delete temp;
			}
			else
			{
				TreeNode<T> * temp = root->getRight();
				while (temp->getLeft() != nullptr)
					temp = temp->getLeft();
				root->setData(temp->getData());
				root->getRight() = Delete(root->getRight(), temp->getData());
			}
		}

		if (root == nullptr)
			ret = nullptr;
		else
		{
			ret = root;
			BF bfs[] = { LLH, LH, EH, RH, RRH };
			int balance = getBalance(root);
			if (balance > 2 || balance < -2)
				throw Exception("Incorrect Balancing detected\n");
			root->setBal(bfs[(-balance) + 2]);
			if (balance > 1 && getBalance(root->getLeft()) >= 0) 
			{
				ret = LL(root);
			}
			else if (balance > 1 && getBalance(root->getLeft()) < 0)
			{
				root->setLeft(RR(root->getLeft()));
				ret = LL(root);
			}
			else if (balance < -1 && getBalance(root->getRight()) <= 0) 
			{
				ret = RR(root);
			}
			else if (balance < -1 && getBalance(root->getRight()) > 0)
			{
				root->setRight(LL(root->getRight()));
				ret = RR(root);
			}
		}
	}
	return ret;
}

/*
 Function: Purge
 Purpose: remove all data from tree
 Entry: -
 Exit: all nodes are deleted
*/
template<typename T>
inline void AVL<T>::Purge()
{
	if (m_root != nullptr)
		Purge(m_root);
	m_root = nullptr;
}

/*
 Function: Copy
 Purpose: copy this tree to match passed root * of tree
 Entry: takes existing root* to tree
 Exit: creates new tree recursively matching passed. m_root shouldnt have memory
	or a call to this will result in memory leaks
*/
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

/*
 Function: Height
 Purpose: Calculate Height of node (recursively)
 Entry: -
 Exit: -
*/
template<typename T>
inline int AVL<T>::Height(TreeNode<T>* node) {
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

/*
 Function: Height
 Purpose: get height of this tree, by calling Hieght(m_root)
 Entry: -
 Exit: -
*/
template<typename T>
inline int AVL<T>::Height()
{
	return Height(m_root);
}

/*
 Function: InOrder
 Purpose: an inorder travseral
 Entry: -
 Exit: -
*/
template<typename T>
inline void AVL<T>::InOrder(void(*visit)(const T & data))
{
	if (m_root != nullptr)
		InOrder(visit, m_root);
}

/*
 Function: Preorder
 Purpose: an inorder travseral
 Entry: -
 Exit: -
*/
template<typename T>
inline void AVL<T>::Preorder(void(*visit)(const T &data))
{
	if (m_root != nullptr)
		Preorder(visit, m_root);
}

/*
 Function: Postorder
 Purpose: a postorder traversal
 Entry:
 Exit:
*/
template<typename T>
inline void AVL<T>::Postorder(void(*visit)(const T &data))
{
	if (m_root != nullptr)
		Postorder(visit, m_root);
}

/*
 Function: BreadthFirst
 Purpose: a breadthfirst traversal
 Entry: -
 Exit: -
*/
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


/*
 Function: Insert
 Purpose: Insert a node into the tree according to BST rules then rebalance
 Entry: -
 Exit: puts a new node into tree & rebalances if necessary
*/
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

/*
 Function: RightBalance
 Purpose: Balance the right side of a tree
 Entry: -
 Exit: rebalances the right side of a tree to restore avl rules
*/
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

/*
 Function: LeftBalance
 Purpose: Balance the left side of a tree
 Entry: -
 Exit: rebalances the left side of a tree to restore avl rules
*/
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

/*
 Function: RR
 Purpose: perform a RR rotation (rotating nodes to the left)
 Entry: -
 Exit: moves nodes around
*/
template<typename T>
inline TreeNode<T> *& AVL<T>::RR(TreeNode<T>*& root)
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
	return root;
}

/*
 Function: LL
 Purpose: perform a LL rotation (rotating nodes to the right)
 Entry: -
 Exit: moves nodes around
*/
template<typename T>
inline TreeNode<T> *& AVL<T>::LL(TreeNode<T>*& root)
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
	return root;
}

/*
 Function: Purge
 Purpose: Get rid of all data in tree (recuesvily)
 Entry: non-empty root
 Exit: removes all data, sets root to nullptr
*/
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

/*
 Function: InOrder
 Purpose: inorder traversal
 Entry: -
 Exit: -
*/
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

/*
 Function: PreOrder
 Purpose: a preorder traversal
 Entry: -
 Exit: -
*/
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

/*
 Function: Postorder
 Purpose: a postorder traversal
 Entry: -
 Exit: -
*/
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