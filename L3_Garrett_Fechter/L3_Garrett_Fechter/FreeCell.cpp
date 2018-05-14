//Garrett Fechter
//Purpose: implementation of freecell
//Created 2018
//Modified: 

#include "FreeCell.h"
#include <iostream>
#include <windows.h>

Card EmptyCard(EMPTY_R, EMPTY_S); //an empty card

/****************
 Purpose: default ctor. there are 4 freecells
 Precondition: -
 Postcondition: m_freecells have length of 4
*****************/
FreeCell::FreeCell() : m_freecells(4)
{ }

/****************
Purpose: copy ctor
Precondition: -
Postcondition: -
*****************/
FreeCell::FreeCell(const FreeCell & copy) : m_freecells(copy.m_freecells)
{ }

/****************
Purpose: overloaded assignment operator
Precondition: -
Postcondition: -
*****************/
FreeCell & FreeCell::operator=(const FreeCell & rhs)
{
	m_freecells = rhs.m_freecells;
	return *this;
}

/****************
Purpose: a dtor. resets cards inside m_freecells
Precondition: -
Postcondition: resets cards inside m_freecells
*****************/
FreeCell::~FreeCell()
{
	m_freecells.SetLength(0);
	m_freecells.SetLength(4);
}

/****************
Purpose: put a card at location. true if successful (space was empty), otherwise false
Precondition: location must be in bounds
Postcondition: may put a card at location if successful
*****************/
bool FreeCell::Place(Card card, int location)
{
	bool placed = false;
	if (GetCard(location).getRank() == EMPTY_R && GetCard(location).getSuit() == EMPTY_S)
	{ //if empty
		m_freecells[location] = card;
		placed = true;
	}
	return placed;
}

/****************
Purpose:remove a card from m_freecells at location
Precondition: location must be in range
Postcondition: removes a card from m_freecells at location
*****************/
Card FreeCell::Remove(int location)
{
	Card ret = m_freecells[location];
	m_freecells[location] = EmptyCard;
	return ret;
}

/****************
Purpose: get # of empty freecells
Precondition: -
Postcondition: -
*****************/
int FreeCell::NumFree()
{
	int free = 0;
	for (int i = 0; i < 4; i++)
	{
		if (GetCard(i).getRank() == EMPTY_R && GetCard(i).getSuit() == EMPTY_S)
			free++;
	}
	return free;
}

/****************
Purpose: get a card at location
Precondition: location must be in bounds
Postcondition: -
*****************/
Card FreeCell::GetCard(int location)
{
	return m_freecells[location];
}

/****************
Purpose: display all the freecell cards
Precondition: -
Postcondition: -
*****************/
void FreeCell::Display()
{ //display each card in free cell
	//set color to white on black
	HANDLE hStdout = 0;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, 0x0F);
	COORD cursor;
	cursor.X = 0;
	cursor.Y = 0;
	SetConsoleCursorPosition(hStdout, cursor);
	std::cout << "Free Cells:";
	cursor.X = 0;
	cursor.Y = 1;
	SetConsoleCursorPosition(hStdout, cursor);
	for (int i = 0; i < 4; i++)
		m_freecells[i].Display();
}

/****************
Purpose: display all the freecell cards with some color info for a selceted/hovering card
Precondition: -
Postcondition: -
*****************/
void FreeCell::Display(char hovering, int h_index1, int h_index2, char selected, int s_index1, int s_index2)
{
	HANDLE hStdout = 0;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, 0x0F);
	COORD cursor;
	cursor.X = 0;
	cursor.Y = 0;
	SetConsoleCursorPosition(hStdout, cursor);
	std::cout << "Free Cells:";
	cursor.X = 0;
	cursor.Y = 1;
	SetConsoleCursorPosition(hStdout, cursor);
	for (int index = 0; index < 4; index++)
	{
		if (hovering == 'F' && h_index1 == index)
			SetConsoleTextAttribute(hStdout, 0x0A);
		if (selected == 'F' && s_index1 == index)
			SetConsoleTextAttribute(hStdout, 0x09);
		m_freecells[index].Display();
		SetConsoleTextAttribute(hStdout, 0x0F);
	}
}

/****************
Purpose: display all the freecell cards with some color info for a selceted/hovering card
Precondition: -
Postcondition: -
*****************/
void FreeCell::Display(chosenCard hovering, chosenCard selected)
{
	Display(hovering.location, hovering.index1, hovering.index2, selected.location, selected.index1, selected.index2);
}

