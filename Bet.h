#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Player.h"
typedef enum {
    GREEN,
    RED,
    BLACK,
    ODD,
    EVEN,
    FIRST, //numbers 1-12
    SECOND, //numbers 13-24
    THIRD //numbers 25-36
} Outcome;

typedef struct
{
    int amount;
    Player* player;
    Outcome outcome;
}Bet;

int      initBet(Bet* pBet, Player* player);
void     chooseOutcome(Bet* pBet);
int      checkValidBet(const Bet* pBet, int amount);
void     closeBet(Bet* pBet, int multiply);