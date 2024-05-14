#include "LuckyWheel.h"


void initializeLuckyWheelGame(LuckyWheelGame* game) {
    game->outcomes[0] = "You won 75$";
    game->outcomes[1] = "You won 50$";
    game->outcomes[2] = "You won 5$";
    game->outcomes[3] = "Better luck next time";
    game->outcomes[4] = "You won 200$";
    game->outcomes[5] = "You won 10$";
}

void playLuckyWheelGame(LuckyWheelGame* game, Player* player)
{
    game->player = player;
    if (game->player->money < ENTRY_AMOUNT_LUCKY_WHEEL)
    {
        printf("Sorry, you don't have enough balance to play the game\n");
        return;
    }
    else {
        player->money = (player->money) - ENTRY_AMOUNT_LUCKY_WHEEL;
        player->totalWager = player->totalWager + ENTRY_AMOUNT_LUCKY_WHEEL;
        initializeLuckyWheelGame(game);
        printf("Let's play the Lucky Wheel game!\n");
        int spinResult = spinLuckyWheel(game);
        switch (spinResult) {
        case 0:
            player->money = player->money + 75;
            break;
        case 1:
            player->money = player->money + 50;
            break;
        case 2:
            player->money = player->money + 5;
            break;
        case 3:
            player->money = player->money + 0;
            break;
        case 4:
            player->money = player->money + 200;
            break;
        case 5:
            player->money = player->money + 10;
            break;
        }
    }
}

int spinLuckyWheel(LuckyWheelGame* game) {
    int spinResult = rand() % NUMBER_OF_SECTORS;
    printf("Spinning the wheel...\n");
    char* outcome = game->outcomes[spinResult];
    printf("%s\n", outcome);
    return spinResult;
}

