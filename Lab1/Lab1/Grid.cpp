#include <windows.h>
#include <iostream>
#include "Grid.h"
#include <cstdlib>
#include <ctime>

#define BACKGROUND_GOLD 0x60
#define FOREGROUND_WHITE 0x0F
#define BACKGROUND_BLACK 0x00

/******************************
Method: Grid
Purpose: Default ctor
Precondition: -
Postcondition: Creates new Grid. Empty m_grid. m_level = 0. Seeds rand
*******************************/
Grid::Grid() : m_grid(), m_level(0)
{
	srand(time(NULL));
}

/******************************
Method: Grid(const Grid & copy)
Purpose: Copy ctor. 
Precondition: Takes existing Grid. 
Postcondition: Creates new Grid with same properties as copy. Seeds rand
*******************************/
Grid::Grid(const Grid & copy) : m_grid(copy.m_grid), m_level(copy.m_level)
{ 
	srand(time(NULL));
}

/******************************
Method: Grid(int length, int width) 
Purpose: Ctor that takes length and width
Precondition: Takes 0 or positive length and width (Array2D will throw exception)
Postcondition: Returns new Grid with level 0 and specified dimensions. Seeds rand
*******************************/
Grid::Grid(int length, int width) : m_grid(length, width), m_level(0)
{ 
	srand(time(NULL));
}

/******************************
Method: Grid(int length, int width, int level)
Purpose: Ctor that specifies dimensions and level
Precondition: Takes 0 or positive length and width (Array2D will throw exception)
	-2 <= level <- 2
Postcondition: Returns new Grid with specified dimensions & level. Seeds rand
*******************************/
Grid::Grid(int length, int width, int level) : m_grid(length, width), m_level(level)
{ 
	if (level < -2 || level > 2)
		throw Exception("Level is out of bounds");
	srand(time(NULL));
}

/******************************
Method:Grid & Grid::operator=(const Grid & rhs)
Purpose: Assigment operator for Grid
Precondition: Takes an existing Grid
Postcondition: Changes Grid to have same properties as right hand side
	Returns this Grid by reference
*******************************/
Grid & Grid::operator=(const Grid & rhs)
{
	m_grid = rhs.m_grid;
	m_level = rhs.m_level;
	return *this;
}

/******************************
Method: ~Grid()
Purpose: Dtor for Grid
Precondition: -
Postcondition: Resets level to 0. m_grid is deallocated
*******************************/
Grid::~Grid()
{
	m_level = 0;
}

/******************************
Method: Array2D<Tile>& Grid::GetGrid()
Purpose: Getter for m_grid
Precondition: - 
Postcondition: Returns m_grid by reference
*******************************/
Array2D<Tile>& Grid::GetGrid()
{
	return m_grid;
}

/******************************
Method: SetGrid(const Array2D<Tile>& newGrid)
Purpose: Setter for m_grid
Precondition: Takes existing grid by reference
Postcondition: sets m_grid to a copy of newgrid
*******************************/
void Grid::SetGrid(const Array2D<Tile>& newGrid)
{
	m_grid = newGrid;
}

/******************************
Method: bool CheckAdjacent(introw, int col, Tile & tile) const
Purpose: Returns whether or not its valid to placed tile at location
	in m_grid specified by row col
Precondition: row and col must be in bounds or will throw exception
Postcondition: returns true if it can be placed, else false
*******************************/
bool Grid::CheckAdjacent(int row, int col, Tile & tile) const
{
	bool okToPlace = true;
	bool hasNeighbor = false;
	char compareShape;
	int compareColor;
	if (m_grid[row][col].GetShape() != ' ')
		throw Exception("Tried to place over existing shape!");
	try
		{
			compareShape = m_grid[row - 1][col].GetShape();
			compareColor = m_grid[row - 1][col].GetColor();
			if (!((0xF & compareColor) == (0xF & tile.GetColor()) || compareShape == tile.GetShape() || compareShape == ' ' || compareShape == '#'))
			{ //must match in fg color or shape, or be blank, or be a wild card
				//above block makes placement invalid
				okToPlace = false;
			}
			if (compareShape != ' ')
				hasNeighbor = true;
		}
	catch (Exception & e) //above block doesn't exist
		{ }
	
	try
		{
			compareShape = m_grid[row][col + 1].GetShape();
			compareColor = m_grid[row][col + 1].GetColor();
			if (!((0xF & compareColor) == (0xF & tile.GetColor()) || compareShape == tile.GetShape() || compareShape == ' ' || compareShape == '#'))
			{
				//right block makes placement invalid
				okToPlace = false;
			}
			if (compareShape != ' ')
				hasNeighbor = true;
		}
	catch (Exception & e) //right block doesn't exist
		{ }

	try
		{
			compareShape = m_grid[row + 1][col].GetShape();
			compareColor = m_grid[row + 1][col].GetColor();
			if (!((0xF & compareColor) == (0xF & tile.GetColor()) || compareShape == tile.GetShape() || compareShape == ' ' || compareShape == '#'))
			{
				//below block makes placement invalid
				okToPlace = false;
			}
			if (compareShape != ' ')
				hasNeighbor = true;
		}
	catch (Exception & e) //below block doesn't exist
		{ }

		try
		{
			compareShape = m_grid[row][col - 1].GetShape();
			compareColor = m_grid[row][col - 1].GetColor();
			if (!((0xF & compareColor) == (0xF & tile.GetColor()) || compareShape == tile.GetShape() || compareShape == ' ' || compareShape == '#'))
			{
				//left block makes placement invalid
				okToPlace = false;
			}
			if (compareShape != ' ')
				hasNeighbor = true;
		}
	catch (Exception & e) //left block doesn't exist
		{ }

	if (tile.GetShape() == '#')
		okToPlace = true; //wildcards don't have to match anything
	if (!hasNeighbor)
		okToPlace = false; //must be placed next to non-empty tile
	return okToPlace;
}

