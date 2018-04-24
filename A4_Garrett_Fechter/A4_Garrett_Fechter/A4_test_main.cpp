#include <iostream>
using std::cout;
using std::cin;
#include <string>
using std::string;
#include "Node.h"
#include "LinkedList.h"

#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a function pointer type


// Strings to test
const char* NAMES[] = { "Kyle", "Brit", "Seth", "Alex", "Josh", "Kian",
"Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
"Oliver", "Tobey" };

const int NUM_NAMES = 15;

// Test function declaration
bool Node_empty_test();
bool Node_not_empty_test();
bool LL_canon();
// OneDimArray of test functions
FunctionPointer test_functions[] = { Node_empty_test , Node_not_empty_test , LL_canon };


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int testNum = 0;
	// Run the test functions
	for (FunctionPointer func : test_functions)
	{
		if (func())
		{
			cout << "passed test " << testNum << "\n";
		}
		else
		{
			cout << "***** failed test number "<< testNum << " *****\n";
		}
		++testNum;
	}

	cout << "\nPress Enter to Exit";
	cin.get();
}

bool Node_empty_test() 
{
	bool pass = true;
	Node<int> empty_i;
	Node<string> empty_s;
	string e_s;
	if (empty_s.getData() != e_s)
		pass = false;
	if (empty_i.getNext() != nullptr || empty_i.getPrev() != nullptr || empty_s.getNext() != nullptr || empty_s.getPrev() != nullptr)
		pass = false;
	Node<int> empty_i_2(empty_i);
	Node<string> empty_s_2(empty_s);
	if (empty_s_2.getData() != e_s)
		pass = false;
	if (empty_i_2.getNext() != nullptr || empty_i_2.getPrev() != nullptr || empty_s_2.getNext() != nullptr || empty_s_2.getPrev() != nullptr)
		pass = false;
	Node<int> * newNodeNext_i = new Node<int>;
	Node<int> * newNodePrev_i = new Node<int>;
	empty_i.setNext(newNodeNext_i);
	empty_i.setPrev(newNodePrev_i);
	Node<string> * newNodeNext_s = new Node<string>;
	Node<string> * newNodePrev_s = new Node<string>;
	empty_s.setNext(newNodeNext_s);
	empty_s.setPrev(newNodePrev_s);
	if (empty_i.getNext() != newNodeNext_i || empty_i.getPrev() != newNodePrev_i || empty_s.getNext() != newNodeNext_s || empty_s.getPrev() != newNodePrev_s)
		pass = false;
	empty_i_2 = empty_i;
	empty_s_2 = empty_s;
	if (empty_i_2.getNext() != newNodeNext_i || empty_i_2.getPrev() != newNodePrev_i || empty_s_2.getNext() != newNodeNext_s || empty_s_2.getPrev() != newNodePrev_s)
		pass = false;
	delete newNodeNext_i;
	delete newNodePrev_i;
	delete newNodeNext_s;
	delete newNodePrev_s;

	return pass;
}

bool Node_not_empty_test()
{
	bool pass = true;
	Node<int> nempty_i;
	nempty_i.setData(55);
	Node<string> nempty_s;
	string e_s = "This is an example string I'm using to test Node";
	nempty_s.setData(e_s);
	if (nempty_i.getData() != 55)
		pass = false;
	if (nempty_s.getData() != e_s)
		pass = false;
	if (nempty_i.getNext() != nullptr || nempty_i.getPrev() != nullptr || nempty_s.getNext() != nullptr || nempty_s.getPrev() != nullptr)
		pass = false;
	Node<int> nempty_i_2(nempty_i);
	Node<string> nempty_s_2(nempty_s);
	if (nempty_s_2.getData() != nempty_s.getData())
		pass = false;
	if (nempty_i_2.getData() != nempty_i.getData())
		pass = false;
	if (nempty_i_2.getNext() != nullptr || nempty_i_2.getPrev() != nullptr || nempty_s_2.getNext() != nullptr || nempty_s_2.getPrev() != nullptr)
		pass = false;
	Node<int> * newNodeNext_i = new Node<int>;
	newNodeNext_i->setData(-22);
	Node<int> * newNodePrev_i = new Node<int>;
	newNodePrev_i->setData(22);
	nempty_i.setNext(newNodeNext_i);
	nempty_i.setPrev(newNodePrev_i);
	Node<string> * newNodeNext_s = new Node<string>;
	newNodeNext_s->setData(e_s);
	Node<string> * newNodePrev_s = new Node<string>;
	newNodePrev_s->setData("asdfasdfasdfasdfasdfasdf");
	nempty_s.setNext(newNodeNext_s);
	nempty_s.setPrev(newNodePrev_s);
	if (nempty_i.getNext() != newNodeNext_i || nempty_i.getPrev() != newNodePrev_i || nempty_s.getNext() != newNodeNext_s || nempty_s.getPrev() != newNodePrev_s)
		pass = false;
	if (nempty_i.getNext()->getData() != newNodeNext_i->getData() || nempty_i.getPrev()->getData() != newNodePrev_i->getData() || nempty_s.getNext()->getData() != newNodeNext_s->getData() || nempty_s.getPrev()->getData() != newNodePrev_s->getData())
		pass = false;
	nempty_i_2 = nempty_i;
	nempty_s_2 = nempty_s;
	if (nempty_i_2.getNext() != newNodeNext_i || nempty_i_2.getPrev() != newNodePrev_i || nempty_s_2.getNext() != newNodeNext_s || nempty_s_2.getPrev() != newNodePrev_s)
		pass = false;
	if (nempty_i_2.getPrev()->getData() != newNodePrev_i->getData() || nempty_i_2.getPrev()->getData() != newNodePrev_i->getData() || nempty_s_2.getNext()->getData() != newNodeNext_s->getData() || nempty_s_2.getPrev()->getData() != newNodePrev_s->getData())
		pass = false;
	delete newNodeNext_i;
	delete newNodePrev_i;
	delete newNodeNext_s;
	delete newNodePrev_s;

	return pass;
}

bool LL_canon() 
{
	bool pass = true;
	LL<int> myLinked;
	for (int i = 0; i < 100; i++) 
	{
		myLinked.Append(i);
	}
	myLinked.PrintForwards();
	myLinked.PrintBackwards();
	LL<int> myL_copy(myLinked);
	myL_copy.PrintForwards();
	myL_copy.PrintBackwards();
	Node<int> *steppin = myLinked.getHead()->getNext();
	while (steppin != nullptr) 
	{
		if (steppin->getData() != 1 + steppin->getPrev()->getData())
			pass = false;
		steppin = steppin->getNext();
	}
	steppin = myL_copy.getHead()->getNext();
	while (steppin != nullptr)
	{
		if (steppin->getData() != 1 + steppin->getPrev()->getData())
			pass = false;
		steppin = steppin->getNext();
	}
	if (myLinked.getHead()->getPrev() != nullptr || myL_copy.getHead()->getPrev() != nullptr)
		pass = false;
	if (myLinked.getTail()->getNext() != nullptr || myL_copy.getTail()->getNext() != nullptr)
		pass = false;
	return pass;
}