//Garrett Fechter
//Purpose: implementation of card 
//Created 2018
//Modified: 

#include <windows.h>
#include <string>
#include <iostream>
#include "card.h"

Card::Card() : m_rank(EMPTY_R), m_suit(EMPTY_S)//default ctor
{ }

Card::Card(CardRank rank, CardSuit suit) : m_rank(rank), m_suit(suit)//ctor that takes the rank and suit
{ }

Card::Card(const Card & copy) : m_rank(copy.m_rank), m_suit(copy.m_suit)//copy ctor
{ }

Card & Card::operator=(const Card & rhs)//overloaded assignment operator
{
	m_rank = rhs.m_rank;//dont need to check for self reference since this won't fail
	m_suit = rhs.m_suit;
	return *this;
}

bool Card::operator==(const Card & rhs)
{
	bool matching = false;
	if (rhs.getRank() == m_rank && rhs.getSuit() == m_suit)
		matching = true;
	return matching;
}

void Card::setRank(CardRank rank)//setter for the rank of the cardlocation2
{
	m_rank = rank;
}

void Card::setSuit(CardSuit suit)//setter for the suit of the card
{
	m_suit = suit;
}

CardRank Card::getRank() const//getter for the rank of the card
{
	return m_rank;
}

CardSuit Card::getSuit() const//getter for the rank of the card
{
	return m_suit;
}

void Card::Display() const
{
	HANDLE hStdout = 0;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursor;
	char suits_Str[] = { char(5), char(4), char(3), char(6), ' ' };
	std::string ranks_Str[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", " " };
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hStdout, &info);
	cursor.X = info.dwCursorPosition.X;
	int baseX = cursor.X;
	cursor.Y = info.dwCursorPosition.Y;
	std::cout << " ___ ";
	cursor.Y++;
	cursor.X = baseX;
	SetConsoleCursorPosition(hStdout, cursor);
	std::cout << "| ";
	//save color
	int savedAttr = 0;
	savedAttr = info.wAttributes;
	//change color based on suit
	int suitColor = 0;
	if (m_suit == DIAMONDS || m_suit == HEARTS)
		suitColor = 0xC;
	else if (m_suit == CLUBS || m_suit == SPADES)
		suitColor = 0xF;
	SetConsoleTextAttribute(hStdout, suitColor);
	std::cout << ranks_Str[m_rank];
	//restore color
	SetConsoleTextAttribute(hStdout, savedAttr);
	if (ranks_Str[m_rank] != "10")
		std::cout << " |";
	else
		std::cout << "|";
	cursor.Y++;
	cursor.X = baseX;
	SetConsoleCursorPosition(hStdout, cursor);
	std::cout << "| ";
	SetConsoleTextAttribute(hStdout, suitColor);
	std::cout << suits_Str[m_suit];
	//std::cout << char(3);
	SetConsoleTextAttribute(hStdout, savedAttr);
	std::cout << " |";
	cursor.Y++;
	cursor.X = baseX;
	SetConsoleCursorPosition(hStdout, cursor);
	std::cout << " ''' ";
	cursor.Y -= 3;
	cursor.X = baseX + 5;
	SetConsoleCursorPosition(hStdout, cursor);
}

bool Card::isEmpty() const
{
	bool empty = false;
	if (m_rank == EMPTY_R && m_suit == EMPTY_S)
		empty = true;
	return empty;
}

Card::~Card()//empty dtor
{ 
	m_rank = EMPTY_R;
	m_suit = EMPTY_S;
}
