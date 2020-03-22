#include <stdio.h>
#include <stdlib.h>
#include "board.h"

/****************************************************************************
 *SUBMODULE : createLog
 *IMPORT : counter(Integer), inPlayer(String), inX(Integer), inY(Integer),
            inGame(Integer)
 *EXPORT : Pointer to a log entry
 *ASSERTION : Allocate memory for a new log entry according to the imports
 ***************************************************************************/
 
log* createLog(int counter,char* inPlayer,int inX, int inY, int inGame)
{
    log *newLog = (log*)malloc(sizeof(log));
    
    newLog -> turn = counter;
    newLog -> player = inPlayer;
    newLog -> x = inX;
    newLog -> y = inY;
    newLog -> gameNum = inGame;

    return newLog;
}

/****************************************************************************
 *SUBMODULE : printLog
 *IMPORT : inLog (Pointer to a log)
 *EXPORT : none
 *ASSERTION : Display logs to the user
 ***************************************************************************/
 
void printLog(void* inLog)
{
    log* toLog = (log*)inLog;

    /*Print game number only once accoriding to specification*/
    if(toLog->turn == 1)
    {
        printf("GAME : %d\n",toLog -> gameNum);
    }
    printf("\tTurn : %d\n", toLog -> turn);
    printf("\tPlayer : %s\n", toLog -> player);
    printf("\tLocation : %d,%d\n", toLog -> x, toLog -> y);
}

/****************************************************************************
 *SUBMODULE : freeLog
 *IMPORT : inLog (Pointer to a log)
 *EXPORT : none
 *ASSERTION : Deallocate memory for the log entry
 ***************************************************************************/
 
void freeLog(void* inLog)
{
    log* killLog = (log*)inLog;
    free(killLog);
    killLog = NULL;
}

