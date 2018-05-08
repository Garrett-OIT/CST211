#include "card.h"
#include <iostream>

using std::cin;

int main() 
{
	Card demo(QUEEN, DIAMONDS);
	demo.Display();
	Card demo2(ACE, CLUBS);
	demo2.Display();
	char a;
	cin >> a;
}