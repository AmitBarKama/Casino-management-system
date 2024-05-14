#define _CRT_SECURE_NO_WARNINGS
#include "Player.h"

int	initPlayerNoUserName(Player* pPlayer)
{
    initLoginNoUser(&pPlayer->login);
    pPlayer->name = getStrExactName("Enter your first name");
    if (!pPlayer->name)
        return 0;
    pPlayer->money = INITIAL_AMOUNT;
    pPlayer->totalWager = 0;
    if (!L_init(&pPlayer->loan))
        return 0;
    return 1;
}

int	writePlayerToTextFile(FILE* fp, const Player* pPlayer)
{
    if (!fp)
    {
        printf("Error open file to write\n");
        return 0;
    }
    int numOfLoans = getNumberOfLoan(pPlayer);
    int nameLength = (int)strlen(pPlayer->name);
    fprintf(fp, "%d\n", nameLength);
    fprintf(fp, "%s\n%d\n%d\n", pPlayer->name, pPlayer->money, pPlayer->totalWager);
    writeLoginToTextFile(fp, &pPlayer->login);
    fprintf(fp, "%d\n", numOfLoans);
    if (numOfLoans > 0)
    {
        NODE* pNode = pPlayer->loan.head.next;//first node
        Loan* pLoan;
        while (pNode != NULL)
        {
            pLoan = (Loan*)pNode->key;
            if (!writeLoanToTextFile(fp, pLoan))
            {
                printf("Error write loan\n");
                return 0;
            }
            pNode = pNode->next;
        }
    }
    return 1;
}

int	readPlayerFromTextFile(FILE* fp, Player* pPlayer)
{
    if (!fp)
        return 0;
    int nameLength;
    if (fscanf(fp, "%d\n", &nameLength) != 1)
        return 0;
    pPlayer->name = (char*)malloc((nameLength + 1) * sizeof(char));  // +1 for '\0' character
    if (!pPlayer->name)
        return 0;
    fgets(pPlayer->name, nameLength + 1, fp);
    if (fscanf(fp, "%d\n", &pPlayer->money) != 1)
        return 0;
    if (fscanf(fp, "%d\n", &pPlayer->totalWager) != 1)
        return 0;
    readLoginFromTextFile(fp, &pPlayer->login);
    L_init(&pPlayer->loan);
    readLoanListFromTextFile(fp, pPlayer);
    return 1;
}

int	writePlayerToBinFile(FILE* fp, const Player* pPlayer)
{
    if (!fp)
        return 0;
    int nameLen = (int)strlen(pPlayer->name) + 1;
    int numOfLoans = getNumberOfLoan(pPlayer); //number of loans
    if (fwrite(&nameLen, sizeof(int), 1, fp) != 1)
        return 0;
    if (fwrite(pPlayer->name, sizeof(char), nameLen, fp) != nameLen)
        return 0;
    if (fwrite(&pPlayer->money, sizeof(int), 1, fp) != 1)
        return 0;
    if (fwrite(&pPlayer->totalWager, sizeof(int), 1, fp) != 1)
        return 0;
    if (!writeLoginToBinFileCompressed(fp, &pPlayer->login))
        return 0;
    if (fwrite(&numOfLoans, sizeof(int), 1, fp) != 1)
        return 0;
    if (numOfLoans > 0) {
        NODE* pNode = pPlayer->loan.head.next;
        for (int i = 0; i < numOfLoans; i++) {
            if (!writeLoanToBinFileCompressed(fp, pNode->key))
                return 0;
            pNode = pNode->next;
        }
    }
    return 1;
}

int	readPlayerFromBinFile(FILE* fp, Player* pPlayer)
{
    if (!fp)
        return 0;
    int nameLen;
    if (fread(&nameLen, sizeof(int), 1, fp) != 1)
        return 0;
    pPlayer->name = (char*)malloc(nameLen * sizeof(char));
    if (!pPlayer->name)
        return 0;
    if (fread(pPlayer->name, sizeof(char), nameLen, fp) != nameLen)
    {
        free(pPlayer->name);
        return 0;
    }
    if (fread(&(pPlayer->money), sizeof(int), 1, fp) != 1)
        return 0;
    if (fread(&(pPlayer->totalWager), sizeof(int), 1, fp) != 1)
        return 0;
    if (!readLoginFromBinFileCompressed(fp, &pPlayer->login))
        return 0;
    L_init(&pPlayer->loan);
    readLoansListFromBinFile(fp, pPlayer);
    return 1;
}

int	readLoanListFromTextFile(FILE* fp, Player* pPlayer)
{
    if (!fp)
        return 0;
    int numOfLoans = 0;
    if (fscanf(fp, "%d\n", &numOfLoans) != 1)
        return 0;
    for (int i = 0; i < numOfLoans; i++) {
        Loan* theLoan = (Loan*)malloc(sizeof(Loan));
        if (theLoan == NULL || readLoanFromTextFile(fp, theLoan) == 0) {
            free(theLoan);
            fclose(fp);
            return 0;
        }
        L_insert(&(pPlayer->loan).head, theLoan);
    }
    return 1;
}

