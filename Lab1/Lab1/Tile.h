/*******************************
	Author: Garrett Fechter
	Purpose: Header file for Tile
	Date Created: 4/11/2018
	Modifications:

******************************/
#ifndef TILE_H
#define TILE_H

/********************************
 Class: Tile
 Purpose: A Tile that will be used in making the
	game Alchemy (PopCap)
 Manager Functions:
 Methods:
************************************/
class Tile 
{
public:
	Tile();
	Tile(int color, char shape);
	Tile(const Tile & copy);
	Tile & operator=(const Tile & rhs);
	~Tile();
	char GetShape() const;
	void SetShape(char shape);
	int GetColor() const;
	void SetColor(int color);

private:
	int m_color; //the color of this tile
		//bits 3:0 are (text color) intensity, red, green blue
		//bits 7:4 are (background color) intensity, red, green, blue
	char m_shape; //the shape of the tile, just a char

};

#endif 