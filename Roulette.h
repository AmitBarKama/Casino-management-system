#pragma once
#include "Player.h"
#include "Bet.h"

typedef struct {
    Player* player;
    Bet bet;
    Outcome outcomeColor;
    Outcome outcomeEvebOdd;
    Outcome outcome12;
} RouletteGame;

void     playRouletteGame(RouletteGame* game, Player* player);
void     spinRouletteWheel(RouletteGame* game);
void     processBet(RouletteGame* game);
char*    outcomeString(Outcome outcome);


