/*******************************
Author: Garrett Fechter
Purpose: Header for a basic Exception class
Date Created: 4/2/2018
Modifications:
			4/3/2018 - const methods
*****************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using std::ostream;

#ifndef EXCEPTION
#define EXCEPTION

/*********************************
 Class: Exception
 Purpose: A simple exception class, with a message that can be displayed
 Manager Functions:
	Exception()
		A default ctor, empty message
 Methods:
	const char* getMessage() const
		getter for m_msg
	Exception(const char* msg)
		ctor, takes null terminated msg at char* pointer
	Exception(Exception & copy)
		copy ctor
	~Exception()
		destructor to free m_msg memory
	Exception & operator=(const Exception &)
		overloaded assignment operator
	void setMessage(char* msg)
		setter for m_msg
	friend ostream& operator<<(ostream& os, const Exception& ex)
		an overloaded ostream insertion operator
 *********************************/
class Exception 
{
	public:
		Exception();//default ctor, empty message
		Exception(const char* msg);//ctor, takes null terminated msg at char* pointer
		Exception(const Exception & copy); //copy ctor
		~Exception();//destructor to free m_msg memory
		Exception & operator=(const Exception & rhs);//overloaded assignment operator
		const char* getMessage() const;//getter for m_msg
		void setMessage(char* msg);//setter for m_msg
		friend ostream& operator<<(ostream& os, const Exception& ex);//an overloaded ostream insertion operator
	private:
		char* m_msg; //a message containing information about the exception. null terminated
};

#endif