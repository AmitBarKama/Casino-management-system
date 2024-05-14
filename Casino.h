#pragma once
#include "Player.h"

typedef enum {
    eNotSorted, eByMoney, eByWager, eByUsername, eNofSortTypes
} eSortType;

static const char* sortTypeStr[eNofSortTypes]
= { "Not sorted", "Money", "Total wagered", "Username" };

typedef struct
{
    Player** playersArr;
    int numOfPlayers;
    char* name;
    eSortType  sortType;
}Casino;

int             initCasino(Casino* casino);
int             writeCasinoToTextFile(const Casino* casino, const char* fileName);
int             readCasinoFromTextFile(Casino* casino, const char* fileName);
int             writeCasinoToBinFile(const Casino* casino, const char* fileName);
int             readCasinoFromBinFile(Casino* casino, const char* fileName);
int             addPlayer(Casino* casino);
int             initPlayer(Casino* casino, Player* player);
int             checkUniqueUsername(const Casino* casino, const char* id);
void            findPlayer(const Casino* casino);
Player*         findPlayerByUsername(const Casino* casino, const char* id);
void            sortCasino(Casino* casino);
eSortType	    getSortType();
const char*     getSortTypeStr(int type);
void            printCasino(const Casino* casino);
void            freeCasino(Casino* casino);
