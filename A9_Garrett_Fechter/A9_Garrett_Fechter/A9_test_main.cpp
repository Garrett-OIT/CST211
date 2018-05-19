//Author: Garrett Fechter
#include <iostream>
using std::cout;
using std::cin;
#include <string>
using std::string;
#include "TreeNode.h"
#include "BST.h"

#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a function pointer type
								   // Test function declaration

bool t_insert();
bool t_del();

FunctionPointer test_functions[] = { t_insert, t_del };


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
	BST<int> ints;
	for (int i = 0; i < 100; i += 10) 
	{
		for (int j = i; j > i - 5; j--)
			ints.Insert(j);
	}
	ints.InOrder(Display_and_Sum);
	return pass;
}

bool t_del() 
{
	bool pass = true;
	BST<int> ints;
	for (int i = 0; i < 100; i += 10) 
	{
		for (int j = i; j > i - 5; j--)
			ints.Insert(j);
	}
	for (int i = 50; i < 100; i += 10) 
	{
		for (int j = i; j > i - 5; j--)
			ints.Delete(j);
	}
	ints.InOrder(Display_and_Sum1);
	return pass;
}
