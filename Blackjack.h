#pragma once
#include "Player.h"
#include "CardDeck.h"
#include "Bet.h"
#include "GeneralFunctions.h"
#include "Macros.h"

typedef struct
{
    Player* player;
    CardDeck deck;
    Card* playerHand;
    Card* dealerHand;
    int playerCardCount;
    int dealerCardCount;
    Bet bet;
}Blackjack;

void     startGameBj(Blackjack* game, Player* the_player);
int      dealerTotal(Blackjack* game);
int      playerTotal(Blackjack* game);
int      calculateHandTotal(Card* hand, int card_count);
int      calculateResult(Blackjack* game);
int      playerHit(Blackjack* game);
int      dealerHit(Blackjack* game);


