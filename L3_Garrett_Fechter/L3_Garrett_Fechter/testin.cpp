//Author: Garrett Fechter
#include <iostream>
#include "card.h"
#include "deck.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
using std::cout;
using std::cin;
#include <string>
#include "PlayCell.h"
#include "HomeCell.h"
#include "FreeCell.h"
using std::string;

#define _CRTDBG_MAP_ALLOC

void ClearScreen();

typedef bool(*FunctionPointer)();  // Define a function pointer type
								   // Test function declaration
bool t_playcell();
bool t_homecell();
bool t_freecell();
bool t_arrow();

FunctionPointer test_functions[] = { t_freecell , t_homecell , t_playcell , t_arrow };


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
	Card temp;
	int rank_count = 0;
	int suit_count = 0;
	int numCards = 0;
	int stackNum = 0;
	PlayCell demo;
	demo.Init(0);
	for (int i = 0; i < 7; i++)
		demo.RemoveCard(0);
	chosenCard hovering = { 'P', 0, 0 };
	chosenCard selected = { 'P', 1, 1 };
	//for (int j = 0; j < 8; j++)
	//{
	//		selected.index1 = j;
	//	for (int i = 0; i < demo.GetLength(j); i++)
	//	{
	//		selected.index2 = i;
	//		demo.Display(hovering, selected);
	//	}
	//}
	Deck random;
	random.shuffle();
	while (random.getNumCards() > 2)
		demo.Place(random.draw(), 0);
	//for (int j = 0; j < 8; j++)
	//{
	//		selected.index1 = j;
	//	for (int i = 0; i < demo.GetLength(j); i++)
	//	{
	//		selected.index2 = i;
	//		demo.Display(hovering, selected);
	//	}
	//}
	return pass;
}

bool t_homecell()
{
	bool pass = true;
	HomeCell demo;
	Card temp1(ACE, CLUBS);
	//demo.Place(temp1, 0);
	Card temp2(ACE, DIAMONDS);
	Card temp3(ACE, SPADES);
	demo.Place(temp3, 2);
	demo.Place(temp3, 2);
	demo.Place(temp3, 2);
	Card temp4(ACE, HEARTS);
	Card temp5(TWO, HEARTS);
	demo.Place(temp4, 3);
	if (!demo.Place(temp5, 3))
		pass = false;
	if (demo.Place(temp5, 2))
		pass = false;
	CardRank ranks[13] = { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };//array of all possible ranks
	for (int i = 0; i < 13; i++)
	{
		temp2.setRank(ranks[i]);
		if (!demo.Place(temp2, 1))
			pass = false;
	}
	chosenCard hovering = { 'H', 0, 4 };
	chosenCard selected = { 'H', 1, 1 };
	demo.Display(hovering, selected);
	return pass;
}

bool t_freecell()
{
	bool pass = true;
	FreeCell demo;
	Card temp1(ACE, CLUBS);
	//demo.Place(temp1, 0);
	Card temp2(ACE, DIAMONDS);
	demo.Place(temp2, 1);
	Card temp3(ACE, SPADES);
	demo.Place(temp3, 2);
	Card temp4(ACE, HEARTS);
	if (!demo.Place(temp4, 3))
		pass = false;
	if (demo.Place(temp4, 3))
		pass = false;
	chosenCard selected = { 'F', 0, 4 };
	chosenCard hovering = { 'F', 2, 4 };
	demo.Display(hovering, selected);
	return pass;
}

