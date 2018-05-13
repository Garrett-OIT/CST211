#include "PlayCell.h"
#include <windows.h>
#include "deck.h"

bool ValidSuits(Card card1, Card card2);

PlayCell::PlayCell() : m_playcells(8)
{ }

PlayCell::PlayCell(const PlayCell & copy) : m_playcells(copy.m_playcells)
{ }

PlayCell & PlayCell::operator=(const PlayCell & rhs)
{
	m_playcells = rhs.m_playcells;
	return *this;
}

PlayCell::~PlayCell()
{
	m_playcells.SetLength(0);
	m_playcells.SetLength(8);
}

Card PlayCell::GetCard(int index, int cellNum)
{
	Card * cards = new Card[index + 1];
	int i = 0;
	Card ret;
	if (!m_playcells[cellNum].isEmpty())
	{
		for (int i = 0; i < index; i++)
		{
			cards[i] = m_playcells[cellNum].Pop();
			ret = cards[i];
		}
		ret = m_playcells[cellNum].Pop();
		cards[index] = ret;
		for (int i = index; i >= 0; i--)
		{
			m_playcells[cellNum].Push(cards[i]);
		}
	}
	else ret = {EMPTY_R, EMPTY_S};
	delete[] cards;
	return ret;
}

int PlayCell::GetLength(int index)
{
	return m_playcells[index].Size();
}

bool PlayCell::Moveable(int numFreeCells, int index, int cellNum)
{
	bool canMove = true;
	if (GetLength(cellNum) > 1)
	{
		int movable = (1 + numFreeCells) * pow(2, numFree());
		if (index > (movable - 1))
			canMove = false;
		for (int i = index; canMove && (i > 0); i--) 
		{
			if (GetCard(i, cellNum).getRank() != 1 + GetCard(i - 1, cellNum).getRank())
				canMove = false;
			if (!ValidSuits(GetCard(i, cellNum), GetCard(i - 1, cellNum)))
				canMove = false;
		}
	}
	return canMove;
}

bool ValidSuits(Card card1, Card card2)
{
	bool valid = false;
	CardSuit suits[] = { //enum for different card suits
		CLUBS, DIAMONDS, HEARTS, SPADES, EMPTY_S
	};//0 1 2 3
	//valid: 
	//	0 1
	//	0 2	
	//  1 3
	//	1 0
	//	2 3
	//	2 0	
	//  3 1
	//	3 2
	if (card1.getSuit() == suits[0])
	{
		if (card2.getSuit() == suits[1])
			valid = true;
		else if (card2.getSuit() == suits[2])
			valid = true;
	}
	else if (card1.getSuit() == suits[1]) 
	{
		if (card2.getSuit() == suits[3])
			valid = true;
		if (card2.getSuit() == suits[0])
			valid = true;
	}
	else if (card1.getSuit() == suits[2]) 
	{
		if (card2.getSuit() == suits[3])
			valid = true;
		else if (card2.getSuit() == suits[0])
			valid = true;
	}
	else if (card1.getSuit() == suits[3]) 
	{
		if (card2.getSuit() == suits[1])
			valid = true;
		else if (card2.getSuit() == suits[2])
			valid = true;
	}
	return valid;
}

bool PlayCell::Place(Card card, int index)
{
	bool placed = false;

	if (!card.isEmpty())
	{
		if (m_playcells[index].isEmpty())
		{
			m_playcells[index].Push(card);
			placed = true;
		}
		else if (ValidSuits(card, m_playcells[index].Peek()) && m_playcells[index].Peek().getRank() == card.getRank() + 1)
		{
			m_playcells[index].Push(card);
			placed = true;
		}
	}
	return placed;
}


void PlayCell::Init(int seed)
{
	m_playcells.SetLength(0);
	m_playcells.SetLength(8);
	Deck myDeck;
	if (seed != 0)
		myDeck.shuffle(seed);
	int stackNum = 0;
	int numCards = 0;
	while (myDeck.getNumCards() > 0)
	{
		if (stackNum < 4)
		{
			m_playcells[stackNum].Push(myDeck.draw());
			numCards++;
			if (numCards == 7)
			{
				numCards = 0;
				stackNum++;
			}
		}
		else
		{
			m_playcells[stackNum].Push(myDeck.draw());
			numCards++;
			if (numCards == 6)
			{
				stackNum++;
				numCards = 0;
			}
		}
	}
}

