/*******************************
Author: Garrett Fechter
Purpose: A test file for OneDimArray
Date Created: 4/2/2018
Modifications:

*****************************/
#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a function pointer type

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;

#include <crtdbg.h>
#include <conio.h>

#include "OneDimArray.h"
//#include "Exception.h"

using std::cout;
using std::cin;

bool test_default_ctor();
bool test_ctor2();

// Array of test functions
FunctionPointer test_functions[] = { test_default_ctor, test_ctor2 };

int main() 
{
	cout << "Running tests...\n";
	int testNum = 0; //the number of the test being run
	for (FunctionPointer func : test_functions)
	{
		if (!func())
		{
			cout << "Failed test #" << testNum << ".\n";
		}
		++testNum;
	}
	cout << "Tests complete! Press enter to exit.\n";
	cin.get();
}

bool test_default_ctor() 
{
	OneDimArray<int> empty; // a OneDimArray using default ctor
	bool pass = false; //holds pass/fail results
	if (empty.getStartIndex() == 0 && empty.getLength() == 0) 
	{
		pass = true; 
	}
	return pass;
}

bool test_ctor2()
{
	OneDimArray<int> empty(10, 0); // a OneDimArray using default ctor
	bool pass = false; //holds pass/fail results
	if (empty.getStartIndex() == 10 && empty.getLength() == 0)
	{
		pass = true;
	}
	return pass;
}