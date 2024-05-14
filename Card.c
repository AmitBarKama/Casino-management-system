
#include "Card.h"


void initCard(Card* pCard, eSuitCard suit, int value)
{
	pCard->suitCard = suit;
	pCard->value = value;
}

const char* GetSuitCardStr(int suit)
{
	if (suit < 0 || suit >= eNofSuitCards)
		return NULL;
	return suitCardStr[suit];
}

void printCardV(const void* val)
{
	printCard((const Card*)val);
}

void printCard(const Card* pCard)
{
	printf("-----------\n");
	printf("|");
	printf("  %s [%s]  ", rank[pCard->value - 1], suitCardStr[pCard->suitCard]);
	printf("|\n");
	printf("-----------\n");
}