#ifndef FREE_CELL_H
#define FREE_CELL_H

#include "Array1D.h"
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
	void Display(char hovering, int h_index1, int h_index2, char selected, int s_index1, int s_index2);
	void Display(chosenCard hovering, chosenCard selected);
private:
	Array1D<Card> m_freecells;
};

#endif // !FREE_CELL_H
