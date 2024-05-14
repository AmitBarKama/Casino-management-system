#include <stdio.h>
#include <stdlib.h>
#include "Roulette.h"
#include "Macros.h"

void playRouletteGame(RouletteGame* game, Player* player) {
    game->player = player;
    game->outcomeColor = RED; //default value
    game->outcome12 = FIRST;
    game->outcomeEvebOdd = EVEN;
    Bet the_bet;
    do {
    } while (!initBet(&the_bet, game->player));
    game->bet = the_bet;
    chooseOutcome(&game->bet);
    spinRouletteWheel(game);
    processBet(game);
}

void spinRouletteWheel(RouletteGame* game) {
    int random_num = rand() % 37; //Generate a random number between 0 and 36
    game->outcomeEvebOdd = IS_EVEN(random_num) ? EVEN : ODD;
    //Determine the outcome based on the random number
    if (IS_ZERO(random_num)) {
        game->outcomeColor = GREEN;
        game->outcomeEvebOdd = GREEN;
    }
    else if (IS_BETWEEN(random_num, 1, 10))
    {
        if (IS_EVEN(random_num))
            game->outcomeColor = BLACK;
        else
            game->outcomeColor = RED;
        game->outcome12 = FIRST;
    }
    else if (IS_BETWEEN(random_num, 11, 18))
    {
        if (IS_EVEN(random_num))
            game->outcomeColor = RED;
        else
            game->outcomeColor = BLACK;
        game->outcome12 = IS_BETWEEN(random_num, 11, 12) ? FIRST : SECOND;
    }
    else if (IS_BETWEEN(random_num, 19, 28))
    {
        if (IS_EVEN(random_num))
            game->outcomeColor = BLACK;
        else
            game->outcomeColor = RED;
        game->outcome12 = IS_BETWEEN(random_num, 19, 24) ? SECOND : THIRD;
    }
    else
    {
        if (IS_EVEN(random_num))
            game->outcomeColor = RED;
        else
            game->outcomeColor = BLACK;
        game->outcome12 = THIRD;
    }
    printf("------------------------------------------\n");
    printf("Ball landed on %d\nThe color result is %s\nThe even/odd result is %s\nThe numbers result is %s\n", random_num, outcomeString(game->outcomeColor), outcomeString(game->outcomeEvebOdd), outcomeString(game->outcome12));
}

void processBet(RouletteGame* game)
{
    printf("You chose %s \n", outcomeString(game->bet.outcome));
    if (game->bet.outcome == game->outcomeEvebOdd || game->bet.outcome == game->outcomeColor || game->bet.outcome == game->outcome12) {
        switch (game->bet.outcome) {
        case GREEN:
            closeBet(&(game->bet), 36);
            break;
        case RED:
        case BLACK:
        case ODD:
        case EVEN:
            closeBet(&(game->bet), 2);
            break;
        case FIRST:
        case SECOND:
        case THIRD:
            closeBet(&(game->bet), 3);
            break;
        }
        printf("Congratulations! You win!\nYour balance is %d$\n", game->player->money);
    }
    else
        printf("Sorry! You lose!\nYour current balance is %d$\n", game->player->money);
}

char* outcomeString(Outcome outcome)
{
    switch (outcome) {
    case GREEN:
        return "Green";
    case RED:
        return "Red";
    case BLACK:
        return "Black";
    case ODD:
        return "Odd";
    case EVEN:
        return "Even";
    case FIRST:
        return "First";
    case SECOND:
        return "Second";
    case THIRD:
        return "Third";
    default:
        return "Unknown";
    }
}

