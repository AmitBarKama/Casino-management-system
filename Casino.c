#include "Casino.h"
#include <stdio.h>
#include <stdlib.h>

int writeCasinoToTextFile(const Casino* casino, const char* fileName) {
    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Cannot open file\n");
        return -1;
    }
    int nameLength = (int)strlen(casino->name);
    fprintf(file, "%d\n%s\n", nameLength, casino->name);
    fprintf(file, "%d\n", casino->numOfPlayers);
    fprintf(file, "%d\n", casino->sortType);
    for (int i = 0; i < casino->numOfPlayers; ++i)
    {
        writePlayerToTextFile(file, casino->playersArr[i]);
    }
    fclose(file);
    return 1;
}

int readCasinoFromTextFile(Casino* casino, const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Cannot open file\n");
        return -1;
    }
    int nameLength;
    if (fscanf(file, "%d\n", &nameLength) != 1)
        return 0;
    casino->name = (char*)malloc((nameLength + 1) * sizeof(char));  // +1 for '\0' character
    if (!casino->name)
        return 0;
    fgets(casino->name, nameLength + 1, file);
    if (fscanf(file, "%d\n", &casino->numOfPlayers) != 1)
        return 0;
    if (fscanf(file, "%d\n", &casino->sortType) != 1)
        return 0;
    casino->playersArr = (Player**)malloc(casino->numOfPlayers * sizeof(Player*));
    if (casino->playersArr == NULL)
    {
        printf("Memory not allocated.\n");
        return -1;
    }
    for (int i = 0; i < casino->numOfPlayers; ++i) {
        casino->playersArr[i] = (Player*)malloc(sizeof(Player));
        if (!casino->playersArr[i])
        {
            printf("Memory not allocated.\n");
            return -1;
        }
        readPlayerFromTextFile(file, casino->playersArr[i]);
    }
    fclose(file);
    return 1;
}

int initCasino(Casino* casino)
{
    casino->sortType = eNotSorted;
    casino->name = getStrExactName("Enter Casino name");
    casino->playersArr = NULL;
    casino->numOfPlayers = 0;
    return 1;
}

int addPlayer(Casino* casino)
{
    Player* pPlayer = (Player*)calloc(1, sizeof(Player));
    if (!pPlayer)
        return 0;
    if (!initPlayer(casino, pPlayer))
    {
        free(pPlayer);
        return 0;
    }
    casino->playersArr = (Player**)realloc(casino->playersArr,
        (casino->numOfPlayers + 1) * sizeof(Player*));
    if (!casino->playersArr)
    {
        free(pPlayer);
        return 0;
    }
    casino->playersArr[casino->numOfPlayers] = pPlayer;
    casino->numOfPlayers++;
    return 1;
}

int initPlayer(Casino* casino, Player* pPlayer)
{
    while (1)
    {
        getPlayerUserName(pPlayer->login.username);
        if (checkUniqueUsername(casino, pPlayer->login.username))
            break;
        printf("The username is already exist, try a diffrent username\n");
    }
    return initPlayerNoUserName(pPlayer);
}

void findPlayer(const Casino* casino)
{
    int(*compare)(const void* player1, const void* player2) = NULL;
    Player temp = { 0 };
    Player* pTemp = &temp;

    switch (casino->sortType)
    {
    case eByUsername:
        printf("Enter Username:\n");
        getPlayerUserName(temp.login.username);
        compare = comparePlayerByUserName;
        break;

    case eByMoney:
        printf("Enter money amount:\n");
        scanf("%d", &temp.money);
        compare = comparePlayerByMoney;
        break;

    case eByWager:
        printf("Enter total wagered:\n");
        scanf("%d", &temp.totalWager);
        compare = comparePlayerByWager;
        break;
    }

    if (compare != NULL)
    {
        Player** pPlayer = bsearch(&pTemp, casino->playersArr, casino->numOfPlayers, sizeof(Player*), compare);
        if (pPlayer == NULL)
            printf("Player was not found\n");
        else {
            printf("Player found:\n");
            printPlayer(*pPlayer);
        }
    }
    else {
        printf("The search cannot be performed, array not sorted\n");
    }
}

