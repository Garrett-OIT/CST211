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
	Tile();
		A default ctor. Initializes color to 0x0F (black on white)
		and shape to ' '
	Tile(int color, char shape);
		Ctor that initializes m_color to masked (0xFF) color input and
		m_shape to shape
	Tile(const Tile & copy);
		Copy ctor
	Tile & operator=(const Tile & rhs);
		Overloaded assigment operator
	~Tile();
		Simple dtor (no memory). Resets m_color to 0x0F (black on white
		and m_shape to ' '
 Methods:
	char GetShape() const;
		A getter for m_shape
	void SetShape(char shape);
		 A setter for m_shape
	int GetColor() const;
		A getter for m_color
	void SetColor(int color);
		A setter for m_color
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