int PlayCell::numFree()
{
	int free = 0;
	for (int i = 0; i < 8; i++)
	{
		if (m_playcells[i].isEmpty())
			free++;
	}
	return free;
}

void PlayCell::RemoveCard(int cellNum)
{
	m_playcells[cellNum].Pop();
}

void PlayCell::Display()
{
	HANDLE hStdout = 0;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	//set location to x = 0, y = 4
	COORD cursor;
	cursor.X = 0;
	cursor.Y = 5;
	SetConsoleCursorPosition(hStdout, cursor);
	SetConsoleTextAttribute(hStdout, 0x0F);
	cout << "Play Cells:";
	cursor.X = 0;
	cursor.Y = 6;
	SetConsoleCursorPosition(hStdout, cursor);
	Array1D<Stack_LL<Card>> copy_stack(m_playcells);
	int max = cursor.Y;
	for (int i = 0; i < 8; i++)
	{
		while (!copy_stack[i].isEmpty())
		{
			copy_stack[i].Pop().Display();
			cursor.Y += 4;
			SetConsoleCursorPosition(hStdout, cursor);
		}
		max = (max > cursor.Y) ? max : cursor.Y;
		cursor.Y = 6;
		cursor.X += 5;
		SetConsoleCursorPosition(hStdout, cursor);
	}
	cursor.Y = max;
	cursor.X = 0;
	SetConsoleCursorPosition(hStdout, cursor);
}

void PlayCell::Display(char hovering, int h_index1, int h_index2, char selected, int s_index1, int s_index2)
{
	HANDLE hStdout = 0;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	//set location to x = 0, y = 4
	COORD cursor;
	cursor.X = 0;
	cursor.Y = 5;
	SetConsoleCursorPosition(hStdout, cursor);
	SetConsoleTextAttribute(hStdout, 0x0F);
	cout << "Play Cells:";
	cursor.X = 0;
	cursor.Y = 6;
	SetConsoleCursorPosition(hStdout, cursor);
	Array1D<Stack_LL<Card>> copy_stack(m_playcells);
	int max = cursor.Y;
	for (int index = 0; index < 8; index++) //for each stack
	{
		int numPopped = 0;
		cursor.Y = 2 + (copy_stack[index].Size() * 4);
		SetConsoleCursorPosition(hStdout, cursor);
		max = (max > cursor.Y) ? max : (cursor.Y + 4);
		if (copy_stack[index].isEmpty())
		{
			//empty!
			cursor.Y = 2 + 4;
			SetConsoleCursorPosition(hStdout, cursor);
			if (hovering == 'P' && numPopped == h_index2 && h_index1 == index)
				SetConsoleTextAttribute(hStdout, 0x0A);
			if (selected == 'P' && numPopped == s_index2 && s_index1 == index)
				SetConsoleTextAttribute(hStdout, 0x09);
			Card empty;
			empty.Display();
			SetConsoleTextAttribute(hStdout, 0x0F);
		}
		else
		{
			while (!copy_stack[index].isEmpty())
			{
				if (hovering == 'P' && numPopped == h_index2 && h_index1 == index)
					SetConsoleTextAttribute(hStdout, 0x0A);
				if (selected == 'P' && numPopped <= s_index2 && s_index1 == index)
					SetConsoleTextAttribute(hStdout, 0x09);
				copy_stack[index].Pop().Display();
				SetConsoleTextAttribute(hStdout, 0x0F);
				numPopped++;
				cursor.Y -= 4;
				SetConsoleCursorPosition(hStdout, cursor);
			}
		}
		cursor.X += 5;
		SetConsoleCursorPosition(hStdout, cursor);
	}
	cursor.Y = max;
	cursor.X = 0;
	SetConsoleCursorPosition(hStdout, cursor);
}

void PlayCell::Display(chosenCard hovering, chosenCard selected)
{
	Display(hovering.location, hovering.index1, hovering.index2, selected.location, selected.index1, selected.index2);
}
