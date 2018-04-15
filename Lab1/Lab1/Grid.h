/***********************
 Author: Garrett Fechter
 Purpose: A header file for Grid
 Date Created:	4/11/2018
 Modifications:	
************************/

#include "Tile.h"
#include "Array2D.h"

#ifndef GRID_H
#define GRID_H
/*************************
 Class: Grid
 Purpose: A class for an Alchemy (PopCap) game
	Holds a 2 dimensional array of tiles, and performs
	various operations on those tiles
 Manager Functions:
 Methods:
**************************/
class Grid 
{
public:
	Grid();
	Grid(const Grid & copy);
	Grid(int length, int width);
	Grid(int length, int width, int level);
	Grid & operator=(const Grid & rhs);
	~Grid();
	Array2D<Tile> & GetGrid();
	void SetGrid(const Array2D<Tile> & newGrid);
	bool CheckAdjacent(int row, int col, Tile & tile) const;
	bool CheckRowComplete(int row) const;
	bool CheckColComplete(int col) const;
	bool CheckBoardComplete() const;
	Tile GenerateTile() const;
	int InsertTile(int row, int col, Tile & tile);//returns # of sides new block touches
	void ClearRow(int row);
	void ClearCol(int col);
	void ClearTile(int row, int col);
	void Display();
	int GetLevel() const;
	void SetLevel(int level);
private:
	Array2D<Tile> m_grid;
	int m_level; //the amount of colors/symbols beyond 5
};

#endif