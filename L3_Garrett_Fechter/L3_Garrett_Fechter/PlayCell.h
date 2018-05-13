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
	Array1D<Stack_LL<Card>> m_playcells;
};

#endif // !PLAY_CELL_H
