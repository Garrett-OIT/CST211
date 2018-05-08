#include "FreeCell.h"

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

