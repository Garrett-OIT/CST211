#include "Grid.h"

#ifndef ALCHEMY_H
#define ALCHEMY_H
class Alchemy
{
public:
	Alchemy();
	Alchemy(const Alchemy & copy);
	Alchemy & operator=(const Alchemy & rhs);
	bool Start(int level);
	const Grid  & GetBoard() const;
	void SetBoard(Grid & board);
	void DisplayScore();
	~Alchemy();

private:
	bool PlaceTile(Tile & current);
	Grid m_board;
	Array1D<Tile> m_cauldron;
	int m_score;
};
#endif