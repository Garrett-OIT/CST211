//Garrett Fechter
//Purpose: play cells of free cell the game
//Created 2018
//Modified: 

#ifndef PLAY_CELL_H
#define PLAY_CELL_H

#include "card.h"
#include "Array1D.h"
#include "Stack_LL.h"

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
	class: PlayCell
	Purpose: play cell area of freecell the game
	member funcs:
	PlayCell();
		default ctor. empty cards. 12 stacks in playcell array
	PlayCell(const PlayCell & copy);
		copy ctor
	PlayCell & operator = (const PlayCell & rhs);
		overloaded assignment operator
	~PlayCell();
		dtor
	Card GetCard(int index, int cellNum);
		get a card at index index in the cell number cellNum
	int GetLength(int index);
		get the length of a stack
	bool Moveable(int numFreeCells, int cellNum, int index);
		check whether or not a card is moveable
	bool Place(Card card, int index);
		place a card on a stack
	void Init(int seed = -1);
		intiizlize the stacks to starting game conditions
	int numFree();
		the nunmber of free play cells
	void RemoveCard(int cellNum);
		pop a card off a stack
	void Display();
		display all the cards
	void Display(char hovering, int h_index1, int h_index2, char selected, int s_index1, int s_index2);
		display all the cards with some extra color info for a hovering card and a selected card
	void Display(chosenCard hovering, chosenCard selected);
		display all the cards with some extra color info for a hovering card and a selected card
*/

class PlayCell
{
public:
	PlayCell();
	PlayCell(const PlayCell & copy);
	PlayCell & operator = (const PlayCell & rhs);
	~PlayCell();
	Card GetCard(int index, int cellNum);
	int GetLength(int index);
	bool Moveable(int numFreeCells, int cellNum, int index);
	bool Place(Card card, int index);
	void Init(int seed = -1);
	int numFree();
	void RemoveCard(int cellNum);
	void Display();
	void Display(char hovering, int h_index1, int h_index2, char selected, int s_index1, int s_index2);
	void Display(chosenCard hovering, chosenCard selected);
private:
	Array1D<Stack_LL<Card>> m_playcells;//the cards in the playcells
};

#endif // !PLAY_CELL_H
