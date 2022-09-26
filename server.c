#include"terminal.h"
#include "server.h"
#include "app.h"

#define Database_size 255
uint16_t x =0;
EN_serverError_t returnof_isValidAccout = 0, returnof_isAmountAvailable=0;
EN_transState_t returnof_saveTransaction=0, returnof_recieveTransactionData=0;
extern float transaction_amount;
static uint32_t SequenceNumber = 0;

ST_accountsDB_t valid_accounts_Database[Database_size] = { {50000,"125487695847521537"},{5487.2548,"125879630215478954"},{168547.254,"984652458701236548"},
                                                         {48568.2445,"123456789012345678"},{85274.21,"012345678901234567"},{95100.2458,"2345678901234567"},
                                                         {74102.658,"3456789012345678901"},{96841.254,"475869362514010203"},{854520.25,"8745210365987401"},
                                                         {254.268,"1234567890123456789"},{968410.254,"012345678901234568"},{5480.7254,"111111111111111111"},
                                                         {48518.2445,"211111111111111111"},{1685.254,"121111111111111111"},{2030.28,"112111111111111111"},
                                                         {8596.24,"111211111111111111"} };

struct ST_transaction_t transaction_Database[Database_size] = { {0,0} };



EN_serverError_t isValidAccount(struct ST_cardData_t* cardData)
{
    uint8_t counter, returnfromstrcmp=0;
    for (counter = 0; counter < Database_size; counter++)
    {
        returnfromstrcmp =strcmp(valid_accounts_Database[counter].primaryAccountNumber, cardData->primaryAccountNumber);
        if (returnfromstrcmp == 0)
        {
            x = counter;
            //printf("OK \n");
            returnof_isValidAccout = Ok;
            break;
            return returnof_isValidAccout;
        }
        
    }
    
    if (returnfromstrcmp != 0)

        {
         //   printf("DECLINED_STOLEN_CARD \n");
        returnof_isValidAccout = DECLINED_STOLEN_CARD;
            return returnof_isValidAccout;
        }
}

EN_serverError_t isAmountAvailable(struct ST_terminalData_t* termData)
{

    if (valid_accounts_Database[x].balance > termData->transAmount)
    {
      //  printf("OK");
      
        returnof_isAmountAvailable = Ok;
        return returnof_isAmountAvailable;

    }
    else
    {
       // printf("LOW_BALANCE");
        returnof_isAmountAvailable = LOW_BALANCE;
        return returnof_isAmountAvailable;
        exit(0);
    }
}

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
    if (returnof_isValidAccout != 0)
    {
        printf("DECLINED_STOLEN_CARD \n");
        returnof_recieveTransactionData = DECLINED_STOLEN_CARD;
        return returnof_recieveTransactionData;
    }
    else  if (returnof_isAmountAvailable != 0)

    {
        printf("DECLINED_INSUFFECIENT_FUND \n");
        returnof_recieveTransactionData = DECLINED_INSUFFECIENT_FUND;
        return returnof_recieveTransactionData;
    }

    else if (returnof_isAmountAvailable == 0 && returnof_isValidAccout == 0)
    {
        printf("APPROVED \n");
        valid_accounts_Database[x].balance -= transaction_amount;
       // printf("The Balance now:%f \n", valid_accounts_Database[x].balance);
        returnof_recieveTransactionData = APPROVED;
        return returnof_recieveTransactionData;
    }
    else
    {
        returnof_recieveTransactionData = INTERNAL_SERVER_ERROR;
        return returnof_recieveTransactionData;
        exit(0);
    }
}    







EN_serverError_t saveTransaction(ST_transaction_t * transData)
{
    static uint32_t SequenceNumber ;

       if (returnof_isValidAccout != 0)
    {
        transaction_Database[SequenceNumber].transState = DECLINED_STOLEN_CARD;
        printf("%c\n", transaction_Database[SequenceNumber].transState);
    }
    else if (returnof_isAmountAvailable != 0)
    {
        transaction_Database[SequenceNumber].transState = DECLINED_INSUFFECIENT_FUND;
        printf("%c\n", transaction_Database[SequenceNumber].transState);
    }
    else if (returnof_isValidAccout ==0 && returnof_isAmountAvailable ==0)
    {
        transaction_Database[SequenceNumber].transState = APPROVED;
        printf("%c\n", transaction_Database[SequenceNumber].transState);
       // printf("%d\n", transaction_Database[SequenceNumber].transactionSequenceNumber);

        returnof_saveTransaction = Ok;
        return returnof_saveTransaction;
    }
    else if (returnof_recieveTransactionData==3)
    {
        transaction_Database[SequenceNumber].transState = INTERNAL_SERVER_ERROR;
        printf("%c\n", transaction_Database[SequenceNumber].transState);
        returnof_saveTransaction = SAVING_FAILED;
        return returnof_saveTransaction;
    }
    

    transaction_Database[SequenceNumber].transactionSequenceNumber = SequenceNumber;
    transData->transactionSequenceNumber = SequenceNumber;
    SequenceNumber++;
    


    }