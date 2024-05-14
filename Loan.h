#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Player.h"
#include "Def.h"
#define INTEREST 1.15
#define MAX_LOAN 1000

typedef struct
{
	int amountToGive;
	int amountToReturn;
}Loan;

void	initLoan(Loan* pLoan);
int		writeLoanToTextFile(FILE* fp, const Loan* pLoan);
int		readLoanFromTextFile(FILE* fp, Loan* pLoan);
int		writeLoanToBinFileCompressed(FILE* fp, const Loan* pLoan);
int		readLoanFromBinFileCompressed(FILE* fp, Loan* pLoan);
int		isOkAmountOfLoan(int theAmountOfLoan);
void	printLoan(const void* l);





