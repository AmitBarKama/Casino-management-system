#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include "Casino.h"
#include "Player.h"
#include "Roulette.h"
#include "Blackjack.h"
#include "LuckyWheel.h" 

#define TXT_FILE_NAME "Casino.txt"
#define BIN_FILE_NAME "Casino.bin"

int MainMenu(Casino* the_casino);
int LoginMenu(Casino* the_casino, Player** the_player);
int AdminMenu(Casino* the_casino, Player* the_player);
int PlayerMenu(Casino* the_casino, Player* the_player);

Blackjack blackjack;
RouletteGame roulette;
LuckyWheelGame luckyWheel;

int main()
{
    Casino the_casino;
    Player* the_player = NULL;
    srand((unsigned int)time(NULL));
    while (MainMenu(&the_casino)) {
        while (LoginMenu(&the_casino, &the_player))
        {
            if (the_player && strcmp(the_player->login.username, "ADMIN") == 0)
            {
                while (AdminMenu(&the_casino, the_player)) {}
            }
            else {
                while (the_player && PlayerMenu(&the_casino, the_player)) {}
            }
            if(!(writeCasinoToTextFile(&the_casino, TXT_FILE_NAME)&&writeCasinoToBinFile(&the_casino, BIN_FILE_NAME)))
                printf("Error!");
        }
    }
    freeCasino(&the_casino);
    free(the_player);
    printf("Bye bye (:\n");
    return 0;
}

int MainMenu(Casino* the_casino)
{
    int choice;
    printf("------------------------------------------\n");
    printf("Would you like to init the casino from text file or binary file\n");
    printf("1) Txt\n");
    printf("2) Binary\n");
    printf("-1) Exit\n");
    printf("------------------------------------------\n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        if (!readCasinoFromTextFile(the_casino, TXT_FILE_NAME))
            printf("Error reading text file");
        break;
    case 2:
        if(!readCasinoFromBinFile(the_casino, BIN_FILE_NAME))
            printf("Error reading binary file");
        break;
    case -1:
        return 0;
    }
    return 1;
}

int LoginMenu(Casino* the_casino, Player** the_player)
{
    char temp_user[MAX_STR_LEN];
    char temp_password[MAX_STR_LEN];
    int choice;
    while (1)
    {
        printf("------------------------------------------\n");
        printf("Please choose one of the following options\n1) Login\n2) Create new account\n-1) Go back\n");
        printf("------------------------------------------\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            getPlayerUserName(temp_user);
            *the_player = findPlayerByUsername(the_casino, temp_user);
            if (*the_player)
            {
                getPlayerPassword(temp_password);
                if (strcmp(((*the_player)->login).password, temp_password) == 0) {
                    printf("Login succeed!\n");
                    return 1;
                }
                else
                    printf("Wrong password\n");
            }
            else
                printf("Username not found\n");
            break;
        case 2:
            if (!addPlayer(the_casino))
                printf("Error!");
            *the_player = the_casino->playersArr[the_casino->numOfPlayers - 1];
            return 1;
            break;
        case -1:
            return 0;
        default:
            printf("Invalid choice\n");
            break;
        }
    }
}

int AdminMenu(Casino* the_casino, Player* the_player) {
    int choice;
    Player* pPlayer = NULL;
    printf("------------------------------------------\n");
    printf("Choose one of the following options:\n"
        "1) Print Casino\n"
        "2) Add Player\n"
        "3) Sort casino\n"
        "4) Find Player\n"
        "5) Play Blackjack \n"
        "6) Play Roulette\n"
        "7) Play Lucky Wheel (spin cost %d)\n"
        "8) Take Loan \n"
        "9) Pay Loan \n"
        "10) Print Player\n"
        "-1) Go back\n", ENTRY_AMOUNT_LUCKY_WHEEL);
    printf("------------------------------------------\n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        printCasino(the_casino);
        break;
    case 2:
        if (!addPlayer(the_casino))
            printf("Error!");
        break;
    case 3:
        sortCasino(the_casino);
        break;
    case 4:
        findPlayer(the_casino);
        break;
    case 5:
        startGameBj(&blackjack, the_player);
        break;
    case 6:
        playRouletteGame(&roulette, the_player);
        break;
    case 7:
        playLuckyWheelGame(&luckyWheel, the_player);
        break;
    case 8:
        takeLoan(the_player);
        break;
    case 9:
        payLoan(the_player);
        break;
    case 10:
        printPlayer(the_player);
        break;
    case -1:
        return 0;
    default:
        printf("Invalid choice\n");
        break;
    }
    return 1;
}

int PlayerMenu(Casino* the_casino, Player* the_player)
{
    int choice;
    printf("------------------------------------------\n");
    printf("Choose one of the following options:\n"
        "1) Play Blackjack \n"
        "2) Play Roulette\n"
        "3) Play Lucky Wheel (spin cost %d)\n"
        "4) Take Loan \n"
        "5) Pay Loan \n"
        "6) Print Player\n"
        "-1) Go back\n", ENTRY_AMOUNT_LUCKY_WHEEL);
    printf("------------------------------------------\n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        startGameBj(&blackjack, the_player);
        break;
    case 2:
        playRouletteGame(&roulette, the_player);
        break;
    case 3:
        playLuckyWheelGame(&luckyWheel, the_player);
        break;
    case 4:
        takeLoan(the_player);
        break;
    case 5:
        payLoan(the_player);
        break;
    case 6:
        printPlayer(the_player);
        break;
    case -1:
        return 0;
    default:
        printf("invalid choice\n");
        break;
    }
    return 1;
}
