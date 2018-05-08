#ifndef PLAY_CELL_H
#define PLAY_CELL_H

#include "card.h"
#include "Array1D.h"
#include "Stack_LL.h"

class PlayCell
{
public:
	PlayCell();
	PlayCell(const PlayCell & copy);
	PlayCell & operator = (const PlayCell & rhs);
	~PlayCell();
	Card GetCard(int index, int cellNum);
	bool Place(int index, Card card);
	int numFree();
	void RemoveCard(int cellNum);
	void Display();
	void Display(char flag, int index);
	void Display(char flag, int index, char flag2, int index2);
private:
	Array1D<Stack_LL<Card>> m_playcells;
};

#endif // !PLAY_CELL_H
