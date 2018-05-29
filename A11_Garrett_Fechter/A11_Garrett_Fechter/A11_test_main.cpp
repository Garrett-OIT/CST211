//Author: Garrett Fechter
#include <iostream>
using std::cout;
using std::cin;
#include <string>
using std::string;
#include "Graph.h"

#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a function pointer type

bool graph();

FunctionPointer test_functions[] = { graph };


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

bool graph()
{
	bool pass = true;
	Graph<int, int> testGraph;
	return pass;
}