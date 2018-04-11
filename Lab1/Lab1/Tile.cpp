/*****************************
 Author: Garrett Fechter
 Purpose: An implementation file for Tile
 Date Created:	4/11/2018
 Modifications:
******************************/

#include "Tile.h"

/******************************
Method: Tile
Purpose: Default ctor for Tile
Precondition: -
Postcondition: Creates instance of Tile with 0x0F (black on white) 
	and space shape
*******************************/
Tile::Tile() : m_color(0x0F), m_shape(' ')
{ }

/******************************
Method: Tile(int color, char shape)
Purpose: Ctor for Tile that takes a color and shape
Precondition: -
Postcondition: Creates instance of Tile with specified color (masked
	only for text color and bg=ackground color bits) and shape
*******************************/
Tile::Tile(int color, char shape) : m_color(color & 0xFF), m_shape(shape)
{ }

/******************************
Method: Tile(const Tile & copy) 
Purpose: Copy constructor for Tile
Precondition: -
Postcondition: Creates a new instance of tile, with shape and color matching
	the copied 
*******************************/
Tile::Tile(const Tile & copy) : m_color(copy.m_color), m_shape(copy.m_shape)
{ }

/******************************
Method: operator=(const Tile & rhs)
Purpose: Assignment operator for Tile
Precondition: Takes an existing instance of Tile
Postcondition: Changes the lhs to have same color/shape as rhs
*******************************/
Tile & Tile::operator=(const Tile & rhs)
{
	m_color = rhs.m_color;
	m_shape = rhs.m_shape;
	return *this;
}
/******************************
Method: ~Tile()
Purpose: Dtor
Precondition: -
Postcondition: Resets all values
*******************************/
Tile::~Tile()
{
	m_color = 0xF0; //black text on white background
	m_shape = ' ';
}

/******************************
Method: GetShape() const
Purpose: A getter or m_shape
Precondition: -
Postcondition: Returns m_shape
*******************************/
char Tile::GetShape() const
{
	return m_shape;
}

/******************************
Method: SetShape(char shape)
Purpose: A setter for m_shape
Precondition: Takes a char
Postcondition: Changes m_shape
*******************************/
void Tile::SetShape(char shape)
{
	m_shape = shape;
}

/******************************
Method: GetColor() const
Purpose: A getter for m_color
Precondition: -
Postcondition: returns m_color
*******************************/
int Tile::GetColor() const
{
	return m_color;
}

/******************************
Method: SetColor(int color)
Purpose: A setter for m_color
Precondition: Takes an int
Postcondition: Changes m_color, masking to just the text color & bg bits
*******************************/
void Tile::SetColor(int color)
{
	m_color = color & 0xFF; //mask for last 8 bits
}
