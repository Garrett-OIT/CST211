//Garrett Fechter
//Purpose: 
//Created 2017
//Modified: 2018 - added Display function

#ifndef CARD_H
#define CARD_H

enum CardRank { //an enum for the different card ranks, starts at 0
	ACE = 0, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, EMPTY_R
};

enum CardSuit { //enum for different card suits
	CLUBS = 0, DIAMONDS, HEARTS, SPADES, EMPTY_S
};

/**************************************
* Class: Card
* 	This class models a cards of various ranks andd suits, which are listed in the enumerated data types above
* Data Members:
*		CardRank m_rank;//the rank of the card
*		CardSuit m_suit;//the suit of the card
* Constructors:
*	Card();
*		default ctor. the default rank/suit for a card is Ace of Clubs
*	Card(CardRank rank, CardSuit suit)
*		ctor that takes the rank and suit to intialize the card to
*	Card(const Card & copy);
*		copy ctor
* Modifiers:
*	Card & operator = (const Card & rhs)
*		overloaded assignment operator
*	void setRank(CardRank rank)
*		setter for the rank of the card
*	void setSuit(CardSuit suit)
*		setter for the suit of the card
*	~Card()
*		destructor. since no memory is allocated, it's an empty dtor
* Methods: 
*	CardRank getRank() const
*		getter for the rank of the card
*	CardSuit getSuit() const
*		getter for the suit of the card
*****************************************/
class Card 
{
	public:
		Card();//default ctor
		Card(CardRank rank, CardSuit suit);//ctor that takes the rank and suit
		Card(const Card & copy);//copy ctor
		Card & operator = (const Card & rhs);//overloaded assignment operator
		bool operator == (const Card & rhs);//overloaded assignment operator
		void setRank(CardRank rank);//setter for the rank of the card
		void setSuit(CardSuit suit);//setter for the suit of the card
		CardRank getRank() const;//getter for the rank of the card
		CardSuit getSuit() const;//getter for the suit of the card
		void Display() const; 
		bool isEmpty() const;
		~Card();//destructor. since no memory is allocated, it's an empty dtor
private:
		CardRank m_rank;//the rank of the card
		CardSuit m_suit;//the suit of the card
};

#endif
