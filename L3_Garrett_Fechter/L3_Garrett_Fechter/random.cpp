//Garrett Fechter
//Purpose: random's implementation
//Created 2017
//Modified:  2018 - documentation

#include "random.h"

/****************
 Purpose: default ctor. range of 100
 Precondition: - 
 Postcondition: -
*****************/
Random::Random() : m_range(100)
{ }

/****************
Purpose: ctor with specific range
Precondition: -
Postcondition: -
*****************/
Random::Random(int range) : m_range(range)
{ }

/****************
Purpose: copy ctor
Precondition: -
Postcondition: -
*****************/
Random::Random(const Random & copy) : m_range(copy.m_range)
{ }

/****************
Purpose: assignment operator
Precondition: -
Postcondition: -
*****************/
Random & Random::operator=(const Random & rhs)
{
	m_range = rhs.m_range;//no need to check for self reference
	return *this;
}

/****************
Purpose: get a random number with range m_range
Precondition: -
Postcondition: -
*****************/
int Random::getRand()
{
	srand(clock());
	return (rand() % m_range);
}

/****************
Purpose: dtor (empty)
Precondition: -
Postcondition: -
*****************/
Random::~Random()
{ }
