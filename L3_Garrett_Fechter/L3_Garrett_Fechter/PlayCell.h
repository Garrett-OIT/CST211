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
	bool Place(Card card, int index);
	void Init(int seed = -1);
	int numFree();
	void RemoveCard(int cellNum);
	void Display();
	void Display(char hovering, int h_index1, int h_index2, char selected, int s_index1, int s_index2);
private:
	Array1D<Stack_LL<Card>> m_playcells;
};

#endif // !PLAY_CELL_H
