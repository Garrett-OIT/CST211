/************************
 Author: Garrett Fechter
 Purpose: Runs Alchemy game
 Date Created: 4/16/2018
 Modifications:
***********************/
#define _CRT_SECURE_NO_WARNINGS
#include "Alchemy.h"
#include <iostream>

int main() 
{
	Alchemy game;
	if (game.Start(0)) 
	{
		std::cout << "Congrats on winning level 1!\nProceeding to level 2...\n";
		game.Start(1);
	}
}
