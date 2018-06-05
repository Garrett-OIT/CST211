//Author: Garrett Fechter
//Date Created: 5/22/2018
//Date Modified: 
//Purpose: test file for AVL trees
#include <iostream>
using std::cout;
using std::cin;
#include <string>
using std::string;
#include "TreeNode.h"
#include "AVL.h"

#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a function pointer type
								   // Test function declaration

//This test suite isnt very thorough, and i checked most things by hand
//some more test-only private functions could verify the integrity of the avl tree better
bool t_insert();
bool t_del();
bool t_big();

FunctionPointer test_functions[] = { t_insert, t_big, t_del };


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
			cout << "***** failed test number " << testNum << " *****\n";
		}
		++testNum;
	}
	cout << "\nPress Enter to Exit";
	cin.get();
}

void Display_and_Sum(const int & data) 
{
	static int sum = 0;
	cout << data << "\n";
	sum += data;
	cout << "SUM: " << sum << "\n";
}

void Display(const int & data) 
{
	cout << data << " ";
}

void Display_and_Sum1(const int & data) 
{
	static int sum = 0;
	cout << data << "\n";
	sum += data;
	cout << "SUM: " << sum << "\n";
}

bool t_insert() 
{
	bool pass = true;
	AVL<int> ints;
	for (int i = 0; i < 100; i++)
	{
		ints.Insert(i);
	}
	ints.InOrder(Display_and_Sum);
	int height = ints.Height();
	return pass;
}

bool t_del() 
{
	bool pass = true;
	AVL<int> ints;
	for (int i = 0; i < 20; i++)
	{
		ints.Insert(i);
	}
	for (int i = 10; i < 20; i++) 
	{
		ints.Delete(i);
	}
	ints.Delete(4);
	ints.Delete(2);
	ints.Delete(0);
	ints.Delete(1);
	ints.InOrder(Display_and_Sum1);
	ints.Purge();
	ints.Insert(0);
	ints.Insert(1);
	ints.Insert(2);
	ints.Insert(3);
	ints.Insert(4);
	ints.Insert(5);
	ints.Delete(0);
	ints.Delete(4);
	ints.Delete(5);
	return pass;
}

bool t_big() 
{
	bool pass = true;
	AVL<int> ints;
	for (int i = 0; i < 100; i += 10) 
	{
		for (int j = i; j > i - 5; j--)
			ints.Insert(j);
	}
	AVL<int> ints2(ints);
	AVL<int> ints3;
	if (ints3.Height() != 0)
		pass = false;
	ints3 = ints2;
	ints.InOrder(Display);
	cout << "\n";
	ints2.InOrder(Display);
	cout << "\n";

	ints.Preorder(Display);
	cout << "\n";
	ints2.Preorder(Display);
	cout << "\n";

	ints.Postorder(Display);
	cout << "\n";
	ints2.Postorder(Display);
	cout << "\n";

	ints.BreadthFirst(Display);
	cout << "\n";
	ints2.BreadthFirst(Display);
	cout << "\n";
	if (0 == ints.Height() || ints.Height() != ints2.Height() || ints3.Height() != ints2.Height())
		pass = false;
	cout << "Height: " << ints.Height() << "\n";
	ints.Purge();
	if (ints.Height() != 0)
		pass = false;
	return pass;
}