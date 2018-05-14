//Garrett Fechter
//Purpose: play FreeCell, the game
//Created 2018
//Modified: 

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "card.h"
#include "deck.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
using std::cout;
using std::cin;
#include <string>
#include "PlayCell.h"
#include "HomeCell.h"
#include "FreeCell.h"
using std::string;

/*
 Class: Game
 Purpose: play freecell
 functions:
	Game();
		defaukt ctor. buncha empty cards
	~Game();
		dtor. resets cards
	bool Start(int seed = -1);
		start and play the game. optional seed to specify randomness seed (-1 seeds srand, 0 specifies no shuffle)
	Game & operator = (const Game & rhs);
		overloaded assignment operator
	Game(const Game & copy);
		copy ctor
*/

class Game 
{
public:
	Game();
	~Game();
	bool Start(int seed = -1);
	Game & operator = (const Game & rhs);
	Game(const Game & copy);
private:
	PlayCell m_playcell;//the playcells of freecell
	HomeCell m_homecell;//the homecells of freecell
	FreeCell m_freecell;//thje freecells of freecell
	chosenCard m_hovering;//the caard that is currently being hovered
	chosenCard m_selected;//the card that is currently selected
};

#endif