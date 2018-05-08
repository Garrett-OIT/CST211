//Author: Garrett Fechter
#include <iostream>
#include "card.h"
#include <iostream>
using std::cout;
using std::cin;
#include <string>
#include "PlayCell.h"
#include "HomeCell.h"
#include "FreeCell.h"
using std::string;

#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a function pointer type
								   // Test function declaration
bool t_playcell();
bool t_homecell();
bool t_freecell();

FunctionPointer test_functions[] = { t_freecell , t_homecell , t_playcell };


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int testNum = 0;
	// Run the test functions
	for (FunctionPointer func : test_functions)
	{
		if (func())
		{
			//cout << "passed test " << testNum << "\n";
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

bool t_playcell()
{
	bool pass = true;
	CardRank ranks[13] = { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };//array of all possible ranks
	CardSuit suits[4] = { CLUBS, HEARTS, SPADES, DIAMONDS };//array of all suits
	Card temp;
	int rank_count = 0;
	int suit_count = 0;
	int numCards = 0;
	int stackNum = 0;
	PlayCell demo;
	demo.Init(0);
	demo.Display('P', 4, 0, 'P', 3, 3);
	return pass;
}

bool t_homecell()
{
	bool pass = true;
	HomeCell demo;
	Card temp1(ACE, CLUBS);
	demo.Place(temp1, 0);
	Card temp2(ACE, DIAMONDS);
	demo.Place(temp2, 1);
	Card temp3(ACE, SPADES);
	demo.Place(temp3, 2);
	Card temp4(ACE, HEARTS);
	demo.Place(temp4, 3);
	demo.Display();
	return pass;
}

bool t_freecell()
{
	bool pass = true;
	FreeCell demo;
	Card temp1(ACE, CLUBS);
	demo.Place(temp1, 0);
	Card temp2(ACE, DIAMONDS);
	demo.Place(temp2, 1);
	Card temp3(ACE, SPADES);
	demo.Place(temp3, 2);
	Card temp4(ACE, HEARTS);
	demo.Place(temp4, 3);
	demo.Display();
	return pass;
}
