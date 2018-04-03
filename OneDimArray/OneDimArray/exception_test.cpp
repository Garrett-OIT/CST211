/*******************************
Author: Garrett Fechter
Purpose: A test file for Exception
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

#include <conio.h>

#include "Exception.h"

using std::cout;
using std::cin;

bool test_default_ctor();
bool test_ctor2();
bool test_ctor2_nullptr();
bool test_insertion_operator();
bool test_insertion_operator_nullptr();
bool test_setMessage_nullptr();
bool test_setMessage();
bool test_assignment_operator();
bool test_assignment_operator_nullptr();
bool test_assignment_operator_self();
bool test_copy_ctor();

// Array of test functions
FunctionPointer test_functions[] = { test_default_ctor , test_ctor2 , test_ctor2_nullptr ,
									test_insertion_operator , test_setMessage_nullptr , test_setMessage ,
									test_assignment_operator , test_assignment_operator_nullptr , test_assignment_operator_self ,
									test_copy_ctor , test_insertion_operator_nullptr };

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
	cout << "Tests complete!\n";
}

bool test_default_ctor()
{
	Exception empty_msg;
	bool pass = false;
	if (empty_msg.getMessage() == nullptr)
		pass = true;
	return pass;
}

bool test_ctor2() 
{
	char* example = new char[5];
	strcpy(example, "test");
	bool pass = false;
	Exception test(example);
	delete[] example;
	if (strcmp("test", test.getMessage()) == 0)
		pass = true;
	return pass;
}

bool test_ctor2_nullptr()
{
	char* example = nullptr;
	bool pass = false;
	Exception test(example);
	delete[] example;
	if (nullptr == test.getMessage())
		pass = true;
	return pass;
}

bool test_assignment_operator_self()
{
	char* example = new char[5];
	strcpy(example, "test");
	bool pass = false;
	Exception test(example);
	delete[] example;
	test = test;
	if (strcmp("test", test.getMessage()) == 0)
		pass = true; //data intact
	return pass;
}


bool test_assignment_operator_nullptr()
{
	bool pass = false;
	Exception test;
	test = test;
	if (nullptr == test.getMessage())
		pass = true; //data intact
	return pass;
}

bool test_assignment_operator()
{
	char* example = new char[5];
	strcpy(example, "test");
	bool pass = false;
	Exception test(example);
	delete[] example;
	Exception test1;
	test1 = test;
	if (strcmp(test1.getMessage(), test.getMessage()) == 0)
	{
		Exception test_empty;
		test1 = test_empty;
		if (test1.getMessage() == nullptr)
		{
			if (strcmp(test.getMessage(), "test") == 0)
				pass = true; //data intact
		}
	}
	return pass;
}

bool test_setMessage() 
{
	char* example = new char[5];
	strcpy(example, "test");
	bool pass = false;
	Exception test(example);
	test = test;
	strcpy(example, "asdf");
	test.setMessage(example);
	delete[] example;
	if (strcmp("asdf", test.getMessage()) == 0)
		pass = true; //data accurate
	return pass;
}

bool test_setMessage_nullptr()
{
	char* example = new char[5];
	strcpy(example, "test");
	bool pass = false;
	Exception test(example);
	test = test;
	example = nullptr;
	test.setMessage(example);
	delete[] example;
	if (nullptr == test.getMessage())
		pass = true; //data accurate
	return pass;
}

bool test_insertion_operator()
{
	bool pass = true; //verify output manually
	char* example = new char[strlen("test_insertion_operator testing...") + 1];
	strcpy(example, "test_insertion_operator testing...");
	Exception test(example);
	cout << test << "\n";
	return pass;
}

bool test_insertion_operator_nullptr()
{
	bool pass = true; //verify output manually
	Exception test;
	cout << test << "\n";
	return pass;
}

bool test_copy_ctor()
{
	char* example = new char[5];
	strcpy(example, "test");
	bool pass = false;
	Exception test(example);
	delete[] example;
	Exception test1(test);
	if (strcmp(test1.getMessage(), test.getMessage()) == 0)
	{
		test1.setMessage(nullptr);
		Exception test_empty(test1);
		if (test_empty.getMessage() == nullptr)
		{
			if (strcmp(test.getMessage(), "test") == 0)
				pass = true; //data intact
		}
	}
	return pass;
}