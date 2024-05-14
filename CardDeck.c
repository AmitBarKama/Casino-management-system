#include "CardDeck.h"

void initCardDeck(CardDeck* pCardDeck)
{
	int index = 0;
	for (int i = 0; i < eNofSuitCards; i++)
	{
		for (int j = 1; j <= 13; j++)
		{
			initCard(&(pCardDeck->theCardDeck[index]), i, j);
			index++;
		}
	}
	pCardDeck->topCard = NUMBER_OF_CARDS - 1;
}

void shuffleDeck(CardDeck* pCardDeck, int numOfCards)
{
	//srand((unsigned int)time(NULL));
	for (int i = 0; i < numOfCards; i++) {
		int j = rand() % NUMBER_OF_CARDS;
		swapCards(pCardDeck, i, j);  // Swap arr[i] with arr[j]
	}
}

void swapCards(CardDeck* theDeck, int i, int j)
{
	Card temp = theDeck->theCardDeck[i];
	theDeck->theCardDeck[i] = theDeck->theCardDeck[j];
	theDeck->theCardDeck[j] = temp;
}

Card dealCard(CardDeck* theDeck)
{
	Card theCard = theDeck->theCardDeck[theDeck->topCard];
	theDeck->topCard--;
	return theCard;
}

void printCardDeck(const CardDeck* pCardDeck)
{
	for (int i = 0; i < NUMBER_OF_CARDS; i++)
	{
		printf("Card %d:", i + 1);
		printCard(&(pCardDeck->theCardDeck[i]));
	}
}