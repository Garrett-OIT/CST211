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

class Game 
{
public:
	Game();
	~Game();
	bool Start(int seed = -1);
	Game & operator = (const Game & rhs);
	Game(const Game & copy);
private:
	PlayCell m_playcell;
	HomeCell m_homecell;
	FreeCell m_freecell;
	chosenCard m_hovering;
	chosenCard m_selected;
};

#endif