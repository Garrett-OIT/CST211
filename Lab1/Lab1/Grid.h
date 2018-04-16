/***********************
 Author: Garrett Fechter
 Purpose: A header file for Grid
 Date Created:	4/11/2018
 Modifications:	4/16/2018 Documented
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
	Grid();
		Default ctor. Seeds rand. empty grid, level = 0
	Grid(const Grid & copy);
		Copy ctor. Seeds rand
	Grid(int length, int width);
		Ctor that specifies length & width. Level = 0. Seeds rand
	Grid(int length, int width, int level);
		Ctor that specifies length, width, level. Seeds rand. -2 <= level <= 2
	Grid & operator=(const Grid & rhs);
		Assigment operator
	~Grid();
		Simple dtor. Resets level to 0
 Methods:
	Array2D<Tile> & GetGrid();
		Getter for m_grid
	void SetGrid(const Array2D<Tile> & newGrid);
		Setter for m_grid
	bool CheckAdjacent(int row, int col, Tile & tile) const;
		Returns whether a row/col location is a valid place to put tile
	bool CheckRowComplete(int row) const;
		Checks a row number for completeness (non-empty tile in all locations)
	bool CheckColComplete(int col) const;
		Checks a row number for completeness (non-empty tile in all locations)
	bool CheckBoardComplete() const;
		Checks whether or not the whole board is gold backgrounds
	Tile GenerateTile() const;
		Generates a random tile from A-F with +range of level and same color range
		and also # and X (skull and crossbones)
	int InsertTile(int row, int col, Tile & tile);
		returns # of sides new block touches. Inserts a tile into m_grid, throws
		throws exception if a non-empty tile already at that location
	void ClearRow(int row);
		Clears a row, replacing with empty gold background tiles.
		Throws exception if you try to clear a row for which checkrow fails
	void ClearCol(int col);
		Clears a column, replacing with empty gold background tiles.
		Throws exception if you try to clear a col for which checkcol fails
	void Display();
		Iterates through m_grid and displays each tile
	int GetLevel() const;
		Getter for m_level
	void SetLevel(int level);
		Setter for m_level
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
	void Display();
	int GetLevel() const;
	void SetLevel(int level);
private:
	Array2D<Tile> m_grid;
	int m_level; //the amount of colors/symbols beyond 5
};

#endif