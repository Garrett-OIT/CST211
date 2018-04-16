/***************************
 Author: Garrett Fechter

****************************/
#include <iostream>
#include "Alchemy.h"
#include <windows.h>

#define FOREGROUND_WHITE 0x0F
#define BACKGROUND_BLACK 0x00
#define BACKGROUND_GOLD 0x60

#undef max
#define CLEAR_CIN_BUFFER cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n')
//pesky windows max macro definition

using std::cout;
using std::cin;

Alchemy::Alchemy() : m_board(5, 5), m_score(0)
{ }

Alchemy::Alchemy(const Alchemy & copy) : m_board(copy.m_board), m_cauldron(copy.m_cauldron), m_score(copy.m_score)
{ }

Alchemy & Alchemy::operator=(const Alchemy & rhs)
{
	m_board = rhs.m_board;
	m_cauldron = rhs.m_cauldron;
	m_score = rhs.m_score;
	return *this;
}

bool Alchemy::Start(int level)
{
	int length = m_board.GetGrid().GetRow();
	m_board.GetGrid().SetRow(0); //clear grid
	m_board.GetGrid().SetRow(length); //reset grid size
	m_score = 0; //reset score
	bool winnerWinner = false;
	cout << "Hello and welcome to a version of Alchemy!\n";
	cout << "If you don't know how to play, look it up online.\n";
	cout << "Are you ready to play? y/n\n";
	bool cont = true;
	char choice = '-';
	cin >> choice;
	//cout << "Would you like added difficulty? y/n\n";
	//while (cont)
	//{
	//	cin.get(choice);
	//	if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N')
	//		cont = false;
	//	else
	//	{
	//		cout << "Try that again. Would you like added difficulty? y/n\n";
	//		CLEAR_CIN_BUFFER;
	//	}
	//}
	//if (choice == 'y' || choice == 'Y')
	//	m_board.SetLevel(1);
	//otherwise level is 0, 5 characters/colors

	if (level > -2 && level <= 2)
		m_board.SetLevel(level); //otherwise level is 0

	system("CLS"); //clear screen
	Tile center(FOREGROUND_WHITE | BACKGROUND_GOLD, '#');
	m_board.InsertTile(m_board.GetGrid().GetRow() / 2, m_board.GetGrid().GetColumn() / 2, center);

	while (!m_board.CheckBoardComplete() && m_cauldron.GetLength() <= 3)
	{

		Tile current = m_board.GenerateTile();
		system("CLS");
		DisplayScore();
		m_board.Display();
		std::cout << "Here is the tile that you drew: ";
		current.Display();
		cout << "\n";
		std::cout << "Tiles in cauldron: ";
		for (int i = 0; i < m_cauldron.GetLength(); i++) 
		{
			m_cauldron[i].Display(); 
			cout << " ";
		}
		cout << "\n";
		while (!PlaceTile(current))
		{
			system("CLS");
			DisplayScore();
			m_board.Display();
			std::cout << "Tiles in cauldron: ";
			for (int i = 0; i < m_cauldron.GetLength(); i++) 
			{
				m_cauldron[i].Display(); 
				cout << " ";
			}		
			cout << "\n";
			std::cout << "That wasn't a valid place to play your tile. Try again.\n";
			std::cout << "Here is the tile that you drew: ";
			current.Display();
			cout << "\n";
		}
	}
	system("CLS");
	m_board.Display();
	if (m_board.CheckBoardComplete()) 
	{
		cout << "Congratulations, you won!!!\nYour score was " << m_score << "\n";
		winnerWinner = true;
	}

	else
	{
		std::cout << "Tiles in cauldron: ";
		for (int i = 0; i < m_cauldron.GetLength(); i++)
		{
			m_cauldron[i].Display();
			cout << " ";
		}
		cout << "\n";
		cout << "You lost. Better luck next time.\n";
	}
	return winnerWinner;
}

const Grid & Alchemy::GetBoard() const
{
	return m_board;
}

void Alchemy::SetBoard(Grid & board)
{
	m_board = board;
}

const int Alchemy::GetScore() const
{
	return m_score;
}

void Alchemy::DisplayScore() 
{
	HANDLE hStdout = 0;
	COORD cursor;
	cursor.X = m_board.GetGrid().GetRow() + 3;
	cursor.Y = 0;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdout, cursor);
	cout << "Score: " << m_score;
}

Alchemy::~Alchemy()
{ }

bool Alchemy::PlaceTile(Tile & current)
{
	bool placed = true;
	bool cont = true;
	char choice = '-';
	int rowChoice;
	int colChoice;

	if (current.GetShape() == 'X')
		cout << "That's a skull and crossbones that destroys any existing tile.\n";
	else if (current.GetShape() == '#')
		cout << "That's a wild that can go next to any existing tiles.\n";
	cout << "Enter the row you would like to place your tile: \n";
	cout << "You can also enter -1 to put ";
	current.Display();
	cout << " into the cauldron (a discard pile, you lose when 3 tiles are in here).\n";
	CLEAR_CIN_BUFFER;
	cin >> rowChoice;
	cont = true;
	while (cont) 
	{
		if ((!(rowChoice >= 0 && rowChoice < m_board.GetGrid().GetRow())) && rowChoice != -1)
		{
			cout << "Try that again.\nEnter the row you would like to place your tile: \n";
			CLEAR_CIN_BUFFER;
			cin >> rowChoice;
		}
		else
			cont = false;
	}
	system("CLS");
	DisplayScore();
	m_board.Display();

	if (rowChoice != -1) {
		cout << "You chose row " << rowChoice << "\n";
		std::cout << "Here is the tile that you drew: ";
		current.Display();
		cout << "\nEnter the column you would like to place your tile: \n";
		CLEAR_CIN_BUFFER;
		cin >> colChoice;
		cont = true;
		while (cont)
		{
			{
				if (!(colChoice >= 0 && colChoice < m_board.GetGrid().GetColumn()))
				{
					cout << "Try that again.\nEnter the column you would like to place your tile: \n";
					CLEAR_CIN_BUFFER;
					cin >> colChoice;
				}
				else
					cont = false;
			}
			//a col and row have been chosen, but might not be valid
		}
		try
		{
			if (current.GetShape() == 'X')
			{
				if (m_board.GetGrid().Select(rowChoice, colChoice).GetShape() != ' ')
				{
					m_board.GetGrid().Select(rowChoice, colChoice).SetShape(' ');
				}
				else
					placed = false; //have to set X on existing shape
			}
			else
			{
				if (m_board.CheckAdjacent(rowChoice, colChoice, current))
					m_score += 5*m_board.InsertTile(rowChoice, colChoice, current);
				else
					placed = false;
			}
		}
		catch (Exception)
		{
			placed = false;
		}
		if (placed) //check for completed row and column
		{
			if (m_cauldron.GetLength() > 0) 
			{
				m_cauldron.SetLength(m_cauldron.GetLength() - 1);
			}
			try
			{
				m_board.ClearRow(rowChoice);
			}
			catch (Exception) {}
			try
			{
				m_board.ClearCol(colChoice);
			}
			catch (Exception) {}
		}
	}
	else //they want to discard their tile 
	{
		m_cauldron.SetLength(m_cauldron.GetLength() + 1);
		m_cauldron[m_cauldron.GetLength() - 1] = current;
	}
	return placed;
}
