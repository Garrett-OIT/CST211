//Garrett Fechter
//Purpose: freecells of the game freecell
//Created 2018
//Modified: 

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

/*
class: FreeCell
Purpose: functionality that freecells have in the game freecell
functions:
	FreeCell();
		default ctor. empty cards
	FreeCell(const FreeCell & copy);
		copy ctor
	FreeCell & operator = (const FreeCell & rhs);
		overloaded assignment operator
	~FreeCell();
		dtor
	bool Place(Card card, int location);
		place a card at location
	Card Remove(int location);
		remove a card at location
	int NumFree();
		get the # of free freecellsj
	Card GetCard(int location);
		get the card at location
	void Display();
		display all the cards
	void Display(char hovering, int h_index1, int h_index2, char selected, int s_index1, int s_index2);
		display all the cards with some info about a hovering card and selected card
	void Display(chosenCard hovering, chosenCard selected);
		display all the cards with some info about a hovering card and selected card
*/

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
	Array1D<Card> m_freecells;//the cards in the freecells
};

#endif // !FREE_CELL_H
