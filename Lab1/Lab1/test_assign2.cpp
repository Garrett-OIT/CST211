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
bool test_a2dconstDeref();
bool test_a2dsetters();

FunctionPointer test_functions[] = { test_a2dc , test_a2dc2, test_a2dcc, test_a2dconstDeref, test_a2dsetters };

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
	if (emptyInt.GetColumn() != 0)
		pass = false;
	if (emptyInt.GetRow() != 0)
		pass = false;
	if (emptyStr.GetColumn() != 0)
		pass = false;
	if (emptyStr.GetRow() != 0)
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
	if (emptyInt.GetColumn() != 5)
		pass = false;
	if (emptyInt.GetRow() != 5)
		pass = false;
	if (emptyStr.GetColumn() != 2)
		pass = false;
	if (emptyStr.GetRow() != 10)
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
		moreStrings.Select(2, 2) != names3[2])
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

bool test_a2dconstDeref()
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
	const Array2D<int> constInts(ints);
	if (constInts[0][0] != 00 ||
		constInts[0][1] != 01 ||
		constInts[0][2] != 02 ||
		constInts[1][0] != 10 ||
		constInts[1][1] != 11 ||
		constInts[1][2] != 12 ||
		constInts[2][0] != 20 ||
		constInts[2][1] != 21 ||
		constInts[2][2] != 22)
		pass = false;

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
	const Array2D<string> constStrs(strings);
	if (constStrs[0][0] != names1[0] ||
		constStrs[0][1] != names1[1] ||
		constStrs[0][2] != names1[2] ||
		constStrs[1][0] != names2[0] ||
		constStrs[1][1] != names2[1] ||
		constStrs[1][2] != names2[2] ||
		constStrs[2][0] != names3[0] ||
		constStrs[2][1] != names3[1] ||
		constStrs.Select(2, 2) != names3[2])
		pass = false;
	return pass;
}

bool test_a2dsetters()
{
	bool pass = true;
	Array2D<int> ints(3, 3);
	ints[0][0] = 888;
	ints[0][1] = 01;
	ints[0][2] = 02;
	ints[1][0] = 10;
	ints[1][1] = 11;
	ints[1][2] = 12;
	ints[2][0] = 20;
	ints[2][1] = 21;
	ints[2][2] = 99999;

	ints.SetColumn(10);
	ints.SetRow(10);

	if (ints.GetColumn() != 10 || ints.GetRow() != 10)
		pass = false;
	if (ints.Select(0, 0) != 888)
		pass = false;
	if (ints.Select(9, 9) != 0)
		pass = false;
	if (ints[2][2] != 99999) //failing
		pass = false;
	if (ints.Select(2, 2) != 99999) //failing
		pass = false;
	try
	{
		ints.SetColumn(-2);
	}
	catch (Exception &e)
	{
		cout << "Expected error in setters: " << e << "\n";
	}
	try
	{
		ints.SetRow(-2);
	}
	catch (Exception &e)
	{
		cout << "Expected error in setters: " << e << "\n";
	}
	ints.SetColumn(1);
	if (ints.Select(0, 0) != 888)
		pass = false;
	int test = ints.Select(2, 0);
	if (ints.Select(2, 0) != 20)
		pass = false;

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

	strings.SetColumn(22);
	strings.SetRow(22);

	if (strings.GetColumn() != 22 || strings.GetRow() != 22)
		pass = false;
	if (strings.Select(0, 0) != names1[0] || strings.Select(21, 21) != string() || strings.Select(2, 2) != names3[2])
		pass = false;
	try
	{
		strings.SetColumn(-2);
	}
	catch (Exception &e)
	{
		cout << "Expected error in setters: " << e << "\n";
	}
	try
	{
		strings.SetRow(-2);
	}
	catch (Exception &e)
	{
		cout << "Expected error in setters: " << e << "\n";
	}
	strings.SetColumn(1);
	if (strings.Select(0, 0) != names1[0] || strings.Select(2, 0) != names3[0])
		pass = false;
	return pass;
}