//Garrett Fechter
//Purpose: instantiate a game of freecell and play it
//Created 2018
//Modified: 

#include "Game.h"
#include <iostream>

int main() 
{
	Game playing;//the game of freecell
	playing.Start();//put 0 in here to not shuffle, aka ez-mode
	cout << "\n Press any key to continue...\n";
	_getch();
	return 0;
}