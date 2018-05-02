#include <iostream>
using std::cout;
using std::cin;
#include <string>
using std::string;
#include "Node.h"
#include "LinkedList.h"

#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a function pointer type

// Test function declaration
bool Node_empty_test();
bool Node_not_empty_test();
bool LL_canon();
bool LL_2();
bool LL_extracterino();
bool LL_ins_before();
bool LL_ins_after();

FunctionPointer test_functions[] = { Node_empty_test , Node_not_empty_test , LL_canon , LL_2
									, LL_extracterino , LL_ins_before, LL_ins_after};


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
	if (!myLinked.isEmpty())
		pass = false;
	for (int i = 0; i < 100; i++) 
	{
		myLinked.Append(i);
	}
	myLinked.PrintForwards();
	myLinked.PrintBackwards();
	LL<int> myL_copy(myLinked);
	LL<int> myL_copy2;
	myL_copy2 = myLinked;
	myL_copy2.PrintForwards();
	myL_copy2.PrintBackwards();
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
	steppin = myL_copy2.getHead()->getNext();
	while (steppin != nullptr)
	{
		if (steppin->getData() != 1 + steppin->getPrev()->getData())
			pass = false;
		steppin = steppin->getNext();
	}
	if (myLinked.getHead()->getPrev() != nullptr || myL_copy.getHead()->getPrev() != nullptr || myL_copy2.getHead()->getPrev() != nullptr)
		pass = false;
	if (myLinked.getTail()->getNext() != nullptr || myL_copy.getTail()->getNext() != nullptr || myL_copy2.getTail()->getNext() != nullptr)
		pass = false;
	return pass;
}

bool LL_2() 
{
	bool pass = true;
	LL<string> myLinked;
	if (!myLinked.isEmpty())
		pass = false;
	myLinked.Append("sah dude\n");
	if (myLinked.First() != "sah dude\n")
		pass = false;
	if (myLinked.Last() != "sah dude\n")
		pass = false;
	myLinked.Append("wed burh");
	if (myLinked.First() != "sah dude\n")
		pass = false;
	if (myLinked.Last() != "wed burh")
		pass = false;
	myLinked.Prepend("numero 1");
	if (myLinked.First() != "numero 1")
		pass = false;
	if (myLinked.Last() != "wed burh")
		pass = false;
	myLinked.PrintForwards();
	myLinked.PrintBackwards();
	myLinked.Purge();
	if (myLinked.getHead() != nullptr || myLinked.getTail() != nullptr)
		pass = false;
	return pass;
}

bool LL_extracterino() 
{
	bool pass = true;
	LL<string> alpha;
	alpha.Prepend("c");
	alpha.Prepend("b");
	alpha.Append("d");
	alpha.Append("e");
	alpha.Append("f");
	alpha.Append("g");
	alpha.Append("h");
	alpha.Append("i");
	alpha.Prepend("a");
	alpha.Extract("b");
	if (alpha.getHead()->getNext()->getData() != "c")
		pass = false;
	alpha.Extract("i");
	if (alpha.Last() != "h")
		pass = false;
	alpha.Extract("a");
	if (alpha.First() != "c")
		pass = false;
	alpha.PrintForwards();
	alpha.PrintBackwards();
	alpha.Purge();
	if (alpha.getHead() != nullptr || alpha.getTail() != nullptr)
		pass = false;
	return pass;
}

bool LL_ins_before() 
{
	bool pass = true;
	LL<string> alpha;
	alpha.Prepend("b");
	alpha.Append("d");
	alpha.Append("f");
	alpha.Append("h");
	alpha.Append("j");
	alpha.InsertBefore("a", "b");
	alpha.InsertBefore("c", "d");
	alpha.InsertBefore("e", "f");
	alpha.InsertBefore("i", "j");
	alpha.InsertBefore("g", "h");
	//now I know my abc's
	if (alpha.getHead()->getPrev() != nullptr || alpha.getHead()->getNext()->getData() != "b")
		pass = false;
	if (alpha.getTail()->getNext() != nullptr || alpha.getTail()->getPrev()->getData() != "i")
		pass = false;
	if (alpha.First() != "a" || alpha.Last() != "j")
		pass = false;
	alpha.PrintForwards();
	alpha.PrintBackwards();
	alpha.Extract("a");
	alpha.Extract("b");
	alpha.Extract("c");
	alpha.Extract("d");
	alpha.Extract("e");
	alpha.Extract("f");
	alpha.Extract("g");
	alpha.Extract("h");
	alpha.Extract("i");
	alpha.InsertBefore("a", "j");
	alpha.InsertBefore("b", "j");
	alpha.InsertBefore("c", "j");
	alpha.InsertBefore("d", "j");
	alpha.InsertBefore("e", "j");
	alpha.InsertBefore("f", "j");
	alpha.InsertBefore("g", "j");
	alpha.InsertBefore("h", "j");
	alpha.InsertBefore("i", "j");
	alpha.PrintForwards();
	alpha.PrintBackwards();
	if (alpha.getHead()->getPrev() != nullptr || alpha.getHead()->getNext()->getData() != "b")
		pass = false;
	if (alpha.getTail()->getNext() != nullptr || alpha.getTail()->getPrev()->getData() != "i")
		pass = false;
	if (alpha.First() != "a" || alpha.Last() != "j")
		pass = false;
	alpha.Purge();
	if (alpha.getHead() != nullptr || alpha.getTail() != nullptr)
		pass = false;
	return pass;
}

bool LL_ins_after() 
{
	bool pass = true;
	LL<string> alpha;
	alpha.Append("a");
	alpha.InsertAfter("c", "a");
	alpha.InsertAfter("e", "c");
	alpha.InsertAfter("f", "e");
	alpha.InsertAfter("g", "f");
	alpha.InsertAfter("h", "g");
	alpha.InsertAfter("i", "h");
	alpha.InsertAfter("j", "i");
	alpha.InsertAfter("b", "a");
	alpha.InsertAfter("d", "c");
	if (alpha.getHead()->getPrev() != nullptr || alpha.getHead()->getNext()->getData() != "b")
		pass = false;
	if (alpha.getTail()->getNext() != nullptr || alpha.getTail()->getPrev()->getData() != "i")
		pass = false;
	if (alpha.First() != "a" || alpha.Last() != "j")
		pass = false;
	alpha.PrintForwards();
	alpha.PrintBackwards();
	if (alpha.isEmpty())
		pass = false;
	alpha.Purge();
	if (!alpha.isEmpty())
		pass = false;
	alpha.Purge();
	alpha.Purge();
	if (alpha.getHead() != nullptr || alpha.getTail() != nullptr)
		pass = false;
	return pass;
}
