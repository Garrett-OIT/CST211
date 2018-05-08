#include "FreeCell.h"
#include <iostream>
#include <windows.h>

Card EmptyCard(EMPTY_R, EMPTY_S);

FreeCell::FreeCell() : m_freecells(4)
{ }

FreeCell::FreeCell(const FreeCell & copy) : m_freecells(copy.m_freecells)
{ }
FreeCell & FreeCell::operator=(const FreeCell & rhs)
{
	m_freecells = rhs.m_freecells;
	return *this;
}

FreeCell::~FreeCell()
{ 
	m_freecells.SetLength(0);
	m_freecells.SetLength(4);
}

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

Card FreeCell::Remove(int location)
{
	Card ret = m_freecells[location];
	m_freecells[location] = EmptyCard;
	return ret;
}

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

Card FreeCell::GetCard(int location)
{
	return m_freecells[location];
}

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

