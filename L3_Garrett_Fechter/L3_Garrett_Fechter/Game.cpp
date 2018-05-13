#include "Game.h"

Game::Game() : m_hovering({ 'F', 0, 0 }), m_selected({ ' ', 0, 0 })
{ }

Game::~Game()
{ }

void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

bool Game::Start(int seed)
{
	ClearScreen();
	cout << "Hello and welcome to Freecell!\n";
	cout << "Use arrow keys to move the card you're hovering over (green outline)\n";
	cout << "Use spacebar to choose a card, then move around and put that card somewhere\n";
	cout << "If you want to exit, press e at any time\n";
	cout << "A quick note - enable legacy console to display correctly\n";
	cout << "Press any key to continue...\n";
	char wait;
	wait = _getch();
	m_playcell.Init(seed);
	char read = 'q';
	while (read != 'e' && !m_homecell.win())
	{
		while (read != ' ' && read != 'e')
		{
			ClearScreen();
			m_homecell.Display(m_hovering, m_selected);
			m_freecell.Display(m_hovering, m_selected);
			m_playcell.Display(m_hovering, m_selected);
			read = _getch();
			if (read == -32 || read == 0 || read == 0xE0)
			{ //arrow key
				read = _getch();
				switch (read)
				{
				case 'H': //up
					if (m_hovering.location == 'P')
					{
						if (m_hovering.index2 < m_playcell.GetLength(m_hovering.index1) - 1)
							m_hovering.index2++;
						else
						{
							if (m_hovering.index1 < 4)
								m_hovering.location = 'F';
							else
							{
								m_hovering.location = 'H';
								m_hovering.index1 -= 4;
							}
						}
					}
					break;
				case 'P': //down 
				{
					switch (m_hovering.location)
					{
					case 'F':
						m_hovering.location = 'P';
						m_hovering.index2 = m_playcell.GetLength(m_hovering.index1) - 1;
						if (0 > m_hovering.index2)
							m_hovering.index2 = 0;
						break;
					case 'H':
						m_hovering.location = 'P';
						m_hovering.index1 += 4;
						m_hovering.index2 = m_playcell.GetLength(m_hovering.index1) - 1;
						if (0 > m_hovering.index2)
							m_hovering.index2 = 0;
						break;
					case 'P':
						if (m_hovering.index2 > 0)
							m_hovering.index2--;
						break;
					}
					break;
				}
				case 'M': //right
					switch (m_hovering.location)
					{
					case 'F':
						if (m_hovering.index1 < 3)
							m_hovering.index1++;
						else
						{
							m_hovering.index1 = 0;
							m_hovering.location = 'H';
						}
						break;
					case 'H':
						if (m_hovering.index1 < 3)
							m_hovering.index1++;
						break;
					case 'P':
						if (m_hovering.index1 < 7)
						{
							m_hovering.index1++;
							if (m_playcell.GetLength(m_hovering.index1 - 1) == 0)
								m_hovering.index2 = m_playcell.GetLength(m_hovering.index1) - 1;
							else
								m_hovering.index2 = m_playcell.GetLength(m_hovering.index1) - 1 - (m_playcell.GetLength(m_hovering.index1 - 1) -1 - m_hovering.index2);
							if (m_hovering.index2 > (m_playcell.GetLength(m_hovering.index1)))
								m_hovering.index2 = m_playcell.GetLength(m_hovering.index1);
							if (m_hovering.index2 < 0)
								m_hovering.index2 = 0;
						}
						break;
					}
					break;
				case 'K': //left
					switch (m_hovering.location)
					{
					case 'F':
						if (m_hovering.index1 > 0)
							m_hovering.index1--;
						break;
					case 'H':
						if (m_hovering.index1 > 0)
							m_hovering.index1--;
						else
						{
							m_hovering.index1 = 3;
							m_hovering.location = 'F';
						}
						break;
					case 'P':
						if (m_hovering.index1 > 0)
						{
							m_hovering.index1--;
							if (m_playcell.GetLength(m_hovering.index1 + 1) == 0)
								m_hovering.index2 = m_playcell.GetLength(m_hovering.index1) - 1;
							else
								m_hovering.index2 = m_playcell.GetLength(m_hovering.index1) - 1 - (m_playcell.GetLength(m_hovering.index1 + 1) - 1 - m_hovering.index2);
							if (m_hovering.index2 > (m_playcell.GetLength(m_hovering.index1)))
								m_hovering.index2 = m_playcell.GetLength(m_hovering.index1);
							if (m_hovering.index2 < 0)
								m_hovering.index2 = 0;
						}
						break;
					}
					break;
				}
			}
		}
		if (read != 'e')
		{
			if (m_selected.location == ' ')
			{
				switch (m_hovering.location)
				{
				case 'F':
					m_selected = m_hovering;
					break;
				case 'P':
				{
					if (m_playcell.Moveable(m_freecell.NumFree(), m_hovering.index2, m_hovering.index1))
						m_selected = m_hovering;
					break;
				}
				}
			}
			else {
				//move selected to location
				switch (m_selected.location)
				{
				case 'F': //placing from a Free Cell
					switch (m_hovering.location)
					{
					case 'H': //to a home cell
						if (m_homecell.Place(m_freecell.GetCard(m_selected.index1), m_hovering.index1))
							m_freecell.Remove(m_selected.index1);
						break;
					case 'F': //to another free cell
						if (m_freecell.Place(m_freecell.GetCard(m_selected.index1), m_hovering.index1))
							m_freecell.Remove(m_selected.index1);
						break;
					case 'P': //to a play cell
						if (m_hovering.index2 == 0)
						{
							if (m_playcell.Place(m_freecell.GetCard(m_selected.index1), m_hovering.index1))
								m_freecell.Remove(m_selected.index1);
						}
						break;
					}
					break;
				case 'P'://placing from a play cell
					switch (m_hovering.location)
					{
					case 'H': //to a home cell
						if (m_selected.index2 == 0 && m_playcell.GetLength(m_selected.index1) != 0)
						{
							if (m_homecell.Place(m_playcell.GetCard(m_selected.index2, m_selected.index1), m_hovering.index1))
								m_playcell.RemoveCard(m_selected.index1);
						}
						break;
					case 'F': //to a free cell
						if (m_selected.index2 == 0 && m_playcell.GetLength(m_selected.index1) != 0)
						{
							if (m_freecell.Place(m_playcell.GetCard(m_selected.index2, m_selected.index1), m_hovering.index1))
								m_playcell.RemoveCard(m_selected.index1);
						}
						break;
					case 'P': //to another play cell
						if (m_hovering.index2 == 0 && m_playcell.GetLength(m_selected.index1) != 0)
						{
							int remove = 0;
							if (m_playcell.Place(m_playcell.GetCard(m_selected.index2, m_selected.index1), m_hovering.index1))
							{
								remove++;
								m_selected.index2--;
								while (m_selected.index2 >= 0)
								{
									m_playcell.Place(m_playcell.GetCard(m_selected.index2, m_selected.index1), m_hovering.index1);
									remove++;
									m_selected.index2--;
								}
								for (int i = 0; i < remove; i++)
									m_playcell.RemoveCard(m_selected.index1);
							}
						}
						break;
					}
					break;
				}
				m_selected.location = ' ';
			}
			read = '-';
		}
	}
	if (m_homecell.win())
		cout << "Congratulations!!! You won!\n";
	return m_homecell.win();
}

Game & Game::operator=(const Game & rhs)
{
	m_playcell = rhs.m_playcell;
	m_homecell = rhs.m_homecell;
	m_freecell = rhs.m_freecell;
	m_hovering = rhs.m_hovering;
	m_selected = rhs.m_selected;
	return *this;
}

Game::Game(const Game & copy) : m_playcell(copy.m_playcell), m_homecell(copy.m_homecell), m_freecell(copy.m_freecell), m_hovering(copy.m_hovering), m_selected(copy.m_selected)
{ }
