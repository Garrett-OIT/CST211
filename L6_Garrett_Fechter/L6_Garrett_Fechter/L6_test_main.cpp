//Author: Garrett Fechter
#include <iostream>
using std::cout;
using std::cin;
#include <string>
using std::string;
#include "HashTable.h"

#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a function pointer type

bool book_hashing();

struct Book 
{
	string m_title;
	string m_author;
	int m_pages;
};
bool operator==(const Book& lhs, const Book& rhs) 
{
	return ((lhs.m_title == rhs.m_title) && (lhs.m_author == rhs.m_author) && (lhs.m_pages == rhs.m_pages));
}

FunctionPointer test_functions[] = { book_hashing };


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int testNum = 0;
	// Run the test functions
	for (FunctionPointer func : test_functions)
	{
		if (func())
		{
			cout << "passed test " << testNum << "\n";
		}
		else
		{
			cout << "***** failed test number " << testNum << " *****\n";
		}
		++testNum;
	}
	cout << "\nPress Enter to Exit";
	cin.get();
}

int stringHash1(const string & data) 
{
	int ret = data.length();
	for (int i = 0; i < data.length(); i += 3) 
	{
		ret += data[i];
	}
	return ret;
}

int stringHash2(const string & data) 
{
	int ret = data.length();
	for (int i = 1; i < data.length(); i += 3) 
	{
		ret += data[i];
	}
	return ret;
}

void Display(Book book) 
{
	cout << "Title: " << book.m_title << "\n";
	cout << "Author: " << book.m_author << "\n";
	cout << "Pages: " << book.m_pages << "\n";
}

bool book_hashing() 
{
	bool pass = true;

	HashTable<string, Book> table(10);
	table.setHash(&stringHash1);
	if (table.getLen() != 10)
		pass = false;
	table.setLen(5);
	if (table.getLen() != 5)
		pass = false;

	Book temp = { "C++: An Active Learning Approach" , "Randal Albert" , 635 };
	table.Insert("0763757233" , temp);

	Book temp1 = { "Rodeo for Dummies" , "Calvin Caldwell" , 1 };
	table.Insert("7063757233" , temp1);

	Book temp3 = { "And That n There" , "Ralph Carestia" , 1 };
	table.Insert("7063757234" , temp3);

	if (table["0763757233"].m_title != "C++: An Active Learning Approach")
		pass = false;
	if (table["7063757233"].m_title != "Rodeo for Dummies")
		pass = false;
	if (table["7063757234"].m_title != "And That n There")
		pass = false;
	cout << "Table: \n";
	table.Traverse(Display);
	cout << "\n";
	
	table.setHash(stringHash2);

	if (table["0763757233"].m_title != "C++: An Active Learning Approach")
		pass = false;
	if (table["7063757233"].m_title != "Rodeo for Dummies")
		pass = false;
	if (table["7063757234"].m_title != "And That n There")
		pass = false;

	HashTable<string, Book> table2(table);
	table.setLen(0);
	if (table2["0763757233"].m_title != "C++: An Active Learning Approach")
		pass = false;
	if (table2["7063757233"].m_title != "Rodeo for Dummies")
		pass = false;
	if (table2["7063757234"].m_title != "And That n There")
		pass = false;
	cout << "Table2: \n";
	table2.Traverse(Display);
	cout << "\n";
	HashTable<string, Book> table3;
	table = table2;
	table3 = table;
	table.setLen(0);
	if (table3["0763757233"].m_title != "C++: An Active Learning Approach")
		pass = false;
	if (table3["7063757233"].m_title != "Rodeo for Dummies")
		pass = false;
	if (table3["7063757234"].m_title != "And That n There")
		pass = false;
	cout << "Table3: \n";
	table3.Traverse(Display);
	cout << "\n";
	table3.Delete("7063757234");
	if (table3["7063757234"].m_title == "And That n There")
		pass = false;
	if (table3["0763757233"].m_title != "C++: An Active Learning Approach")
		pass = false;
	if (table3["7063757233"].m_title != "Rodeo for Dummies")
		pass = false;

	return pass;
}
