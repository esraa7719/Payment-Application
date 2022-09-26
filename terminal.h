#ifndef terminal_h
#define terminal_h
#include "card.h"
#include "server.h"

typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[12];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
   ok, WRONG_DATE, EXPIRED_CARD , INVALID_CARD , INVALID_AMOUNT , EXCEED_MAX_AMOUNT , INVALID_MAX_AMOUNT
}EN_terminalError_t;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
EN_terminalError_t isCardExpired(struct ST_cardData_t cardData, ST_terminalData_t termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);

#endif
