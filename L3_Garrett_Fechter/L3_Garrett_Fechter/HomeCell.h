#ifndef HOME_CELL_H
#define HOME_CELL_H

#include "Array1D.h"
#include "Stack_A.h"
#include "card.h"

class HomeCell
{
public:
	HomeCell();
	HomeCell(const HomeCell & copy);
	HomeCell & operator = (const HomeCell & rhs);
	~HomeCell();
	bool win();
	bool Place(Card card, int location);
	void Display();
	void Display(char flag, int index);
	void Display(char flag, int index, char flag2, int index2);
private:
	Array1D<Stack_A<Card>> m_homecells;
};

#endif // !HOME_CELL_H
