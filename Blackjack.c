#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include "Blackjack.h"

void startGameBj(Blackjack* game, Player* the_player)
{
    bool playerContinuesToHit;
    char ch;
    int result;
    Bet the_bet;
    CardDeck game_deck;
    initCardDeck(&game_deck);
    shuffleDeck(&game_deck, NUMBER_OF_CARDS);
    do {
    } while (!initBet(&the_bet, the_player));
    game->player = the_player;
    game->deck = game_deck;
    game->bet = the_bet;
    game->playerCardCount = 0;
    game->dealerCardCount = 0;
    game->dealerHand = malloc(2 * sizeof(Card));
    game->playerHand = malloc(2 * sizeof(Card));
    //Deal the first two cards for the dealer
    if (!dealerHit(game))
    {
        closeBet(&game->bet, 1);
        return;
    }
    if (!dealerHit(game))
    {
        closeBet(&game->bet, 1);
        return;
    }
    //Print dealer's one card
    printf("------------------\n");
    printf("Dealer's one card:\n");
    generalArrayFunction(game->dealerHand, 1, sizeof(Card), printCardV);
    //Deal 2 card to the player
    if (!playerHit(game))
    {
        closeBet(&game->bet, 1);
        return;
    }
    if (!playerHit(game))
    {
        closeBet(&game->bet, 1);
        return;
    }
    // Print player's cards
    printf("Player's cards:\n");
    generalArrayFunction(game->playerHand, 2, sizeof(Card), printCardV);
    do {
        printf("Value: %d\n", playerTotal(game));
        printf("Would you like to [H] or [S]?\n");
        scanf(" %c", &ch);
        getchar();
        switch (ch)
        {
        case 'H':
        case 'h':
            if (!playerHit(game))
            {
                closeBet(&game->bet, 1);
                return;
            }
            if (game->playerHand)
                printCard(&game->playerHand[game->playerCardCount - 1]);
            playerContinuesToHit = true;
            break;
        case 'S':
        case 's':
            playerContinuesToHit = false;
            break;
        default:
            printf("Invalid input!\n");
            playerContinuesToHit = true;
            break;
        }
    } while (playerContinuesToHit && UNDER_21(playerTotal(game)));
    printf("Player finished hitting.\nFinal Value: %d\nDealers cards:\n", playerTotal(game));
    generalArrayFunction(game->dealerHand, 2, sizeof(Card), printCardV);
    while (DEALER_HIT(dealerTotal(game)) && UNDER_21(playerTotal(game))) {
        if (!dealerHit(game))
        {
            closeBet(&game->bet, 1);
            return;
        }
        printf("Dealer hits...\n");
        printCard(&game->dealerHand[game->dealerCardCount - 1]);
        printf("Value: %d\n", dealerTotal(game));
    }
    printf("Dealer finished hitting.\nFinal Value: %d\n", dealerTotal(game));
    result = calculateResult(game);
    switch (result)
    {
    case 1:
        printf("You won!\n");
        closeBet(&game->bet, 2);
        break;
    case 0:
        printf("it's a draw!\n");
        closeBet(&game->bet, 1);
        break;
    case -1:
        printf("You lost!\n");
        closeBet(&game->bet, 0);
        break;
    }
    free(game->dealerHand);
    free(game->playerHand);
}

int dealerTotal(Blackjack* game)
{
    return calculateHandTotal(game->dealerHand, game->dealerCardCount);
}

int playerTotal(Blackjack* game)
{
    return calculateHandTotal(game->playerHand, game->playerCardCount);
}

int calculateHandTotal(Card* hand, int card_count)
{
    int total = 0;
    int aceCount = 0;
    for (int i = 0; i < card_count; i++)
    {
        if (hand[i].value > 10) // For face cards
            total += 10;
        else if (hand[i].value == 1) { // For Ace
            total += 11;
            aceCount++;
        }
        else
            total += hand[i].value;
    }
    // If total is over 21 and we have Aces, reduce total value ("move" Ace value from 11 to 1)
    while (!UNDER_21(total) && aceCount > 0)
    {
        total -= 10;
        aceCount--;
    }
    return total;
}

int playerHit(Blackjack* game)
{
    game->playerCardCount++;
    game->playerHand = (Card*)realloc(game->playerHand, game->playerCardCount * sizeof(Card));

    if (game->playerHand == NULL)
    {
        printf("Failed to allocate memory. Exiting.\n");
        return 0;
    }
    game->playerHand[game->playerCardCount - 1] = dealCard(&game->deck);
    return 1;
}

int dealerHit(Blackjack* game)
{
    game->dealerCardCount++;
    game->dealerHand = (Card*)realloc(game->dealerHand, game->dealerCardCount * sizeof(Card));
    if (game->dealerHand == NULL)
    {
        printf("Failed to allocate memory. Exiting.\n");
        return 0;
    }
    game->dealerHand[game->dealerCardCount - 1] = dealCard(&game->deck);
    return 1;
}

int calculateResult(Blackjack* game)
{
    int playerRes = playerTotal(game); //Calculate player total
    int dealerRes = dealerTotal(game); //Calculate dealer total
    //Proceed with comparing playerTotal and dealerTotal
    if (!UNDER_21(playerRes - 1))//Player bust
        return -1;
    else if (!UNDER_21(dealerRes - 1))   //Dealer bust
        return 1;
    else if (IS_BIGGER(playerRes, dealerRes))  //Player has higher valid total
        return 1;
    else if (IS_BIGGER(dealerRes, playerRes))  //Dealer has higher valid total
        return -1;
    else //Tie
        return 0;
}