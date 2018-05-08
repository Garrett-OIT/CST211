#include "PlayCell.h"

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

bool PlayCell::Place(int index, Card card)
{
	bool placed = false;
	if (m_playcells[index].Peek().getSuit() == card.getSuit() && m_playcells[index].Peek().getRank() == card.getRank() - 1)
	{
		m_playcells[index].Push(card);
		placed = true;
	}
	return placed;
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
