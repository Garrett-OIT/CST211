/*******************************
Author: Garrett Fechter
Purpose: Implementations for a basic Exception class
Date Created: 4/2/2018
Modifications:

*****************************/
#include "Exception.h"

/****************
 Purpose: A default ctor for exception
 Precondition: -
 Postcondition: Creates a new exception with a nullptr m_msg
*****************/
Exception::Exception() : m_msg(nullptr)
{}

/****************
Purpose: A convenient ctor for exception
Precondition: msg MUST be null terminated, or be a nullptr
Postcondition: Creates a new exception with a m_msg matching msg (deep copy)
*****************/
Exception::Exception(char * msg)
{
	if (msg != nullptr) //if it points to data
	{
		int length = strlen(msg); //a place to hold the length of the msg
		m_msg = new char[length + 1]; //enough room to store msg and null character
		strcpy(m_msg, msg);
	}
	else
	{
		m_msg = nullptr; //was a null pointer
	}
}

/****************
Purpose: A dtor for exception
Precondition: -
Postcondition: Frees memory for msg
*****************/
Exception::~Exception()
{
	delete[] m_msg;
}

/****************
Purpose: An overloaded = operator for exception
Precondition: -
Postcondition: Changes lhs m_msg contents. Returns a new (deep) copy of rhs m_msg in lhs 
*****************/
Exception & Exception::operator=(const Exception & rhs)
{
	if (this != &rhs) //check for self assignment
	{
		delete[] m_msg; //dump lhs msg
		m_msg = nullptr;
		if (rhs.m_msg) 
		{
			m_msg = new char[strlen(rhs.m_msg) + 1];
			strcpy(m_msg, rhs.m_msg); //deep copy 
		}

	}
	return *this;
}

/****************
Purpose: A getter for m_msg
Precondition: -
Postcondition: Returns reference to m_msg
*****************/
const char * Exception::getMessage() const
{
	return m_msg;
}

/****************
Purpose: A setter for m_msg
Precondition: Takes a null terminated (or nullptr) char*
Postcondition: Allocates memory for m_msg and deep copies data
*****************/
void Exception::setMessage(char * msg)
{
	if (msg == nullptr)
		m_msg = nullptr; //just a nullptr
	else //msg coming in isn't nullptr 
	{
		delete[] m_msg;
		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}
}


