#pragma once
#include "Player.h"
#include "Bet.h"

#define NUMBER_OF_SECTORS 6
#define ENTRY_AMOUNT_LUCKY_WHEEL 65

typedef struct {
    Player* player;
    Bet bet;
    char* outcomes[NUMBER_OF_SECTORS];
} LuckyWheelGame;

void     initializeLuckyWheelGame(LuckyWheelGame* game);
void     playLuckyWheelGame(LuckyWheelGame* game, Player* player);
int      spinLuckyWheel(LuckyWheelGame* game);