eSortType getSortType()
{
    int option;
    printf("\n\n");
    do {
        printf("Base on what field do you want to sort?\n");
        for (int i = 1; i < eNofSortTypes; i++)
            printf("%d) According to %s\n", i, sortTypeStr[i]);
        scanf("%d", &option);
    } while (option < 0 || option >= eNofSortTypes);
    getchar();
    return (eSortType)(option);
}

const char* getSortTypeStr(int type)
{
    if (type < 0 || type >= eNofSortTypes)
        return NULL;
    return sortTypeStr[type];
}

void sortCasino(Casino* casino)
{
    casino->sortType = getSortType();
    switch (casino->sortType)
    {
    case eByUsername:
        qsort(casino->playersArr, casino->numOfPlayers, sizeof(Player*),
            comparePlayerByUserName);
        break;
    case eByMoney:
        qsort(casino->playersArr, casino->numOfPlayers, sizeof(Player*),
            comparePlayerByMoney);
        break;
    case eByWager:
        qsort(casino->playersArr, casino->numOfPlayers, sizeof(Player*),
            comparePlayerByWager);
        break;
    }
}

int checkUniqueUsername(const Casino* casino, const char* userName)
{
    Player* player = findPlayerByUsername(casino, userName);
    if (player != NULL)//The username already exist
        return 0;
    return 1;
}

Player* findPlayerByUsername(const Casino* casino, const char* username)
{
    for (int i = 0; i < casino->numOfPlayers; i++)
    {
        if (isPlayerUser(username, casino->playersArr[i]) == 0)
            return casino->playersArr[i];
    }
    return NULL;
}

void printCasino(const Casino* casino)
{
    printf("Welcome to %s!\n", casino->name);
    printf("In %s there are %d players\n", casino->name, casino->numOfPlayers);
    generalArrayFunction(casino->playersArr, casino->numOfPlayers, sizeof(Player*), printPlayerPTR);
}

void freeCasino(Casino* casino)
{
    generalArrayFunction(casino->playersArr, casino->numOfPlayers, sizeof(Player*), freePlayerPtr);
    free(casino->playersArr);
    free(casino->name);
}

int writeCasinoToBinFile(const Casino* casino, const char* fileName) {
    FILE* file = fopen(fileName, "wb");
    if (file == NULL) {
        printf("Cannot open file\n");
        return -1;
    }
    int nameLength = (int)strlen(casino->name);
    fwrite(&nameLength, sizeof(int), 1, file);
    fwrite(casino->name, sizeof(char), nameLength, file);
    fwrite(&casino->numOfPlayers, sizeof(int), 1, file);
    fwrite(&casino->sortType, sizeof(int), 1, file);
    for (int i = 0; i < casino->numOfPlayers; ++i) {
        writePlayerToBinFile(file, casino->playersArr[i]);
    }
    fclose(file);
    return 1;
}

int readCasinoFromBinFile(Casino* casino, const char* fileName) {
    FILE* file = fopen(fileName, "rb");
    if (file == NULL) {
        printf("Cannot open file\n");
        return -1;
    }
    int nameLength;
    if (fread(&nameLength, sizeof(int), 1, file) != 1)
        return 0;
    casino->name = (char*)malloc((nameLength + 1) * sizeof(char));
    if (!casino->name)
    {
        printf("Memory not allocated.\n");
        return 0;
    }
    fread(casino->name, sizeof(char), nameLength, file);
    casino->name[nameLength] = '\0';
    if (fread(&casino->numOfPlayers, sizeof(int), 1, file) != 1)
        return 0;
    if (fread(&casino->sortType, sizeof(int), 1, file) != 1)
        return 0;
    casino->playersArr = malloc(casino->numOfPlayers * sizeof(Player*));
    if (!casino->playersArr)
    {
        printf("Memory not allocated.\n");
        return 0;
    }
    for (int i = 0; i < casino->numOfPlayers; ++i) {
        casino->playersArr[i] = malloc(sizeof(Player));
        readPlayerFromBinFile(file, casino->playersArr[i]);
    }
    fclose(file);
    return 1;
}