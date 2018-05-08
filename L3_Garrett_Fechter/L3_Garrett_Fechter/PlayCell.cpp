#include "PlayCell.h"
#include <windows.h>
#include "deck.h"

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
	Card * cards = new Card[m_playcells[cellNum].Size() - index];
	int length = m_playcells[cellNum].Size();
	int i = 0;
	int j = length;
	for (; j > index; i++, j--)
		cards[i] = m_playcells[cellNum].Pop();
	Card ret = m_playcells[cellNum].Pop();
	cards[index] = ret;
	for (int i = 0; i <= index; i++)
	{
		m_playcells[cellNum].Push(cards[i]);
	}
	return ret;
}

bool PlayCell::Place(Card card, int index)
{
	bool placed = false;
	if (m_playcells[index].isEmpty())
	{
		m_playcells[index].Push(card);
		placed = true;
	}
	else if (m_playcells[index].Peek().getSuit() == card.getSuit() && m_playcells[index].Peek().getRank() == card.getRank() - 1)
	{
		m_playcells[index].Push(card);
		placed = true;
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
		if (m_playcells[i].Peek().isEmpty())
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
		while (!copy_stack[index].isEmpty()) 
		{
			if (hovering == 'P' && numPopped == h_index2 && h_index1 == index)
				SetConsoleTextAttribute(hStdout, 0x0A);
			if (selected == 'P' && numPopped == s_index2 && s_index1 == index)
				SetConsoleTextAttribute(hStdout, 0x09);
			copy_stack[index].Pop().Display();
			SetConsoleTextAttribute(hStdout, 0x0F);
			numPopped++;
			cursor.Y -= 4;
			SetConsoleCursorPosition(hStdout, cursor);
		}
		cursor.X += 5;
		SetConsoleCursorPosition(hStdout, cursor);
	}
	cursor.Y = max;
	cursor.X = 0;
	SetConsoleCursorPosition(hStdout, cursor);

}
