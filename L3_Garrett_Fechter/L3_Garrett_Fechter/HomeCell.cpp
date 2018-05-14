//Garrett Fechter
//Purpose: implementation of homecell
//Created 2018
//Modified: 

#include "HomeCell.h"
#include <iostream>
#include <windows.h>

/****************
Purpose: defaulkt ctor. there are 4 homecells
Precondition: -
Postcondition: -
*****************/
HomeCell::HomeCell() : m_homecells(4)
{ 
	for (int i = 0; i < 4; i++)
	{
		m_homecells[i].SetSize(13);
	}
}

/****************
Purpose: copy ctor
Precondition: -
Postcondition: -
*****************/
HomeCell::HomeCell(const HomeCell & copy) : m_homecells(copy.m_homecells)
{ }

/****************
Purpose: overloaded assignment operator
Precondition: -
Postcondition: -
*****************/
HomeCell & HomeCell::operator=(const HomeCell & rhs)
{
	m_homecells = rhs.m_homecells;
	return *this;
}

/****************
Purpose: dtor. resets cards.
Precondition: -
Postcondition: -
*****************/
HomeCell::~HomeCell()
{
	for (int i = 0; i < 4; i++)
	{
		m_homecells[i].SetSize(0);
		m_homecells[i].SetSize(13);
	}
}
/****************
Purpose: check if game was won 
Precondition: -
Postcondition: -
*****************/
bool HomeCell::win()
{
	bool won = true;
	for (int i = 0; i < 4; i++)
	{
		if (m_homecells[i].Size() > 0)
		{
			if (m_homecells[i].Peek().getRank() != KING)
				won = false;
		}
		else
			won = false;
	}
	return won;
}

/****************
Purpose: place a card at location
Precondition: location must be valid
Postcondition: put card at location 
*****************/
bool HomeCell::Place(Card card, int location)
{
	bool placed = false;
	CardRank ranks[13] = { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };//array of all possible ranks
	CardSuit suits[4] = { CLUBS, HEARTS, SPADES, DIAMONDS };//array of all suits
	if (!card.isEmpty())
	{
		if (m_homecells[location].Size() == 0)
		{
			if (card.getRank() == ACE)
			{
				m_homecells[location].Push(card);
				placed = true;
			}
		}
		else if (m_homecells[location].Peek().getSuit() == card.getSuit() && m_homecells[location].Peek().getRank() == (card.getRank() - 1))
		{
			m_homecells[location].Push(card);
			placed = true;
		}
	}
	return placed;
}

/****************
Purpose: display all the homecell cards
Precondition: -
Postcondition: -
*****************/
void HomeCell::Display()
{
	HANDLE hStdout = 0;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, 0x0F);
	COORD cursor;
	cursor.X = 20;
	cursor.Y = 0;
	SetConsoleCursorPosition(hStdout, cursor);
	std::cout << " Home Cells:";
	cursor.X = 20;
	cursor.Y = 1;
	SetConsoleCursorPosition(hStdout, cursor);
	std::cout << " ";
	for (int i = 0; i < 4; i++) 
	{
		if (!m_homecells[i].isEmpty())
			m_homecells[i].Peek().Display();
	}
}

/****************
Purpose: display all the homecell cards with extra info about hovering/selected card (uses colors)
Precondition: indicies must be valid
Postcondition: -
*****************/
void HomeCell::Display(char hovering, int h_index1, int h_index2, char selected, int s_index1, int s_index2)
{
	HANDLE hStdout = 0;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, 0x0F);
	COORD cursor;
	cursor.X = 20;
	cursor.Y = 0;
	SetConsoleCursorPosition(hStdout, cursor);
	std::cout << " Home Cells:";
	cursor.X = 20;
	cursor.Y = 1;
	SetConsoleCursorPosition(hStdout, cursor);
	std::cout << " ";
	for (int index = 0; index < 4; index++) 
	{
		if (hovering == 'H' && h_index1 == index)
			SetConsoleTextAttribute(hStdout, 0x0A);
		if (selected == 'H' && s_index1 == index)
			SetConsoleTextAttribute(hStdout, 0x09);
		if (!m_homecells[index].isEmpty()) 
		{
			m_homecells[index].Peek().Display();
		}
		else 
		{
			Card empty;
			empty.Display();
		}
		SetConsoleTextAttribute(hStdout, 0x0F);
	}
}

/****************
Purpose: display all the homecell cards with extra info about hovering/selected card (uses colors)
Precondition: indicies must be valid
Postcondition: -
*****************/
void HomeCell::Display(chosenCard hovering, chosenCard selected)
{
	Display(hovering.location, hovering.index1, hovering.index2, selected.location, selected.index1, selected.index2);
}

