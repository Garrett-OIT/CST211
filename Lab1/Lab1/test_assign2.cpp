//Author: Garrett Fechter
//Purpose: Test alchemy, grid, and tile 

#include "Alchemy.h"
typedef bool(*FunctionPointer)();  // Define a function pointer type

#define FOREGROUND_WHITE 0x0F
#define BACKGROUND_BLACK 0x00
#define BACKGROUND_GOLD 0x60

#include <windows.h>
#include <iostream>
#include <crtdbg.h>
#include <conio.h>
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;

bool testTile();
bool testGrid();
bool testGrid2_display_checkadj();
bool testGrid3_clearing();
bool play();

FunctionPointer test_functions[] = { play, testTile , testGrid, testGrid2_display_checkadj, testGrid3_clearing};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	bool tests_passed = true;

	// Run the test functions
	for (FunctionPointer func : test_functions)
	{
		system("CLS");
		if (func())
		{
			cout << "passed\n";
		}
		else
		{
			tests_passed = false;
			cout << "***** failed *****\n";
		}
	}
	if (!tests_passed)
		cout << "---------  FAILED A TEST  ----------\n";
	else
		cout << "\nPASSED ALL TESTS\n";
	cout << "\nPress Enter to Exit";
	cin.clear(); 
#undef max
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin.get();
	return 0;
}

bool testTile() 
{
	bool pass = true;
	Tile blank_tile;
	if (blank_tile.GetColor() != 0x80)
		pass = false;
	if (blank_tile.GetShape() != ' ')
		pass = false;
	Tile blank_copy(blank_tile);
	if (blank_copy.GetColor() != 0x80)
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

	HANDLE hStdout = 0;
	COORD cursor;
	cursor.X = 0;
	cursor.Y = 0;

	Tile tile;
	tile.SetShape('q');
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 256; i++) 
	{
		if (i != 0 && i % 16 == 0) 
		{
			cursor.X = 0;
			cursor.Y++;
		}
		SetConsoleCursorPosition(hStdout, cursor);
		tile.SetColor(i);
		tile.Display();
		cursor.X++;
	}
	SetConsoleTextAttribute(hStdout, FOREGROUND_WHITE | BACKGROUND_BLACK);

	cout << "\n";
	return pass;
}

bool testGrid() 
{
	bool pass = true;
	Grid empty;
	if (empty.GetGrid().GetColumn() != 0 ||
		empty.GetGrid().GetRow() != 0 ||
		empty.GetLevel() != 0)
		pass = false;
	Grid empty2(empty);
	if (empty2.GetGrid().GetColumn() != 0 ||
		empty2.GetGrid().GetRow() != 0 ||
		empty2.GetLevel() != 0)
		pass = false;
	Grid empty3(0, 0);
	if (empty3.GetGrid().GetColumn() != 0 ||
		empty3.GetGrid().GetRow() != 0 ||
		empty3.GetLevel() != 0)
		pass = false;
	Grid empty4(0, 0, 0);
	if (empty4.GetGrid().GetColumn() != 0 ||
		empty4.GetGrid().GetRow() != 0 ||
		empty4.GetLevel() != 0)
		pass = false;
	Grid oneXone(1, 1);
	if (oneXone.GetGrid().GetColumn() != 1 ||
		oneXone.GetGrid().GetRow() != 1 ||
		oneXone.GetLevel() != 0)
		pass = false;
	Grid oneXone2(1, 1, 1);
	if (oneXone2.GetGrid().GetColumn() != 1 ||
		oneXone2.GetGrid().GetRow() != 1 ||
		oneXone2.GetLevel() != 1)
		pass = false;
	empty = oneXone2;
	if (empty.GetGrid().GetColumn() != 1 ||
		empty.GetGrid().GetRow() != 1 ||
		empty.GetLevel() != 1)
		pass = false;
	Grid all(16, 16, 0);
	Tile each;
	each.SetShape('&');
	for (int i = 0; i < 256; i++) 
	{
		each.SetColor(i);
		all.InsertTile(i / 16, i % 16, each);
	}
	for (int i = 0; i < 16; i++) 
	{
		for (int j = 0; j < 16; j++) 
		{
			if (all.GetGrid().Select(i, j).GetColor() != ((i * 16) + j) &&
				all.GetGrid().Select(i, j).GetShape() != '&')
				pass = false;
		}
	}
	all.Display();

	return pass;
}

bool testGrid2_display_checkadj() 
{
	bool pass = false;
	Grid random(16, 16, 0);
	Tile each;
	each.SetShape('X');
	for (int i = 0; i < 256; i++) 
	{
		each = random.GenerateTile();
		random.InsertTile(i / 16, i % 16, each);
	}
	random.Display();
	Grid ten(10, 10, 0);
	ten.Display();
	Tile center(FOREGROUND_WHITE | BACKGROUND_GOLD, '#');
	ten.InsertTile(5, 5, center);
	Tile temp;
	int sides = 0;
	for (int loop = 0; loop < 1000; loop++)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				temp = ten.GenerateTile();
				try
				{
					if (ten.CheckAdjacent(i, j, temp))
					{
						sides += ten.InsertTile(i, j, temp);
						ten.Display();
						try {
							ten.ClearRow(i);
						}
						catch (Exception) { }
						try {
							ten.ClearCol(j);
						} 
						catch (Exception) { }
						if (ten.CheckBoardComplete()) 
						{
							pass = true;//its possible this doesn't happen but should
							loop += 1000;
						}
					}
				}
				catch (Exception & e)
				{ }
			}
		}
	}
	Grid ten_copy;
	ten_copy.SetGrid(ten.GetGrid());
	ten_copy.Display();

	return pass;
}

bool testGrid3_clearing() 
{
	bool pass = true;
	Grid goldCheck(10, 10, 0);
	for (int row = 0; row < 10; row++) 
	{
		Tile blueA(0x1, 'A');
		goldCheck.InsertTile(row, 0, blueA);
		goldCheck.InsertTile(row, 4, blueA);
	}
	for (int col = 0; col < goldCheck.GetGrid().GetColumn(); col++) {
		goldCheck.Display();
		try
		{
			goldCheck.ClearCol(col);
		}
		catch (Exception)
		{ }
		goldCheck.Display();
	}
	return pass;
}

bool play()
{
	bool pass = true;
	Alchemy game;
	if (game.Start(0))
		game.Start(1);
	return pass;
}