/******************************
Method:bool Grid::CheckRowComplete(int row) const
Purpose: Check whether or not a row is complete (non empty tiles in all positions)
Precondition: Takes in-bounds row, the row to check for completeness
Postcondition: Returns true if row is complete
*******************************/
bool Grid::CheckRowComplete(int row) const
{
	int complete = true;
	for (int col = 0; col < m_grid.GetColumn(); col++) 
	{
		if (m_grid[row][col].GetShape() == ' ')
			complete = false;
	}
	return complete;
}

/******************************
Method:bool Grid::CheckColComplete(int row) const
Purpose: Check whether or not a col is complete (non empty tiles in all positions)
Precondition: Takes in-bounds col, the col to check for completeness
Postcondition: Returns true if col is complete
*******************************/
bool Grid::CheckColComplete(int col) const
{
	bool complete = true;
	for (int row = 0; row < m_grid.GetRow(); row++) 
	{
		if (m_grid[row][col].GetShape() == ' ')
			complete = false;
	}
	return complete;
}

/******************************
Method: bool Grid::CheckBoardComplete() const
Purpose: Check whether or not the board is complete, that is all tiles have a 
	gold background and the game has been won
Precondition: -
Postcondition: returns true if the board is ocmplete, else false
*******************************/
bool Grid::CheckBoardComplete() const
{
	bool complete = true;
	for (int row = 0; complete && row < m_grid.GetRow(); row++) 
	{
		for (int col = 0; complete && col < m_grid.GetColumn(); col++) 
		{
			if ((m_grid.Select(row, col).GetColor() & BACKGROUND_GOLD) != BACKGROUND_GOLD)
				complete = false;
		}
	}
	return complete;
}

/******************************
Method: Tile Grid::GenerateTile() const
Purpose: Generates a random tile from A-F with +range of level and same color range
		and also # and X (skull and crossbones)
Precondition: -
Postcondition: returns a new tile within constraints
*******************************/
Tile Grid::GenerateTile() const
{
	int shapeChoices = 5 + m_level + 2; //symbols, plus wild card and X
	int chosenShape = rand() % shapeChoices;
	int colorChoices = 5 + m_level; //number of available colors
	char newTileShape;
	int newTileColor = (rand() % colorChoices) + 9;//range is 9 to F, or 9 to <F
	//which is text color green to white
	//decides new tile shape	
	if (chosenShape < shapeChoices - 2) {//is a symbol 
		newTileShape = static_cast<char>(chosenShape + 65);//gets a character
	}
	else if (chosenShape == shapeChoices - 2)
	{

		newTileShape = '#';//wild card
		newTileColor = FOREGROUND_WHITE;//white text
	}
	else {
		newTileShape = 'X';//destroys a tile
		newTileColor = FOREGROUND_WHITE;//white text
	}
	return Tile(newTileColor, newTileShape); 
}

