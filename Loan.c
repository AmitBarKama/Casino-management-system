#include "Loan.h"

void initLoan(Loan* pLoan)
{
	do {
		printf("Enter the loan amount you wish to take (the amount can be in increments of 100$ and not more than 1000$):");
		scanf("%d", &pLoan->amountToGive);
	} while (!isOkAmountOfLoan(pLoan->amountToGive));
	pLoan->amountToReturn = (int)(pLoan->amountToGive * INTEREST);
}

int	writeLoanToTextFile(FILE* fp, const Loan* pLoan)
{
	if (!fp)
		return 0;
	fprintf(fp, "%d\n%d\n", pLoan->amountToGive, pLoan->amountToReturn);
	return 1;
}

int readLoanFromTextFile(FILE* fp, Loan* pLoan)
{
	if (fscanf(fp, "%d\n", &pLoan->amountToGive) != 1)
		return 0;
	if (fscanf(fp, "%d\n", &pLoan->amountToReturn) != 1)
		return 0;
	return 1;
}

int writeLoanToBinFileCompressed(FILE* fp, const Loan* pLoan)
{
	BYTE data[3] = { 0 };
	data[0] = pLoan->amountToGive & 0xFF;// lowest 8 bits of int 1
	data[1] = ((pLoan->amountToGive & 0x300) >> 8) | ((pLoan->amountToReturn) << 2);// remaining 2 bits of int1 and lowest 6 bits of int2
	data[2] = (pLoan->amountToReturn) >> 6;// remaining 4 bits of int2
	if (!fp)
		return 0;

	if (fwrite(&data, sizeof(BYTE), 3, fp) != 3)
		return 0;
	return 1;
}

int readLoanFromBinFileCompressed(FILE* fp, Loan* pLoan)
{
	BYTE data[3];
	if (fread(&data, sizeof(BYTE), 3, fp) != 3)
		return 0;
	pLoan->amountToGive = data[0] | (data[1] & 0x03) << 8;
	pLoan->amountToReturn = ((data[1] >> 2 & 0x3F) | data[2] << 6);
	return 1;
}

int isOkAmountOfLoan(int theAmountOfLoan)
{
	if ((theAmountOfLoan % 100 != 0) || (theAmountOfLoan > 1000) || (theAmountOfLoan <= 0))
		return 0;
	return 1;
}

void printLoan(const void* l) {
	Loan* loan = (Loan*)l;
	printf(".......................\n");
	printf("Amount taken: %d$\n", loan->amountToGive);
	printf("Amount to pay: %d$\n", loan->amountToReturn);
	printf(".......................\n");
}