bool t_arrow()
{
	string ranks[] = { //an enum for the different card ranks, starts at 0
		"ACE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING", "EMPTY_R"
	};

	string suits[] = { //enum for different card suits
		"CLUBS", "DIAMONDS", "HEARTS", "SPADES", "EMPTY_S"
	};
	PlayCell m_playcell;
	m_playcell.Init();
	HomeCell m_homecell;
	FreeCell m_freecell;
	chosenCard m_hovering = { 'F', 0, 0 };
	chosenCard m_selected = { ' ', 0, 0 };
	char read = 'q';
	while (read != 'e')
	{
		while (read != ' ' && read != 'e')
		{
			ClearScreen();
			m_homecell.Display(m_hovering, m_selected);
			m_freecell.Display(m_hovering, m_selected);
			m_playcell.Display(m_hovering, m_selected);
			read = _getch();
			if (read == -32 || read == 0 || read == 0xE0)
			{ //arrow key
				read = _getch();
				switch (read)
				{
				case 'H': //up
					if (m_hovering.location == 'P')
					{
						if (m_hovering.index2 < m_playcell.GetLength(m_hovering.index1) - 1)
							m_hovering.index2++;
						else
						{
							if (m_hovering.index1 < 4)
								m_hovering.location = 'F';
							else
							{
								m_hovering.location = 'H';
								m_hovering.index1 -= 4;
							}
						}
					}
					break;
				case 'P': //down 
				{
					switch (m_hovering.location)
					{
					case 'F':
						m_hovering.location = 'P';
						m_hovering.index2 = m_playcell.GetLength(m_hovering.index1) - 1;
						break;
					case 'H':
						m_hovering.location = 'P';
						m_hovering.index1 += 4;
						m_hovering.index2 = m_playcell.GetLength(m_hovering.index1) - 1;
						break;
					case 'P':
						if (m_hovering.index2 > 0)
							m_hovering.index2--;
						break;
					}
					break;
				}
				case 'M': //right
					switch (m_hovering.location)
					{
					case 'F':
						if (m_hovering.index1 < 3)
							m_hovering.index1++;
						else
						{
							m_hovering.index1 = 0;
							m_hovering.location = 'H';
						}
						break;
					case 'H':
						if (m_hovering.index1 < 3)
							m_hovering.index1++;
						break;
					case 'P':
						if (m_hovering.index1 < 7)
						{
							m_hovering.index1++;
							m_hovering.index2 = m_playcell.GetLength(m_hovering.index1) - 1 - (m_playcell.GetLength(m_hovering.index1 - 1) - 1 - m_hovering.index2);
							if (m_hovering.index2 > (m_playcell.GetLength(m_hovering.index1)))
								m_hovering.index2 = m_playcell.GetLength(m_hovering.index1);
							else if (m_hovering.index2 < 0)
								m_hovering.index2 = 0;
						}
						break;
					}
					break;
				case 'K': //left
					switch (m_hovering.location)
					{
					case 'F':
						if (m_hovering.index1 > 0)
							m_hovering.index1--;
						break;
					case 'H':
						if (m_hovering.index1 > 0)
							m_hovering.index1--;
						else
						{
							m_hovering.index1 = 3;
							m_hovering.location = 'F';
						}
						break;
					case 'P':
						if (m_hovering.index1 > 0)
						{
							m_hovering.index1--;
							m_hovering.index2 = m_playcell.GetLength(m_hovering.index1) - 1 - (m_playcell.GetLength(m_hovering.index1 + 1) - 1 - m_hovering.index2);
							if (m_hovering.index2 > (m_playcell.GetLength(m_hovering.index1)))
								m_hovering.index2 = m_playcell.GetLength(m_hovering.index1);
							else if (m_hovering.index2 < 0)
								m_hovering.index2 = 0;
						}
						break;
					}
					break;
				}
			}
		}
		if (read != 'e')
		{
			if (m_selected.location == ' ')
			{
				switch (m_hovering.location)
				{
				case 'F':
					m_selected = m_hovering;
					break;
				case 'P':
				{
					if (m_playcell.Moveable(m_freecell.NumFree(), m_hovering.index2, m_hovering.index1))
						m_selected = m_hovering;
					break;
				}
				}
			}
			else {
				//move selected to location
				switch (m_selected.location)
				{
				case 'F': //placing from a Free Cell
					cout << "Card selected: " << ranks[m_freecell.GetCard(m_selected.index1).getRank()];
					cout << " " << suits[m_freecell.GetCard(m_selected.index1).getSuit()];
					switch (m_hovering.location)
					{
					case 'H': //to a home cell
						if (m_homecell.Place(m_freecell.GetCard(m_selected.index1), m_hovering.index1))
							m_freecell.Remove(m_selected.index1);
						break;
					case 'F': //to another free cell
						if (m_freecell.Place(m_freecell.GetCard(m_selected.index1), m_hovering.index1))
							m_freecell.Remove(m_selected.index1);
						break;
					case 'P': //to a play cell
						if (m_hovering.index2 == 0)
						{
							if (m_playcell.Place(m_freecell.GetCard(m_selected.index1), m_hovering.index1))
								m_freecell.Remove(m_selected.index1);
						}
						break;
					}
					break;
				case 'P'://placing from a play cell
					cout << "Card selected: " << ranks[m_playcell.GetCard(m_selected.index2, m_selected.index1).getRank()];
					cout << " " << suits[m_playcell.GetCard(m_selected.index2, m_selected.index1).getSuit()];
					switch (m_hovering.location)
					{
					case 'H': //to a home cell
						if (m_selected.index2 == 0)
						{
							if (m_homecell.Place(m_playcell.GetCard(m_selected.index2, m_selected.index1), m_hovering.index1))
								m_playcell.RemoveCard(m_selected.index1);
						}
						break;
					case 'F': //to a free cell
						if (m_selected.index2 == 0)
						{
							if (m_freecell.Place(m_playcell.GetCard(m_selected.index2, m_selected.index1), m_hovering.index1))
								m_playcell.RemoveCard(m_selected.index1);
						}
						break;
					case 'P': //to another play cell
						if (m_hovering.index2 == 0)
						{
							int remove = 0;
							if (m_playcell.Place(m_playcell.GetCard(m_selected.index2, m_selected.index1), m_hovering.index1))
							{
								remove++;
								m_selected.index2--;
								while (m_selected.index2 >= 0)
								{
									m_playcell.Place(m_playcell.GetCard(m_selected.index2, m_selected.index1), m_hovering.index1);
									remove++;
									m_selected.index2--;
								}
								for (int i = 0; i < remove; i++)
									m_playcell.RemoveCard(m_selected.index1);
							}
						}
						break;
					}
					break;
				}
				m_selected.location = ' ';
			}
		}
	}
	return true;
}

