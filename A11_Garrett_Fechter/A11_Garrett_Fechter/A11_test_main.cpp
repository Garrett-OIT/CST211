//Author: Garrett Fechter
#include <iostream>
using std::cout;
using std::cin;
#include <string>
using std::string;
#include "Graph.h"

#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a function pointer type

bool traversal();
bool graph();

FunctionPointer test_functions[] = { graph, traversal };


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

template <typename VData>
void Display(VData data) 
{
	cout << data << "\n";
}

bool graph()
{

	bool pass = true;
	Graph<int, int> testGraph;
	for (int i = 0; i < 10; i++) 
	{
		testGraph.InsertVertex(i);
	}
	for (int i = 0; i < 9; i++)
		testGraph.InsertArc(i, i + 1, 0, 0);
	testGraph.InsertArc(9, 0, 0, 0);
	testGraph.InsertArc(8, 3, 0, 0);
	testGraph.InsertArc(7, 3, 0, 0);
	testGraph.DeleteArc(6, 5, 0);
	testGraph.DeleteArc(5, 4, 0);
	cout << "Breadth:\n";
	testGraph.BreadthFirst(Display);
	cout << "Depth:\n";
	testGraph.DepthFirst(Display);
	cout << "\n";
	testGraph.DeleteVertex(5);
	testGraph.BreadthFirst(Display);
	return pass;
}

bool traversal() 
{
	bool pass = true;
	Graph<char, char> testGraph;
	testGraph.InsertVertex('X');
	testGraph.InsertVertex('G');
	testGraph.InsertVertex('H');
	testGraph.InsertVertex('P');
	testGraph.InsertVertex('E');
	testGraph.InsertVertex('Y');
	testGraph.InsertVertex('M');
	testGraph.InsertVertex('J');
	testGraph.InsertVertex('A');
	testGraph.InsertArc('A', 'X', ' ', 0);
	testGraph.InsertArc('X', 'G', ' ', 0);
	testGraph.InsertArc('X', 'H', ' ', 0);
	testGraph.InsertArc('H', 'P', ' ', 0);
	testGraph.InsertArc('H', 'E', ' ', 0);
	testGraph.InsertArc('E', 'M', ' ', 0);
	testGraph.InsertArc('E', 'Y', ' ', 0);
	testGraph.InsertArc('Y', 'M', ' ', 0);
	testGraph.InsertArc('M', 'J', ' ', 0);
	cout << "BREADTH:\n";
	testGraph.BreadthFirst(Display);
	cout << "DEPTH:\n";
	testGraph.DepthFirst(Display);
	return pass;
}
