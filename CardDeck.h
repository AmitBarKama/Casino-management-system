#pragma once
#include "Card.h"

#define NUMBER_OF_CARDS 52
typedef struct
{
	Card	theCardDeck[NUMBER_OF_CARDS];
	int		topCard; //The last card in the deck
}CardDeck;

void	initCardDeck(CardDeck* pCardDeck);
void	shuffleDeck(CardDeck* pCardDeck, int numOfCards);
void	swapCards(CardDeck* theDeck, int i, int j);
Card	dealCard(CardDeck* theDeck);
void	printCardDeck(const CardDeck* pCardDeck);
