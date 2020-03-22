/*****************************************************************************
 * Author : Mahmudul Hossain
 * Date : 17/10/2019
 * Purpose : Determines if a player has played a winning move  
 *           by analysing the current state of tic tac toe board
 * **************************************************************************/

#include <stdio.h>
#include <string.h>
#include "board.h"
#include "win.h"

/****************************************************************************
 *SUBMODULE : checkWin
 *IMPORT : table(2D array of Board), inSettings(Pointer to settings),
            x(Integer),y(Integer),player(String)
 *EXPORT : winner (Integer)
 *ASSERTION : Determines if the board has a matching row for a winner
 ***************************************************************************/

int checkWin(Board** table, Settings* inSettings, char* player)
{
    int winner = -1;

    /*Check horizontal win */
    winner = checkHorizontal(table,inSettings,player);

    /*Check vertical win */
    if(winner == -1)
    {
        winner = checkVertical(table,inSettings,player);
    }

    /*Check diagonal win */
    if(winner == -1)
    {
        winner = checkDiagonal(table,inSettings,player); 
    } 

    /*Check anti diagonal win */
    if(winner == -1)
    {
        winner = checkAntiDiagonal(table,inSettings,player);  
    }
    return winner;
}


/****************************************************************************
 *SUBMODULE : checkHorizontal
 *IMPORT : table(2D array of Board), inSettings(Pointer to Settings),
            String player
 *EXPORT :  winner (Integer)
 *ASSERTION : Determine winner if there is a horizontal match
***************************************************************************/

/*Works*/
int checkHorizontal(Board** table,Settings* inSettings,char* player)
{
    int ii,jj;
    int winner = -1;

    /*Record number of consecutive matches */
    int count = 0;

    /*Iterate through every co-ordinate and check if a horizontal match
     * has occured or not */
    for(ii = 0; ii < inSettings -> rows ; ii++)
    {
        for(jj = 0; jj < inSettings -> columns ; jj++)
        {
            if(strcmp(table[ii][jj].symbol,player) == 0)
            {
                count++;
            }
            else
            {
                count = 0;
            }
            if(count == inSettings -> win)
            {
                winner = checkPlayer(player);
            }
        }
    }

    return winner;
}

/****************************************************************************
 *SUBMODULE : checkVertical
 *IMPORT : table(2D array of Board), inSettings(Pointer to Settings),
            String player
 *EXPORT :  winner (Integer)
 *ASSERTION : Determine winner if there is a vertical match
***************************************************************************/
 /*Works*/
int checkVertical(Board** table,Settings* inSettings,char* player)
{
    int ii,jj;
    int winner = -1;


    /*Record number of consecutive matches */
    int count = 0;

    /*Iterate through every co-ordinate and check if a vertical match
     * has occured or not */ 
    for(ii = 0; ii < inSettings -> columns ; ii++)
    {
        for(jj = 0; jj < inSettings -> rows ; jj++)
        {
            if(strcmp(table[jj][ii].symbol,player) == 0)
            {
                count++;
            }
            else
            {
                count = 0;
            }
            if(count == inSettings -> win)
            {
                winner = checkPlayer(player);
            }
        }
    }
    
    return winner;
}

/****************************************************************************
 *SUBMODULE : checkDiagonal
 *IMPORT : table(2D array of Board), inSettings(Pointer to Settings),
            String player
 *EXPORT :  winner (Integer)
 *ASSERTION : Determine winner if there is a diagonal match
***************************************************************************/
/*Works*/ 
int checkDiagonal(Board** table,Settings* inSettings,char* player)
{
    int ii,jj,kk;
    int winner = -1;


    /*Record number of consecutive matches */
    int count = 0;

    /*Iterate through every co-ordinate and check if a diagonal match
     * has occured or not */ 
    for(ii = 0; ii < inSettings -> rows; ii++)
    {
        for(jj = 0; jj < inSettings -> columns; jj++)
        {
            for(kk = 0; kk < inSettings -> win; kk++)
            {

                /*Prevent indexes access outside the size of board */
                if(((ii+kk) < inSettings -> rows) && ((jj+kk) < inSettings -> columns)) 
                {
                    if(strcmp(table[ii+kk][jj+kk].symbol,player) == 0)
                    {
                        count++;
                    }
                    else
                    {
                        count = 0;
                    }
                    if(count == inSettings -> win)
                    {
                        winner = checkPlayer(player);
                    }
                }   
            }   
        }
    }

    return winner;
}


/****************************************************************************
 *SUBMODULE : checkAntiDiagonal
 *IMPORT : table(2D array of Board), inSettings(Pointer to Settings),
            String player
 *EXPORT :  winner (Integer)
 *ASSERTION : Determine winner if there is a antidiagonal match
***************************************************************************/
/*Works*/ 
int checkAntiDiagonal(Board** table,Settings* inSettings,char* player)
{
    int winner = -1;
    int ii,jj,kk;
    
    /*Record number of consecutive matches */
    int count = 0;

    /*Iterate through every co-ordinate and check if a antidiagonal match
     * has occured or not */ 
    for(ii = 0; ii < inSettings -> rows; ii++)
    {
        for(jj = 0; jj < inSettings -> columns; jj++)
        {
            for(kk = 0; kk < inSettings -> win; kk++)
            {
                /*Prevent indexes access outside the size of board */
                if(((ii+kk) < inSettings -> rows) && ((jj-kk) >= 0)) 
                {
                    if(strcmp(table[ii+kk][jj-kk].symbol,player) == 0)
                    {
                        count++;
                    }
                    else
                    {
                        count = 0;
                    }
                    if(count == inSettings -> win)
                    {
                        winner = checkPlayer(player);
                    }
                }   
            }
        }
    }

    return winner;
}

/****************************************************************************
 *SUBMODULE : checkPlayer
 *IMPORT : player(String)
 *EXPORT : winner(integer)
 *ASSERTION : If a winner is determined, determine if the imported player is 
              X or O
 ***************************************************************************/
 
int checkPlayer(char* player)
{
    int winner = -1;

    if(strcmp(player,"X") == 0)
    {
        /*Player X is the winner */
        winner = 1;
    }
    else if(strcmp(player,"O") == 0)
    {
        /*Player O is the winner */
        winner = 2;
    }

    return winner;

}


