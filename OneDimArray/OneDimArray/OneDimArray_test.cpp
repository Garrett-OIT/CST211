/*******************************
Author: Garrett Fechter
Purpose: A test file for OneDimArray
Date Created: 4/2/2018
Modifications:

*****************************/
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

typedef bool(*FunctionPointer)();  // Define a function pointer type

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;

#include <crtdbg.h>
#include <conio.h>

#include "OneDimArray.h"

using std::cout;
using std::cin;

bool test_default_ctor();
bool test_ctor2();

// Array of test functions
FunctionPointer test_functions[] = { test_default_ctor, test_ctor2 };

int main() 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
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
	return 0;
}

bool test_default_ctor() 
{
	OneDimArray<int> empty; // a OneDimArray using default ctor
	bool pass = false; //holds pass/fail results
	if (empty.getStartIndex() == 0 && empty.getLength() == 0) 
	{
		try
		{
			empty[0];
		}
		catch (const Exception& e) 
		{
			cout << "Successfully threw error:\n\t" << e << "\n";
			pass = true;
		}
	}
	return pass;
}

bool test_ctor2()
{
	OneDimArray<int> empty(10, 0); // a OneDimArray using ctor2
	bool pass = false; //holds pass/fail results
	if (empty.getLength() == 10 && empty.getStartIndex() == 0)
	{
		pass = true;
	}
	return pass;
}

bool test_ctor2_1arg()
{
	OneDimArray<int> empty(0); // a OneDimArray using ctor2
	bool pass = false; 
	if (empty.getLength() == 0 && empty.getStartIndex() == 0)
	{
		pass = true;
	}
	return pass;
}

