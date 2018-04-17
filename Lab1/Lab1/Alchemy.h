/***************************
 Author: Garrett Fechter
 Purpose: A header file for Alchemy
 Date Created:	4/14/2018
 Modifications:	4/16/2018 Documented
*****************************/
#include "Grid.h"

#ifndef ALCHEMY_H
#define ALCHEMY_H

/**************************
 Class: Alchemy
 Purpose: Create a playable instance of the PopCap game Alchemy,
	modified to be a text based in-console version.
 Manager Functions:
	Alchemy();
		Default ctor. Empty grid, empty cauldron, score = 0
	Alchemy(const Alchemy & copy);
		Copy ctor
	Alchemy & operator=(const Alchemy & rhs);
		Assignment operator for Alchemy
	~Alchemy();
		Destructor. Resets score to 0
 Methods:
	bool Start(int level);
		Starts the game. Uses cout and cin for interacting with use
	const Grid  & GetBoard() const;
		A getter for m_board
	void SetBoard(Grid & board);
		A setter for m_board
	const int GetScore() const;
		A getter for m_score
	void DisplayScore();
		Displays score at coordinates (length of m_board, 0)
****************************/
class Alchemy
{
public:
	Alchemy();
	Alchemy(const Alchemy & copy);
	Alchemy & operator=(const Alchemy & rhs);
	bool Start(int level);
	const Grid  & GetBoard() const;
	void SetBoard(Grid & board);
	const int GetScore() const;
	void DisplayScore();
	~Alchemy();
private:
	bool PlaceTile(Tile & current);
	Grid m_board;
	Array1D<Tile> m_cauldron;
	int m_score;
};
#endif