#include "random.h"

Random::Random() : m_range(100)
{ }

Random::Random(int range) : m_range(range)
{ }

Random::Random(const Random & copy) : m_range(copy.m_range)
{ }

Random & Random::operator=(const Random & rhs)
{
	m_range = rhs.m_range;//no need to check for self reference
	return *this;
}

int Random::getRand()
{
	srand(clock());
	return (rand() % m_range);
}

Random::~Random()
{ }
