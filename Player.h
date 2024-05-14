#pragma once
#include "Loan.h"
#include "Login.h"
#include "List.h"
#include "GeneralFunctions.h"
#define INITIAL_AMOUNT 100
#define MAX_POSSIBLE_LOANS 5
typedef struct
{
	char* name;
	int money;
	int totalWager;
	Login login;
	LIST loan;
}Player;


int		initPlayerNoUserName(Player* pPlayer);
int		readPlayerFromTextFile(FILE* fp, Player* pPlayer);
int		readLoanListFromTextFile(FILE* fp, Player* pPlayer);
int		writePlayerToTextFile(FILE* fp, const Player* pPlayer);
int		writePlayerToBinFile(FILE* fp, const Player* pPlayer);
int		readPlayerFromBinFile(FILE* fp, Player* pPlayer);
int		readLoansListFromBinFile(FILE* fp, Player* pPlayer);
int		getNumberOfLoan(const Player* pPlayer);
void	addMoney(Player* player, int money);
void	subMoney(Player* player, int money);
int		takeLoan(Player* pPlayer);
int		payLoan(Player* pPlayer);
int		isValidInput(char choose);
int		comparePlayerByUserName(const void* v1, const void* v2);
int		comparePlayerByMoney(const void* v1, const void* v2);
int		comparePlayerByWager(const void* v1, const void* v2);
int		isPlayerUserName(const void* v1, const void* v2);
int		isPlayerUser(const void* v1, const void* v2);
int		isPlayerMoney(const void* v1, const void* v2);
int		isPlayerWager(const void* v1, const void* v2);
void    printPlayer(const Player* player);
void	printPlayerPTR(void* pPlayerPtr);
void	freePlayerPtr(void* pPlayerPtr);
void	freePlayer(Player* p);




