#pragma once
#include <stdio.h>
#include <stdlib.h>

//♥♠♦♣
typedef enum {
	eHearts, eDiamonds, eClubs, eSpades, eNofSuitCards
} eSuitCard;

static const char* suitCardStr[eNofSuitCards]
= { "H", "S", "C", "D" };

typedef enum {
	eAce, eTwo, eThree, eFour, eFive, eSix, eSeven, eEight, eNine, eTen, eJack, eQueen, eKing, eNofRanks
} eRank;

static const char* rank[eNofRanks]
= { "Ace", "2", "3", "4","5" ,"6", "7", "8", "9","10","J","Q","K" };

typedef struct
{
	int			value; //can be 1-13
	eSuitCard	suitCard;
}Card;

void			initCard(Card* card, eSuitCard suit, int value);
const char*		GetSuitCardStr(int suit);
void			printCard(const Card* pCard);
void			printCardV(const void* val);