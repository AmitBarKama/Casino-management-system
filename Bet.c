#include "Bet.h"

int initBet(Bet* pBet, Player* the_player)
{
    int bet_temp = 0;
    pBet->player = the_player;
    printf("Choose your bet size:\n");
    scanf("%d", &bet_temp);
    if (bet_temp > 0) {
        if (checkValidBet(pBet, bet_temp)) {
            pBet->amount = bet_temp;
            the_player->money = (the_player->money - bet_temp);
            the_player->totalWager = the_player->totalWager + bet_temp;
            return 1;
        }
        else {
            printf("You dont have enough balance.\n");
            return 0;
        }
    }
    else {
        printf("Error! Enter a bet bigger than 0.\n");
        return 0;
    }
}

int checkValidBet(const Bet* pBet, int amount)
{
    if (pBet->player->money < amount)
        return 0;
    return 1;
}

void closeBet(Bet* pBet, int multiply)
{
    pBet->player->money = pBet->player->money + (pBet->amount * multiply);
}

void chooseOutcome(Bet* pBet)
{
    int choise = 0;
    do {
        printf("What do you want to gumble\n1) Green\n2) Red\n3) Black\n4) Even\n5) Odd\n6) First(numbers 1-12)\n7) Secound(numbers 13-24)\n8) Third(numbers 25-36)\n");
        scanf("%d", &choise);
    } while (choise > 8 || choise < 1);
    switch (choise)
    {
    case 1:
        pBet->outcome = GREEN;
        break;
    case 2:
        pBet->outcome = RED;
        break;
    case 3:
        pBet->outcome = BLACK;
        break;
    case 4:
        pBet->outcome = EVEN;
        break;
    case 5:
        pBet->outcome = ODD;
        break;
    case 6:
        pBet->outcome = FIRST;
        break;
    case 7:
        pBet->outcome = SECOND;
        break;
    case 8:
        pBet->outcome = THIRD;
        break;
    default:
        break;
    }
}

