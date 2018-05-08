#ifndef FREE_CELL_H
#define FREE_CELL_H

#include "Array1D.h"
#include "card.h"

class FreeCell
{
public:
	FreeCell();
	FreeCell(const FreeCell & copy);
	FreeCell & operator = (const FreeCell & rhs);
	~FreeCell();

	bool Place(Card card, int location);
	Card Remove(int location);
	int NumFree();
	Card GetCard(int location);
	void Display();
	void Display(char flag, int index);
	void Display(char flag, int index, char flag2, int index2);
private:
	Array1D<Card> m_freecells;
};

#endif // !FREE_CELL_H