/******************************
Method: int Grid::InsertTile(int row, int col, Tile & tile)
Purpose: Inserts tile at location specified, return how many sides that tile
	borders if insertion successful. CheckAdjacent must return true
Precondition: takes in-bounds row and col
Postcondition: returns the number of sides tile borders. Tile inserted
*******************************/
int Grid::InsertTile(int row, int col, Tile & tile)
{
	char shape = '_';//used to check if adjacent tiles are empty
	int sides = 0;//the numbers of sides new block touches
	if (row >= m_grid.GetRow() || col >= m_grid.GetColumn())
		throw Exception("Out of bounds");
	try {
		if (m_grid[row][col].GetShape() != ' ')
			throw Exception("Tried to insert tile on top of another one!");
		Tile tile_differentBG((tile.GetColor() & 0x0F) | (m_grid[row][col].GetColor() & 0xF0), tile.GetShape());
		//take old tiles background and new tiles foreground
		m_grid.Select(row, col) = tile_differentBG;
		//starting checking for adjacent blocks
		try //left
		{
			shape = m_grid[row - 1][col].GetShape();
			if (shape != ' ')
			{
				++sides;
			}
		}
		catch (Exception & e) //block doesn't exist
		{
		}

		try //above
		{
			shape = m_grid[row][col + 1].GetShape();
			if (shape != ' ')
			{
				++sides;
			}
		}
		catch (Exception & e) //block doesn't exist
		{
		}

		try //right
		{
			shape = m_grid[row + 1][col].GetShape();
			if (shape != ' ')
			{
				++sides;
			}
		}
		catch (Exception & e) //block doesn't exist
		{
		}

		try //below
		{
			shape = m_grid[row][col - 1].GetShape();
			if (shape != ' ')
			{
				++sides;
			}
		}
		catch (Exception & e) //block doesn't exist
		{

		}
	}
	catch (Exception & e) { } //block doesn't exist
	return sides;
}

/******************************
Method: void Grid::ClearRow(int row)
Purpose: clears row specified with empty tiles with gold background,
	if checkrow returns true
Precondition: Takes in-bounds row
Postcondition: Clears a row. 
*******************************/
void Grid::ClearRow(int row)
{
	if (!CheckRowComplete(row)) 
	{
		throw Exception("Can't clear a row that isn't complete");
	}
	for (int i = 0; i < m_grid.GetColumn(); i++) 
	{
		m_grid.Select(row, i) = Tile(BACKGROUND_GOLD, ' ');//gold space
	}
}

/******************************
Method: void Grid::ClearCol(int col)
Purpose: clears col specified with empty tiles with gold background,
	if checkcol returns true
Precondition: Takes in-bounds col
Postcondition: Clears a col. 
*******************************/
void Grid::ClearCol(int col)
{
	if (!CheckColComplete(col))
	{
		throw Exception("Can't clear a col that isn't complete");
	}
	for (int i = 0; i < m_grid.GetRow(); i++)
	{
		m_grid.Select(i, col) = Tile(BACKGROUND_GOLD, ' ');//gold space
	}
}

/******************************
Method: void Grid::Display()
Purpose: Iterates through m_grid and displays each tile
Precondition: - 
Postcondition: Outputs to console
*******************************/
void Grid::Display()
{
	HANDLE hStdout = 0;
	COORD cursor;
	cursor.X = 0;
	cursor.Y = 1;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < m_grid.GetRow(); i++) //output row labels
	{
		SetConsoleCursorPosition(hStdout, cursor);
		std::cout << std::hex << i << std::dec;
		cursor.Y++;
	}
	cursor.X = 1;
	cursor.Y = 0;
	SetConsoleCursorPosition(hStdout, cursor);
	for (int i = 0; i < m_grid.GetColumn(); i++)
		std::cout << std::hex << i << std::dec;
	cursor.X = 1;
	cursor.Y = 1;
	for (int i = 0; i < m_grid.GetRow(); i++) 
	{
		SetConsoleCursorPosition(hStdout, cursor);
		for (int j = 0; j < m_grid.GetColumn(); j++) 
		{
			m_grid[i][j].Display();
		}
		cursor.Y++;
	}
	std::cout << "\n";
	SetConsoleTextAttribute(hStdout, FOREGROUND_WHITE | BACKGROUND_BLACK);
	cursor.X = 0;
	cursor.Y = m_grid.GetColumn() + 1;
	SetConsoleCursorPosition(hStdout, cursor);
}

/******************************
Method: int Grid::GetLevel() const
Purpose: Getter for m_level
Precondition: -
Postcondition: returns m_level
*******************************/
int Grid::GetLevel() const
{
	return m_level;
}

/******************************
Method: void Grid::SetLevel(int level)
Purpose: setter for m_level
Precondition: -
Postcondition: Sets m_level to level. -2 <= level <- 2, otherwise 
	will throw an exception
*******************************/
void Grid::SetLevel(int level)
{
	if (level < -2 || level > 2)
		throw Exception("Level specified is out of bounds");
	m_level = level;
}
