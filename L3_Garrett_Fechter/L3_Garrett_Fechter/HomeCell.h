#ifndef HOME_CELL_H
#define HOME_CELL_H

#include "Array1D.h"
#include "Stack_A.h"
#include "card.h"

#ifndef CHOSEN_CARD
#define CHOSEN_CARD
struct chosenCard 
{
	char location; //'F' freecell, 'H' homecell, 'P' playcell
	int index1; //which stack (P) or array index (F and H)
	int index2; //card num in context of 'P'
};
#endif

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
	void Display(char hovering, int h_index1, int h_index2, char selected, int s_index1, int s_index2);
	void Display(chosenCard hovering, chosenCard selected);
private:
	Array1D<Stack_A<Card>> m_homecells;
};

#endif // !HOME_CELL_H
