#include "Array2D.h"

typedef bool(*FunctionPointer)();  // Define a function pointer type

#include <crtdbg.h>
#include <conio.h>
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;

bool test_a2dc();
bool test_a2dc2();
bool test_a2dcc();

FunctionPointer test_functions[] = { test_a2dc , test_a2dc2, test_a2dcc };

string names1[] = { "Bob", "Joe", "Lorem" };
string names2[] = { "Ipsum", "Babbidty", "whoboo" };
string names3[] = { "a", "bayou doo", "this should be the last entry" };

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	bool tests_passed;

	// Run the test functions
	for (FunctionPointer func : test_functions)
	{
		if (func())
		{
			cout << "passed\n";
		}
		else
		{
			cout << "***** failed *****\n";
		}
	}

	cout << "\nPress Enter to Exit";
	cin.get();
	return 0;
}

bool test_a2dc()
{
	bool pass = true;
	Array2D<int> emptyInt;
	Array2D<string> emptyStr;
	if (emptyInt.getColumn() != 0)
		pass = false;
	if (emptyInt.getRow() != 0)
		pass = false;
	if (emptyStr.getColumn() != 0)
		pass = false;
	if (emptyStr.getRow() != 0)
		pass = false;
	try
	{
		int test = emptyInt[0][0];
	}
	catch (Exception &e)
	{
		cout << "Expected error from test0: " << e << "\n";
	}
	try
	{
		emptyStr[0][0];
	}
	catch (Exception &e)
	{
		cout << "Expected error from test0: " << e << "\n";
	}
	return pass;
}

bool test_a2dc2()
{
	bool pass = true;
	Array2D<int> emptyInt(5, 5);
	Array2D<string> emptyStr(10, 2);
	if (emptyInt.getColumn() != 5)
		pass = false;
	if (emptyInt.getRow() != 5)
		pass = false;
	if (emptyStr.getColumn() != 2)
		pass = false;
	if (emptyStr.getRow() != 10)
		pass = false;
	if (emptyInt[0][0] != 0)
		pass = false;
	if (emptyInt[4][4] != 0)
		pass = false;
	if (!emptyStr[0][0].empty())
		pass = false;
	if (!emptyStr[9][1].empty())
		pass = false;
	return pass;
}

bool test_a2dcc()
{
	bool pass = true;
	Array2D<int> ints(3, 3);
	ints[0][0] = 00;
	ints[0][1] = 01;
	ints[0][2] = 02;
	ints[1][0] = 10;
	ints[1][1] = 11;
	ints[1][2] = 12;
	ints[2][0] = 20;
	ints[2][1] = 21;
	ints[2][2] = 22;
	Array2D<int> moreInts(ints);
	ints.~Array2D();
	if (moreInts[0][0] != 00 ||
		moreInts[0][1] != 01 ||
		moreInts[0][2] != 02 ||
		moreInts[1][0] != 10 ||
		moreInts[1][1] != 11 ||
		moreInts[1][2] != 12 ||
		moreInts[2][0] != 20 ||
		moreInts[2][1] != 21 ||
		moreInts[2][2] != 22)
		pass = false;
	try
	{
		ints[0][0];
	}
	catch (Exception &e)
	{
		cout << "Expected error from test_a2dcc: " << e << "\n";
	}
	Array2D<string> strings(3, 3);
	strings[0][0] = names1[0];
	strings[0][1] = names1[1];
	strings[0][2] = names1[2];
	strings[1][0] = names2[0];
	strings[1][1] = names2[1];
	strings[1][2] = names2[2];
	strings[2][0] = names3[0];
	strings[2][1] = names3[1];
	strings[2][2] = names3[2];
	Array2D<string> moreStrings(strings);
	strings.~Array2D();
	if (moreStrings[0][0] != names1[0] ||
		moreStrings[0][1] != names1[1] ||
		moreStrings[0][2] != names1[2] ||
		moreStrings[1][0] != names2[0] ||
		moreStrings[1][1] != names2[1] ||
		moreStrings[1][2] != names2[2] ||
		moreStrings[2][0] != names3[0] ||
		moreStrings[2][1] != names3[1] ||
		moreStrings[2][2] != names3[2])
		pass = false;
	try
	{
		strings[0][0];
	}
	catch (Exception &e)
	{
		cout << "Expected error 2 from test_a2dcc: " << e << "\n";
	}
	return pass;
}