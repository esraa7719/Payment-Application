#include "server.h"
#include "app.h"

void main() //appStart FUNCTION_TEST
{
	appStart();
}

void appStart(void)
{	
    ST_cardData_t cardData = { {0,0,0} };

	ST_terminalData_t terminalData = { 0,0,0 };

	ST_transaction_t transactionData = { 0,0 };

	getCardHolderName(&cardData);

	getCardExpiryDate(&cardData);

	getCardPAN(&cardData);

	getTransactionDate(&terminalData);

	if (isCardExpired(cardData, terminalData) != 0)
	{
		printf("DECLINED_EXPIRED_CARD");
		exit(0);
	}
	
	
	getTransactionAmount(&terminalData);

	setMaxAmount(&terminalData);
	
	if (isBelowMaxAmount(&terminalData)!=0)
	{
		printf("DECLINED_EXEEDING_MAXIMUM_LIMIT");
		exit(0);
	}
	
	
	if (isValidAccount(&cardData)!=0)
	{
		printf("DECLINED_STOLEN_CARD");
		exit(0);
	}
	

	if (isAmountAvailable(&terminalData) != 0)
	{
		printf("DECLINED_LOW_BALANCE");
		exit(0);
	}
	
    recieveTransactionData(&transactionData);

	saveTransaction(&transactionData);

	

}







