#ifndef DECK_H
#define DECK_H

#include "random.h"
#include "card.h"

/***********************************
* Class: Deck
* Data Members:
*	Card * m_cards
*	pointer to memory that's allocated to hold all the cards in the deck
*	int m_numCards
*	the number of cards in the deck
* Contructors:
*	Deck()
*		default ctor that makes one deck
*	Deck(int numDecks)
*		makes numDecks of decks
*	Deck(const Deck & copy)
*		copy ctor
* Mutators:
*	Card draw()
*		copies a card and returns it, off the top of the deck
*	void addCards(Card * toAdd, int numOfCards)
*		add some cards to the deck
*	void shuffle()
*		mixes up the deck a whole bunch
*	void resetDeck()
*		resets the deck back to a single, ordered deck
*	void resetDeck(int numDecks)
*		resets the deck back to an ordered number of specified deck
*	~Deck()
*		dtor for m_cards
* Methods:
*	Card * getCards() const
*		getter for m_cards
*	int getNumCards() const
*		getter for m_numCards
**********************************/
class Deck 
{
public:
	Deck();//default ctor that makes one deck
	Deck(int numDecks);//makes numDecks of decks
	Deck(const Deck & copy);//copy ctor
	Deck & operator = (const Deck & rhs);//overloaded assignment operator
	Card draw();//copies a card and returns it, off the top of the deck
	Card * getCards() const;//getter for m_cards
	int getNumCards() const;//getter for m_numCards
	void addCards(Card * toAdd, int numOfCards);//add some cards to the deck
	void shuffle();//mixes up the deck a whole bunch
	void resetDeck();//resets the deck back to a single, ordered deck
	void resetDeck(int numDecks);//resets the deck back to an ordered number of specified deck
	~Deck();//dtor for m_cards
private:
	Card * m_cards;//pointer to memory that's allocated to hold all the cards in the deck
	int m_numCards;//the number of cards in the deck
};

#endif
