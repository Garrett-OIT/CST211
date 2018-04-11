#include "Tile.h"

typedef bool(*FunctionPointer)();  // Define a function pointer type

#include <crtdbg.h>
#include <conio.h>
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;

bool testTile();

FunctionPointer test_functions[] = { testTile };

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

bool testTile() 
{
	bool pass = true;
	Tile blank_tile;
	if (blank_tile.GetColor() != 0x0F)
		pass = false;
	if (blank_tile.GetShape() != ' ')
		pass = false;
	Tile blank_copy(blank_tile);
	if (blank_copy.GetColor() != 0x0F)
		pass = false;
	if (blank_copy.GetShape() != ' ')
		pass = false;
	Tile notBlank(0xEA, 'A');
	if (notBlank.GetColor() != 0xEA)
		pass = false;
	if (notBlank.GetShape() != 'A')
		pass = false;
	Tile copy_notBlank(notBlank);
	if (copy_notBlank.GetColor() != 0xEA)
		pass = false;
	if (copy_notBlank.GetShape() != 'A')
		pass = false;
	return pass;
}