int readLoansListFromBinFile(FILE* fp, Player* pPlayer)
{
    if (!fp)
        return 0;
    int numOfLoans;
    if (fread(&numOfLoans, sizeof(int), 1, fp) != 1)
        return 0;
    for (int i = 0; i < numOfLoans; i++) {
        Loan* theLoan = (Loan*)malloc(sizeof(Loan));
        if (theLoan == NULL || readLoanFromBinFileCompressed(fp, theLoan) == 0) {
            free(theLoan);
            return 0;
        }
        L_insert(&(pPlayer->loan).head, theLoan);
    }
    return 1;
}

int getNumberOfLoan(const Player* pPlayer)
{
    int count = 0;
    NODE* pN = pPlayer->loan.head.next; //first Node
    while (pN != NULL)
    {
        count++;
        pN = pN->next;
    }
    return count;
}

void addMoney(Player* pPlayer, int money)
{
    pPlayer->money = pPlayer->money + money;
}

void subMoney(Player* pPlayer, int money)
{
    pPlayer->money = pPlayer->money - money;
}

int takeLoan(Player* pPlayer)
{
    int numOfLoans = getNumberOfLoan(pPlayer);//number of loans 
    if (numOfLoans == MAX_POSSIBLE_LOANS)
    {
        printf("Sorry, you have reached the maximum amount of loans (%d)\n", MAX_POSSIBLE_LOANS);
        return 0;
    }
    Loan* pNewLoan = (Loan*)malloc(sizeof(Loan)); 
    if (!pNewLoan)
        return 0;
    NODE* pNode = &pPlayer->loan.head;//pNode = head
    initLoan(pNewLoan);
    while (pNode->next != NULL)
    {
        pNode = pNode->next;
    }
    L_insert(pNode, pNewLoan);//Insert the new loan to the end of the list
    addMoney(pPlayer, pNewLoan->amountToGive);
    return 1;
}

// this function return:
//  0 - if player regret or has no loans
//  1 - if the player pay the loans and the loan deleted from the list
//  -1 - if the player doesn't have enough money to pay
int payLoan(Player* pPlayer)
{
    char input;
    Loan* theLoan = NULL;
    NODE* pNode = pPlayer->loan.head.next;//the first loan of the player
    if (!pNode)//if the player has no loans to pay
    {
        printf("You don't have any loans to pay \n");
        free(pNode);
        return 0;
    }
    theLoan = pNode->key;
    if (pPlayer->money < theLoan->amountToReturn)//if the player doesn't have enough money to pay
    {
        printf("Error, you dont have enough balance \n");
        return -1;
    }
    printf("The loan amount you have to repay is: %d$\n", theLoan->amountToReturn);
    do {
        printf("Would you like to pay this loan? (Y/N)\n");
        getchar();
        scanf("%c", &input);
    } while (!isValidInput(input));

    if (input == 'y' || input == 'Y')
    {
        subMoney(pPlayer, theLoan->amountToReturn);
        if (L_delete(&pPlayer->loan.head, free))
        {
            printf("The loan was succesfully paid\n");
            return 1;
        }
    }
    else //if player regret
        return 0;
    return 1;
}

int isValidInput(char choose)
{
    if (choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N')
    {
        printf("Error, Invalid input!\n");
        return 0;
    }
    return 1;
}

int comparePlayerByUserName(const void* v1, const void* v2)
{
    Player* pPlayer1 = *(Player**)v1;
    Player* pPlayer2 = *(Player**)v2;
    return strcmp(((&pPlayer1->login)->username), ((&pPlayer2->login)->username));
}

int comparePlayerByMoney(const void* v1, const void* v2)
{
    Player* pPlayer1 = *(Player**)v1;
    Player* pPlayer2 = *(Player**)v2;
    return pPlayer1->money - pPlayer2->money;
}

int comparePlayerByWager(const void* v1, const void* v2)
{
    Player* pPlayer1 = *(Player**)v1;
    Player* pPlayer2 = *(Player**)v2;
    return pPlayer1->totalWager - pPlayer2->totalWager;
}

int isPlayerUser(const void* v1, const void* v2)
{
    char* userName = (char*)v1;
    Player* pPlayer = (Player*)v2;
    Login* login = &pPlayer->login;
    return strcmp(userName, login->username);
}

int isPlayerUserName(const void* v1, const void* v2)
{
    char* userName = (char*)v1;
    Player** pPlayer = (Player**)v2;
    return strcmp(userName, (*pPlayer)->login.username);
}

int isPlayerMoney(const void* v1, const void* v2)
{
    int* money = (int*)v1;
    Player** pPlayer = (Player**)v2;
    return ((*pPlayer)->money - *money);
}

int isPlayerWager(const void* v1, const void* v2)
{
    int* wager = (int*)v1;
    Player** pPlayer = (Player**)v2;
    return ((*pPlayer)->totalWager - *wager);
}

void printPlayerPTR(void* pPlayerPtr)
{
    const Player* temp = *(Player**)pPlayerPtr;
    printPlayer(temp);
}

void printPlayer(const Player* player)
{
    printf("____________________________________________\n");
    printf("Player %s has %d$ and total wagered: %d$\n", player->name, player->money, player->totalWager);
    printf("%s has %d Loans\n", player->name, getNumberOfLoan(player));
    L_print(&(player->loan), printLoan);
}

void freePlayerPtr(void* pPlayerPtr)
{
    Player* temp = *(Player**)pPlayerPtr;
    freePlayer(temp);
}

void freePlayer(Player* pPlayer)
{
    free(pPlayer->name);
    L_free(&pPlayer->loan, free);
}

