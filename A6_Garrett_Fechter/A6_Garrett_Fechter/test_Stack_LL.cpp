#include <iostream>
using std::cout;
using std::cin;
#include <string>
using std::string;
#include "Stack_LL.h"

#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a function pointer type
								   // Test function declaration
bool t_Stack_LL_canon();
bool t_Stack_LL_length();

FunctionPointer test_functions[] = { t_Stack_LL_canon , t_Stack_LL_length};


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

bool t_Stack_LL_canon()
{
	bool pass = true;
	Stack_LL<int> emptyi;
	if (pass) {
		try {
			emptyi.Pop();
			pass = false;
		}
		catch (Exception e) {
			pass = true; //tried to pop on empty
		}
	}
	Stack_LL<string> emptys;
	if (pass) {
		try {
			pass = false;
			emptys.Pop();
		}
		catch (Exception e) {
			pass = true; //tried to pop on empty
		}
	}
	if (emptyi.Size() != 0 || emptys.Size() != 0  || !emptyi.isEmpty() || !emptys.isEmpty())
		pass = false;
	Stack_LL<int> longi;
	Stack_LL<string> longs;
	if (longi.Size() != 0 || longs.Size() != 0 || !longi.isEmpty() || !longs.isEmpty())
		pass = false;
	if (pass) {
		try {
			pass = false;
			longi.Pop();
		}
		catch (Exception e) {
			pass = true; //tried to pop on empty
		}
	}
	if (pass) {
		try {
			pass = false;
			longs.Pop();
		}
		catch (Exception e) {
			pass = true; //tried to pop on empty
		}
	}
	Stack_LL<int> longi_copy(longi);
	Stack_LL<string> longs_copy(longs);
	if (pass) {
		try {
			pass = false;
			longs_copy.Pop();
		}
		catch (Exception e) {
			pass = true; //tried to pop on empty
		}
	}
	if (pass) {
		try {
			pass = false;
			longi_copy.Pop();
		}
		catch (Exception e) {
			pass = true; //tried to pop on empty
		}
	}
	if (longi_copy.Size() != 0 || longs_copy.Size() != 0|| !longi_copy.isEmpty() || !longs_copy.isEmpty())
		pass = false;
	for (int i = 0; i < 100; i++) 
		longi.Push(i);
	for (int i = 100; i < 200; i++) 
		longi_copy.Push(i);
	Stack_LL<int> longi_data_copy(longi);
	if (longi.isEmpty() || !longs.isEmpty())
		pass = false;
	if (longi_copy.isEmpty() || !longs_copy.isEmpty())
		pass = false;
	if (longi_data_copy.isEmpty())
		pass = false;
	for (int i = 99; i >= 0; i--) 
	{
		if (longi.Peek() != i)
			pass = false;
		if (longi.Pop() != i)
			pass = false;
	}
	for (int i = 99; i >= 0; i--) 
	{
		if (longi_data_copy.Peek() != i)
			pass = false;
		if (longi_data_copy.Pop() != i)
			pass = false;
	}
	longi_data_copy = longi_copy;
	for (int i = 199; i >= 100; i--) 
	{
		if (longi_copy.Peek() != i)
			pass = false;
		if (longi_copy.Pop() != i)
			pass = false;
	}
	for (int i = 199; i >= 100; i--) 
	{
		if (longi_data_copy.Peek() != i)
			pass = false;
		if (longi_data_copy.Pop() != i)
			pass = false;
	}
	if (emptyi.Size() != 0 || emptys.Size() != 0 || !emptyi.isEmpty() || !emptys.isEmpty())
		pass = false;
	if (longi_copy.Size() != 0 || longs_copy.Size() != 0|| !longi_copy.isEmpty() || !longs_copy.isEmpty())
		pass = false;
	if (longi.Size() != 0 || longs.Size() != 0 || !longi.isEmpty() || !longs.isEmpty())
		pass = false;
	return pass;
}

bool t_Stack_LL_length() 
{
	bool pass = true;
	Stack_LL<int> mystack;
	if (!mystack.isEmpty())
		pass = false;
	for (int i = 0; i < 100; i++) 
	{
		mystack.Push(i);
	}
	for (int i = 100; i < 200; i++) 
	{
		mystack.Push(i);
	}
	for (int i = 199; i >= 0; i--) 
	{
		if (i != mystack.Peek())
			pass = false;
		if (i != mystack.Pop())
			pass = false;
	}
	if (!mystack.isEmpty())
		pass = false;
	for (int i = 0; i < 200; i++)
		mystack.Push(i);
	for (int i = 199; i >= 0; i--) 
	{
		if (i != mystack.Peek())
			pass = false;
		if (i != mystack.Pop())
			pass = false;
	}
	if (!mystack.isEmpty())
		pass = false;
	return pass;
}
