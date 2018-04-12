#include "Grid.h"
#include <cstdlib>

#define GOLD_BACKGROUND 0x60

Grid::Grid() : m_grid(), m_level(0)
{ }

Grid::Grid(const Grid & copy) : m_grid(copy.m_grid), m_level(copy.m_level)
{ }

Grid::Grid(int length, int width) : m_grid(length, width), m_level(0)
{ }

Grid::Grid(int length, int width, int level) : m_grid(length, width), m_level(level)
{ 
	if (level < -2 || level > 2)
		throw Exception("Level is out of bounds");
}

Grid & Grid::operator=(const Grid & rhs)
{
	m_grid = rhs.m_grid;
	m_level = m_level;
	return *this;
}

Grid::~Grid()
{
	m_level = 0;
}

Array2D<Tile>& Grid::GetGrid()
{
	return m_grid;
}

void Grid::SetGrid(const Array2D<Tile>& newGrid)
{
	m_grid = newGrid;
}

bool Grid::CheckAdjacent(int row, int col) const
{
	bool okToPlace = true;
	bool hasNeighbor = false;
	char shape;
	int color;
	char compareShape;
	char compareColor;
	shape = m_grid[row][col].GetShape(); //these will throw exceptions if
	color = m_grid[row][col].GetColor(); //row or col are invalid
	if (okToPlace) {
		try
		{
			compareShape = m_grid[row - 1][col].GetShape();
			compareColor = m_grid[row - 1][col].GetColor();
			if (!((0xF & compareColor) == (0xF & color) || compareShape == shape || compareShape == ' ' || compareShape == '#'))
			{ //must match in fg color or shape, or be blank, or be a wild card
				//left block makes placement invalid
				okToPlace = false;
			}
			if (compareShape != ' ')
				hasNeighbor = true;
		}
		catch (Exception & e) //left block doesn't exist
		{
		}
	}
	if (okToPlace) {
		try
		{
			compareShape = m_grid[row][col + 1].GetShape();
			compareColor = m_grid[row][col + 1].GetColor();
			if (!((0xF & compareColor) == (0xF & color) || compareShape == shape || compareShape == ' ' || compareShape == '#'))
			{
				//above block makes placement invalid
				okToPlace = false;
			}
			if (compareShape != ' ')
				hasNeighbor = true;
		}
		catch (Exception & e) //above block doesn't exist
		{ }
	}
	if (okToPlace) {
		try
		{
			compareShape = m_grid[row + 1][col].GetShape();
			compareColor = m_grid[row + 1][col].GetColor();
			{
				//right block makes placement invalid
				okToPlace = false;
			}
			if (compareShape != ' ')
				hasNeighbor = true;
		}
		catch (Exception & e) //right block doesn't exist
		{ }
	}
	if (okToPlace) {
		try
		{
			compareShape = m_grid[row][col - 1].GetShape();
			compareColor = m_grid[row][col - 1].GetColor();
			if (!((0xF & compareColor) == (0xF & color) || compareShape == shape || compareShape == ' ' || compareShape == '#'))
			{
				//below block makes placement invalid
				okToPlace = false;
			}
			if (compareShape != ' ')
				hasNeighbor = true;
		}
		catch (Exception & e) //below block doesn't exist
		{ }
	}
	if (shape == '#')
		okToPlace = true; //wildcards don't have to match anything
	if (!hasNeighbor)
		okToPlace = false; //must be placed next to non-empty tile
	return okToPlace;
}

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

bool Grid::CheckColComplete(int col) const
{
	int complete = true;
	for (int row = 0; row < m_grid.GetRow(); row++) 
	{
		if (m_grid[row][col].GetShape() == ' ')
			complete = false;
	}
	return complete;
}

//int Grid::CheckScore() const
//{
//	int sides = 0;//running total of block|block sides
//	char shape = '_';//the shape of adjacent blocks
//	char isBlock = '_';//checking to see if current tile isn't empty
//	for (int row = 0; row < m_grid.GetRow(); row++) //for each row
//	{
//		for (int col = 0; col < m_grid.GetColumn(); col++)//for each col
//		{
//			isBlock = m_grid[row][col].GetShape();
//			if (isBlock != ' ') //if current tile isn't empty
//			{
//				//starting checking for adjacent blocks
//				try //left
//				{
//					shape = m_grid[row - 1][col].GetShape();
//					if (shape != ' ')
//					{
//						++sides;
//					}
//				}
//				catch (Exception & e) //block doesn't exist
//				{ }
//
//				try //above
//				{
//					shape = m_grid[row][col + 1].GetShape();
//					if (shape != ' ')
//					{
//						++sides;
//					}
//				}
//				catch (Exception & e) //block doesn't exist
//				{ }
//
//				try //right
//				{
//					shape = m_grid[row + 1][col].GetShape();
//					if (shape != ' ')
//					{
//						++sides;
//					}
//				}
//				catch (Exception & e) //block doesn't exist
//				{ } 
//
//				try //below
//				{
//					shape = m_grid[row][col - 1].GetShape();
//					if (shape != ' ')
//					{
//						++sides;
//					}
//				}
//				catch (Exception & e) //block doesn't exist
//				{ } 
//			}
//		}
//	}
//	//sides is twice what it should be
//
//}

Tile & Grid::GenerateTile() const
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
		newTileColor = 0x06;//white text
	}
	else {
		newTileShape = 'X';//destroys a tile
		newTileColor = 0x06;//white text
	}
	Tile returnTile(GOLD_BACKGROUND | newTileColor, newTileShape); //white on gold
	return returnTile;
}

int Grid::InsertTile(int row, int col, Tile & tile)
{
	char shape = '_';//used to check if adjacent tiles are empty
	int sides = 0;//the numbers of sides new block touches
	try {
		m_grid.Select(row, col) = tile;
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

void Grid::ClearRow(int row)
{
	if (!CheckRowComplete(row)) 
	{
		throw Exception("Can't clear a row that isn't complete");
	}
	for (int i = 0; i < m_grid.GetColumn(); i++) 
	{
		m_grid.Select(row, i) = Tile(GOLD_BACKGROUND, ' ');//gold space
	}
}

void Grid::ClearCol(int col)
{
	if (!CheckColComplete(col))
	{
		throw Exception("Can't clear a col that isn't complete");
	}
	for (int i = 0; i < m_grid.GetRow(); i++)
	{
		m_grid.Select(i, col) = Tile(GOLD_BACKGROUND, ' ');//gold space
	}
}

void Grid::ClearTile(int row, int col)
{
	Tile gold_space(GOLD_BACKGROUND, ' ');
	InsertTile(row, col, gold_space);
}
