#include "deck.h"

#define NO_CARDS_IN_DECK -1

Deck::Deck() : m_numCards(52), m_cards(nullptr)//default ctor that makes one deck
{
	CardRank ranks[13] = { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };//array of all possible ranks
	CardSuit suits[4] = { CLUBS, HEARTS, SPADES, DIAMONDS };//array of all suits
	m_cards = new Card[52];//pointer to array of cards
	int cardNum = 0;//which card number we're working with
	for (int i = 0; i < 1; i++) { //for each deck
		for (int j = 0; j < 13; j++) { //for each rank
			for (int k = 0; k < 4; k++) { //for each suit
				m_cards[cardNum].setRank(ranks[j]);
				m_cards[cardNum].setSuit(suits[k]);
				cardNum++;
			}
		}
	}
}

Deck::Deck(int numDecks) : m_numCards(52*numDecks), m_cards(nullptr)//makes numDecks of decks
{
	if (numDecks != 0)
	{
		CardRank ranks[13] = { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };//array of all possible ranks
		CardSuit suits[4] = { CLUBS, HEARTS, SPADES, DIAMONDS };//array of all suits
		m_cards = new Card[(52 * numDecks)];//pointer to array of cards
		int cardNum = 0;//which card number we're working with
		for (int i = 0; i < numDecks; i++) { //for each deck
			for (int j = 0; j < 13; j++) { //for each rank
				for (int k = 0; k < 4; k++) { //for each suit
					m_cards[cardNum].setRank(ranks[j]);
					m_cards[cardNum].setSuit(suits[k]);
					cardNum++;
				}
			}
		}
	}
}

Deck::Deck(const Deck & copy) : m_numCards(copy.m_numCards), m_cards(nullptr)//copy ctor
{ 
	if (m_numCards != 0)
	{
		m_cards = new Card[m_numCards];//pointer to array of cards
		for (int i = 0; i < m_numCards; i++)
		{
			m_cards[i].setRank(copy.m_cards[i].getRank());
			m_cards[i].setSuit(copy.m_cards[i].getSuit());
		}
	}
}

Deck & Deck::operator=(const Deck & rhs)//overloaded assignment operator
{
	if (this != &rhs)
	{
		delete[] m_cards;
		m_numCards = rhs.m_numCards;
		m_cards = nullptr;
		if (m_numCards != 0)
		{
			m_cards = new Card[m_numCards];//pointer to array of cards
			for (int i = 0; i < m_numCards; i++)
			{
				m_cards[i].setRank(rhs.m_cards[i].getRank());
				m_cards[i].setSuit(rhs.m_cards[i].getSuit());
			}
		}
	}
	return *this;
}

Card Deck::draw()//copies a card and returns it, off the top of the deck
{
	Card retVal = m_cards[0];//the card to be returned
	Card * temp = new Card[m_numCards - 1];
	for (int i = 1; i < m_numCards; i++)//cards will often be drawn, so a dynamic array is VERY inefficent :(
	{
		temp[i - 1] = m_cards[i];
	}
	delete[] m_cards;
	m_cards = temp;
	m_numCards--;
	return retVal;
}

Card * Deck::getCards() const//getter for m_cards
{
	return m_cards;
}

int Deck::getNumCards() const//getter for m_numCards
{
	return m_numCards;
}

void Deck::addCards(Card * toAdd, int numOfCards)//add some cards to the deck
{
	Card * temp = new Card[m_numCards + numOfCards];
	for (int i = 0; i < m_numCards; i++)//cards will often be drawn, so a dynamic array is VERY inefficent :(
	{
		temp[i] = m_cards[i];
	}
	for (int i = m_numCards; i < numOfCards; i++) 
	{
		temp[i] = toAdd[i - m_numCards];
	}
	delete[] m_cards;
	m_cards = temp;
	m_numCards += numOfCards;
}

void Deck::shuffle(int seed)//mix the deck up lots
{
	if (seed == -1)
		srand(clock());
	else 
		srand(seed);
	Card temp;//temp place to store a card
	int rando = 0;
	for (int j = 0; j < 5; j++) {
		if (seed == 0)
			srand(clock());
		else 
			srand(seed);
		for (int i = 0; i < m_numCards; i++) {//move random cards around enough to give each card at least 5 chances to move
			rando = rand() % m_numCards;
			temp.setRank(m_cards[rando].getRank());
			temp.setSuit(m_cards[rando].getSuit());
			m_cards[rando].setRank(m_cards[i].getRank());
			m_cards[rando].setSuit(m_cards[i].getSuit());
			m_cards[i].setRank(temp.getRank());
			m_cards[i].setSuit(temp.getSuit());
		}
	}
}

void Deck::resetDeck()//resets the deck back to a single, ordered deck
{
	delete[] m_cards;
	CardRank ranks[13] = { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };//array of all possible ranks
	CardSuit suits[4] = { CLUBS, HEARTS, SPADES, DIAMONDS };//array of all suits
	m_cards = new Card[52];//pointer to array of cards
	m_numCards = 52;
	int cardNum = 0;//which card number we're working with
	for (int i = 0; i < 1; i++) { //for each deck
		for (int j = 0; j < 13; j++) { //for each rank
			for (int k = 0; k < 4; k++) { //for each suit
				m_cards[cardNum].setRank(ranks[j]);
				m_cards[cardNum].setSuit(suits[k]);
				cardNum++;
			}
		}
	}
}

void Deck::resetDeck(int numDecks)//resets the deck back to an ordered number of specified deck
{
	if (numDecks != 0)
	{
		CardRank ranks[13] = { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };//array of all possible ranks
		CardSuit suits[4] = { CLUBS, HEARTS, SPADES, DIAMONDS };//array of all suits
		delete[] m_cards;
		m_cards = new Card[52 * numDecks];//pointer to array of cards
		m_numCards = 52 * numDecks;
		int cardNum = 0;//which card number we're working with
		for (int i = 0; i < numDecks; i++) { //for each deck
			for (int j = 0; j < 13; j++) { //for each rank
				for (int k = 0; k < 4; k++) { //for each suit
					m_cards[cardNum].setRank(ranks[j]);
					m_cards[cardNum].setSuit(suits[k]);
					cardNum++;
				}
			}
		}
	}
}

Deck::~Deck()//dtor to free memory for m_cards
{
	delete[] m_cards;
}
