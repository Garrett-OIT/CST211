//Author: Garrett Fechter
#include <iostream>
using std::cout;
using std::cin;
#include <string>
using std::string;
#include "CircularQueue.h"

#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a function pointer type
								   // Test function declaration
bool t_CQ_empty();
bool t_CQ_data();

FunctionPointer test_functions[] = { t_CQ_empty , t_CQ_data};


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

bool t_CQ_empty() 
{
	bool pass = true;
	CircularQueue<int> empty;
	if (!empty.isEmpty())
		pass = false;
	if (empty.isFull())
		pass = false;
	if (empty.Size() != 0)
		pass = false;
	CircularQueue<int> empty2(empty);
	if (!empty2.isEmpty())
		pass = false;
	if (empty2.isFull())
		pass = false;
	if (empty2.Size() != 0)
		pass = false;
	CircularQueue<int> empty3(10);
	empty3 = empty;
	if (!empty3.isEmpty())
		pass = false;
	if (empty3.isFull())
		pass = false;
	if (empty3.Size() != 0)
		pass = false;
	return pass;
}


bool t_CQ_data()  
{
	bool pass = true;
	CircularQueue<int> ints(100);
	for (int i = 0; i < 100; i++) 
	{
		ints.Enqueue(i);
	}
	CircularQueue<int> ints_c(ints);
	if (ints_c.Size() != 100)
		pass = false;
	if (ints.Size() != 100)
		pass = false;
	if (!ints_c.isFull())
		pass = false;
	if (!ints.isFull())
		pass = false;
	for (int i = 0; i < 100; i++) 
	{
		if (ints.Size() != (100 - i))
			pass = false;
		if (ints_c.Size() != (100 - i))
			pass = false;
		if (ints.Front() != i)
			pass = false;
		if (ints.Dequeue() != i)
			pass = false;
		if (ints_c.Front() != i)
			pass = false;
		if (ints_c.Dequeue() != i)
			pass = false;
	}
	for (int i = 0; i < 50; i++) 
	{
		ints.Enqueue(i);
		ints_c.Enqueue(i);
	}
	for (int i = 0; i < 25; i++) 
	{
		if (ints.Size() != (50 - i))
			pass = false;
		if (ints_c.Size() != (50 - i))
			pass = false;
		if (ints.Front() != i)
			pass = false;
		if (ints.Dequeue() != i)
			pass = false;
		if (ints_c.Front() != i)
			pass = false;
		if (ints_c.Dequeue() != i)
			pass = false;
	}
	for (int i = 50; i < 125; i++) 
	{
		ints.Enqueue(i);
		ints_c.Enqueue(i);
	}
	if (ints_c.Size() != 100)
		pass = false;
	if (ints.Size() != 100)
		pass = false;
	if (!ints_c.isFull())
		pass = false;
	if (!ints.isFull())
		pass = false;
	for (int i = 25; i < 125; i++) 
	{
		if (ints.Size() != (125 - i))
			pass = false;
		if (ints_c.Size() != (125 - i))
			pass = false;
		if (ints.Front() != i)
			pass = false;
		if (ints.Dequeue() != i)
			pass = false;
		if (ints_c.Front() != i)
			pass = false;
		if (ints_c.Dequeue() != i)
			pass = false;
	}
	if (ints_c.isFull())
		pass = false;
	if (ints.isFull())
		pass = false;
	if (!ints_c.isEmpty())
		pass = false;
	if (!ints.isEmpty())
		pass = false;
	return pass;
}
