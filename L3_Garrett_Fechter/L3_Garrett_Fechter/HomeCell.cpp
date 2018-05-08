#include "HomeCell.h"
#include <iostream>
#include <windows.h>

HomeCell::HomeCell() : m_homecells(4)
{ 
	for (int i = 0; i < 4; i++)
	{
		m_homecells[i].SetSize(12);
	}
}

HomeCell::HomeCell(const HomeCell & copy) : m_homecells(copy.m_homecells)
{ }

HomeCell & HomeCell::operator=(const HomeCell & rhs)
{
	m_homecells = rhs.m_homecells;
	return *this;
}

HomeCell::~HomeCell()
{
	for (int i = 0; i < 4; i++)
	{
		m_homecells[i].SetSize(0);
		m_homecells[i].SetSize(12);
	}
}

bool HomeCell::win()
{
	bool won = true;
	for (int i = 0; i < 4; i++)
	{
		if (m_homecells[i].Peek().getRank() != KING)
			won = false;
	}
	return won;
}

bool HomeCell::Place(Card card, int location)
{
	bool placed = false;
	CardRank ranks[13] = { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };//array of all possible ranks
	CardSuit suits[4] = { CLUBS, HEARTS, SPADES, DIAMONDS };//array of all suits
	if (m_homecells[location].Size() == 0) 
	{
		m_homecells[location].Push(card);
		placed = true;
	}
	else if (m_homecells[location].Peek().getSuit() == card.getSuit() && m_homecells[location].Peek().getRank() == (card.getRank() - 1))
	{
		m_homecells[location].Push(card);
		placed = true;
	}
	return placed;
}

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
