#include "card.h"
#include "terminal.h"

#define size_of_cardHolderName 25
#define max_size_of_cardHolderName_array 24
#define min_size_of_cardHolderName_array 20
#define size_of_exdate_array 6
#define size_of_PAN 20
#define max_size_of_PAN_array 19
#define min_size_of_PAN_array 16
#define current_year 2022

uint8_t numof_holdername_chars = 0;//counter for the number of (holder_name) chars
uint8_t numof_exdate_chars = 0;//counter for the number of (expiration Date) chars
uint8_t numof_PAN_chars = 0;//counter for the number of (PAN) chars
uint16_t exM = 0;
uint16_t exY = 0;
EN_cardError_t returnof_CardHolderName=0;// variable that carries the return value
EN_cardError_t returnof_cardExpirationDate=0;
EN_cardError_t returnof_primaryAccountNumber=0;

 EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
 {
	 	printf("Please enter you name \n ");

    gets(cardData->cardHolderName);

   // printf("%d\n", strlen(cardData->cardHolderName));

	if (strlen(cardData->cardHolderName) > max_size_of_cardHolderName_array || strlen(cardData->cardHolderName) < min_size_of_cardHolderName_array)
	{
		//printf("WRONG_NAME \n");

		returnof_CardHolderName = WRONG_NAME;

		return returnof_CardHolderName;

	}
	else if(cardData->cardHolderName==NULL)
	{
		//printf("WRONG_NAME \n");

		returnof_CardHolderName = WRONG_NAME;

		return returnof_CardHolderName;
	}
	else
	{
		//printf("OK\n");
		returnof_CardHolderName = OK;
		return returnof_CardHolderName;
	}
	
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("Please enter the expiration date of the card in format MM/YY \n ");

	for (numof_exdate_chars = 0; numof_exdate_chars < size_of_exdate_array; numof_exdate_chars++)
	{
		scanf_s("%c", &cardData->cardExpirationDate[numof_exdate_chars]);

		if (cardData->cardExpirationDate[numof_exdate_chars] == 10) //10 represents the enter button decimal equivalent
		{
			break;
		}

	}
	//printf("%d\n", numof_exdate_chars);

	exM = (cardData->cardExpirationDate[0] - 48) * (10) + (cardData->cardExpirationDate[1] - 48);//Month's Number
	exY = (cardData->cardExpirationDate[3] - 48) * (10) + (cardData->cardExpirationDate[4] - 48) + 2000;//Year's Number

	if (numof_exdate_chars  > size_of_exdate_array)
	{
		//printf("WRONG_EXP_DATE\n");
		returnof_cardExpirationDate = WRONG_EXP_DATE;
		return returnof_cardExpirationDate;
	}
	else if (cardData->cardExpirationDate== NULL)
	{
		//printf("WRONG_EXP_DATE\n");
		returnof_cardExpirationDate = WRONG_EXP_DATE;
		return returnof_cardExpirationDate;
	}
	else if ((exM > 12) || (exM < 1))
	{
		//printf("WRONG_EXP_DATE\n");

		returnof_cardExpirationDate = WRONG_EXP_DATE;
		return returnof_cardExpirationDate;
	}
	else if (((exY - current_year) < 0) || (exY - current_year) > 5)
	{
		//printf("WRONG_EXP_DATE\n");

		returnof_cardExpirationDate = WRONG_EXP_DATE;
		return returnof_cardExpirationDate;
	}
	else
	{
		//printf("OK\n");

		returnof_cardExpirationDate = OK;
		return returnof_cardExpirationDate;
	}
	
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("Please enter the PAN \n ");
	gets(cardData->primaryAccountNumber);
	//printf("%d\n", strlen(cardData->primaryAccountNumber));
	if (strlen(cardData->primaryAccountNumber) > max_size_of_PAN_array || strlen(cardData->primaryAccountNumber) < min_size_of_PAN_array)
	{
		//printf("WRONG_PAN \n");

		returnof_primaryAccountNumber = WRONG_PAN;
		return returnof_primaryAccountNumber;
	}
	else if (cardData->primaryAccountNumber == NULL)
	{
		//printf("WRONG_PAN \n");
		returnof_primaryAccountNumber = WRONG_PAN;
		return returnof_primaryAccountNumber;
	}
	else
	{
		//printf("OK \n");
		returnof_primaryAccountNumber = OK;
		return returnof_primaryAccountNumber;
	}
}
