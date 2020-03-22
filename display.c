/*****************************************************************************
 * Author : Mahmudul Hossain
 * Date : 09/10/2019
 * Purpose : Displays any valid output to the user
 * **************************************************************************/



#include <stdio.h>
#include "board.h"

/****************************************************************************
 *SUBMODULE : displaySettings
 *IMPORT : rows(Integer), columns(Integer), win(Integer)
 *EXPORT : none
 *ASSERTION : Display settings of the game to the user
 ***************************************************************************/
 
void displaySettings(Settings* inSettings)
{
    printf("Height : %d \n", inSettings->rows);
    printf("Width : %d\n", inSettings->columns);
    printf("Number of consecutive symbols to win : %d \n", inSettings->win);
}


/****************************************************************************
 *SUBMODULE : menu 
 *IMPORT : none
 *EXPORT : node
 *ASSERTION : Display the main menu to the user with options
 ***************************************************************************/
 
void menu(void)
{
    printf("Enter choice :\n");
    printf("0:Exit the application \n");

    printf("1:Start a new game \n");  
    printf("2:View the settings of the game\n"); 
    printf("3:View the current logs\n"); 
    printf("4:Save the logs to a file\n");
    #ifdef Editor
    printf("5:Change settings\n");  
    #endif
    printf("\n"); /*Just to make it more visible */
}

 /****************************************************************************
 *SUBMODULE : displayBoard
 *IMPORT : table(Board array), rows(Integer), columns(Integer)
 *EXPORT : none
 *ASSERTION : Display the state of the board to the user
 ***************************************************************************/
 
void displayBoard(Board** table,Settings* inSettings)
{
    int i,j;
    printf("=====================================================\n");
    for(i = 0; i < inSettings->rows; i++)
    {
        printf("||");
        for(j = 0; j < inSettings->columns; j++)
        {
            printf("%s |",table[i][j].symbol);
        }
        printf("|\n");
        printf("----------------------------------------------------\n");
    }

    printf("=======================================================\n");
}

/****************************************************************************
 *SUBMODULE : displayWinner
 *IMPORT : winner(Integer)
 *EXPORT : none
 *ASSERTION : Display winner to the user where 1 = X, 2 = O or 0 = draw
 ***************************************************************************/
 
void displayWinner(int winner)
{
    switch(winner)
    {
        case 0 : 
            printf("The match is a draw. \n");
            break;

        case 1 :
            printf("Player X is the winner !! \n");
            break;
        case 2 :
            printf("Player O is the winner !! \n");
            break;
    }
}

/****************************************************************************
 *SUBMODULE : displayFile 
 *IMPORT : rows(Integer), columns(Integer), win(Integer)
 *EXPORT : none
 *ASSERTION : Display the settings of the file used in displaying the logs
 ***************************************************************************/
 
void displayFile(Settings* inSettings)
{
    printf("SETTINGS : \n");
    printf("\t M : %d\n", inSettings->rows);
    printf("\t N : %d\n", inSettings->columns);
    printf("\t K : %d\n", inSettings->win);
}

