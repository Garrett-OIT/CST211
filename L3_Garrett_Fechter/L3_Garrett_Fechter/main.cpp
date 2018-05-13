#include "Game.h"
#include <iostream>

int main() 
{
	Game playing;
	playing.Start();//put 0 in here to not shuffle
	cout << "\n Press any key to continue...\n";
	_getch();
	return 0;
}