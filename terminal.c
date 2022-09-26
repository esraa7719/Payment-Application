#include "card.h"
#include "terminal.h"
#include "server.h"

#define size_of_trDate_array 10
#define current_year 2022
#define max_amount 5000

uint8_t numof_trDate_chars = 0;//counter for the number of (transaction Date) chars
uint16_t trD = 0;
uint16_t trM = 0;
uint16_t trY = 0;
EN_terminalError_t returnof_TransactionDate = 0,returnof_isCardExpired = 0, 
returnof_isBelowMaxAmount=0,returnof_TransactionAmount = 0,returnof_setMaxAmount = 0;
extern uint16_t exM;
extern uint16_t exY;
float transaction_amount = 0;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	printf("Please enter the transaction date in format DD/MM/YYYY \n ");

	for (numof_trDate_chars = 0; numof_trDate_chars < size_of_trDate_array; numof_trDate_chars++)
	{
		scanf_s("%c", &termData->transactionDate[numof_trDate_chars]);

		if (termData->transactionDate[numof_trDate_chars] == 10) //10 represents the enter button decimal equivalent
		{
			break;
		}

	}
	//printf("%d\n", strlen(termData->transactionDate));

	trD = (termData->transactionDate[0] - 48) * (10) + (termData->transactionDate[1] - 48);//transaction day
	trM = (termData->transactionDate[3] - 48) * (10) + (termData->transactionDate[4] - 48);//transaction Month
	trY = (termData->transactionDate[6] - 48) * (1000) + (termData->transactionDate[7] - 48) * (100) + (termData->transactionDate[8] - 48) * (10) + (termData->transactionDate[9] - 48);//transaction year

	if (strlen(termData->transactionDate) > size_of_trDate_array || strlen(termData->transactionDate) < size_of_trDate_array)
	{
		//printf("WRONG_DATE\n");
		returnof_TransactionDate = WRONG_DATE;
		return returnof_TransactionDate;
	}
	else if (termData->transactionDate == NULL)
	{
		//printf("WRONG_DATE\n");
		returnof_TransactionDate = WRONG_DATE;
		return returnof_TransactionDate;
	}

	else if ((trM > 12) || (trM < 1))
	{
		//printf("WRONG_DATE\n");
		returnof_TransactionDate = WRONG_DATE;
		return returnof_TransactionDate;
	}
	else if ((trY - current_year) != 0)
	{
		//printf("WRONG_DATE\n");
		returnof_TransactionDate = WRONG_DATE;
		return returnof_TransactionDate;
	}
	else if ((trD > 31) || (trD < 1))
	{
		//printf("WRONG_DATE\n");
		returnof_TransactionDate = WRONG_DATE;
		return returnof_TransactionDate;
	}

	else
	{
		//printf("OK\n");
		returnof_TransactionDate = ok;
		return returnof_TransactionDate;
	}
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	if (trY > exY)
	{
		returnof_isCardExpired = EXPIRED_CARD;
		return returnof_isCardExpired;
	}
	else if (trY = exY)
	{
		if (trM > exM)
		{
			returnof_isCardExpired = EXPIRED_CARD;
			return returnof_isCardExpired;
		}
		else
		{
			returnof_isCardExpired = ok;
			return returnof_isCardExpired;
		}
	}
	else
	{
		returnof_isCardExpired = ok;
		return returnof_isCardExpired;
	}

}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("Please enter the transaction amount \n ");
	scanf_s("%f", &termData->transAmount);
	transaction_amount =  termData->transAmount;
		if (transaction_amount <= 0.000)
	{
		//printf("INVALID_AMOUNT\n");
		returnof_TransactionAmount = INVALID_AMOUNT;
		return returnof_TransactionAmount;
	}
	else
	{
		//printf("OK\n");
		returnof_TransactionAmount = ok;
		return returnof_TransactionAmount;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	termData->maxTransAmount = max_amount;
	if (max_amount <= 0)
	{
		//printf("INVALID_MAX_AMOUNT \n");
		returnof_setMaxAmount = INVALID_MAX_AMOUNT;
		return returnof_setMaxAmount;
	}
	else
	{
		//printf("OK \n");
		returnof_setMaxAmount = ok;
		return returnof_setMaxAmount;
	}

}















EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if ((transaction_amount) > (max_amount))
	{
		returnof_isBelowMaxAmount = EXCEED_MAX_AMOUNT;
		return returnof_isBelowMaxAmount;
	}
	else
	{
		returnof_isBelowMaxAmount = ok;
		return returnof_isBelowMaxAmount;
	}

}


