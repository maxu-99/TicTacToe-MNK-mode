#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "board.h"
#include "display.h"
#include "logger.h"
#include "game.h"
#include "win.h"
#define FALSE 0
#define TRUE !FALSE

/****************************************************************************
 *SUBMODULE : play 
 *IMPORT : table(2D array of board), inSettings(Pointer to Settings),
            recordLog(Pointer to LinkedList)
 *EXPORT : none
 *ASSERTION : Play tic tac toe game until a win or a draw
 ***************************************************************************/
 
void play(Board** table,Settings* inSettings, LinkedList *recordLog)
{
    /*Keep track on number of turns */
    int counter = 1;

    /*x and y co-ordinates for player to enter in tactactoe board */
    int x,y;

    /*Initialise winner to be no one */
    int winner = -1;

    /*Keep track the number of games played */
    static int game = 1;


    printf("Game no : %d\n",game);

    /*No need to play game if draw is already predicted */
    /*If winning condition is already 0, the game is considered as a draw before initiating */ 
    if(inSettings -> win == 0 )
    {
        winner = 0;
    }

    /*Start with player X*/
    while(winner == -1)
    {     
        printf("Turn : %d\n",counter);
        /*Player enters and valid move in the board */
        /*If the move was a winning move 1 is assigned to winner meaning that
         * X is the winner */
        winner = makeMove(table,"X",inSettings,&x,&y);

        /*Create a new log record and insert into the recordLog LinkedList */       
        insertLast(recordLog,createLog(counter,"X",y,x,game));

        /*Inc turn number after a valid move is made */
        counter++;
     
        /*Determine if the board is full */
        /*If full then it is a draw */   
        winner = checkDraw(counter, inSettings, winner);
            
        /*If winner is not determine proceed to the next player */
        if(winner == -1)
        {

            printf("Turn : %d\n",counter);
            winner = makeMove(table,"O",inSettings,&x,&y);

            insertLast(recordLog,createLog(counter,"O",y,x,game));
            counter++;

            winner = checkDraw(counter, inSettings, winner);
        }

    }

    /*Game over*/
    /*Display valid winner to the user */
    displayWinner(winner);

    /*Increase the game count for next game to be played */
    game++;

    /*Free memory allocated for the board */
    freeBoard(table,inSettings->rows);
}


/****************************************************************************
 *SUBMODULE : checkDraw
 *IMPORT : counter(Integer), inSettings(Pointer to Settings), winner (Integer)
 *EXPORT : winner (Integer)
 *ASSERTION : If the board is full of player entries then the game is draw
***************************************************************************/
 
int checkDraw(int counter, Settings* inSettings, int winner)
{
    if(winner == -1)
    {  
        /*If counter is greater than total number of entries of the board
         * indicating that the board is full */
        if(counter > inSettings->rows*inSettings->columns)
        {
            winner = 0;
        }   
    }
    return winner;
}   

/****************************************************************************
 *SUBMODULE : makeMove
 *IMPORT : table(2D array of Board), player(String),
            inSettings(Pointer to Settings), x (Pointer to Integer),
            y (Pointer to Integer)
 *EXPORT : winner(Integer)
 *ASSERTION : Make a valid entry in the tic tac toe game followed by deciding
              if the entry is a winning move
***************************************************************************/
 
int makeMove(Board** table,char* player,Settings* inSettings,int* x,int* y)
{
    int winner = -1;
    int valid = FALSE;

    /*Used for input validation from terminal */
    int c;
    char check;

    /*Take input for entry from user until a valid non-empty co-ordinates are
     * entered */
    while(!(valid))
    {
        /*Display current state of tic tac board */
        displayBoard(table,inSettings);
        printf("Player %s's turn, enter position : \n", player);
        
        /*Co-ordinates enter must be withing the dimensions of the board 
         * and of right format */
        while((scanf("%d,%d%c",y,x,&check) != 3) || (*y < 0) || 
              (*y > inSettings->columns - 1 ) || (*x < 0) || 
              (*x > inSettings->rows - 1) || (check != '\n'))
        {
            fprintf(stderr,"Invalid choice please enter again : \n");      
            displayBoard(table,inSettings);
            printf("Player %s's turn, enter position : \n", player);
                    
            /*Taken from slide 38 Lecure 6 :Input and Output */
            while((c=getchar()) != '\n' && (c != EOF))
            {
            /*  Clear the buffer stdin by reading each character of stdin to c */
            /* Tried to use fflush(stdin) didnt work since the behaviour is undefined */
 
            }
                
        }

        /*Check if the state is pre occupied or not */
        /* state = 1 means occupied else 0 empty*/
        if(table[*x][*y].state != 1)
        {
            /*Update the board with valid entry symbol and state */
            table[*x][*y].symbol = player;
            table[*x][*y].state = 1;
            /*The move is valid */
            valid = TRUE;
            
        }
        if(!(valid))
        {
            fprintf(stderr,"The position is already occupied, enter again : \n");
        }
    }
 
    /*Determine if the recent entry is a winning move horizontally/vertically/
     * diagonally/anti-diagonally */   
    winner = checkWin(table,inSettings,player); 

    
    return winner;
}
   


/****************************************************************************
 *SUBMODULE : freeBoard
 *IMPORT : table(2D array of Board), rows (Integer)
 *EXPORT : none
 *ASSERTION : free allocated memory for the board
 ***************************************************************************/
 
void freeBoard(Board** table, int rows)
{
    int ii;
    for(ii = 0; ii< rows; ii++)
    {
        free(table[ii]);
        table[ii] = NULL;
    }

    free(table);
    table = NULL;
}

/****************************************************************************
 *SUBMODULE : createBoard 
 *IMPORT : inSettings (Pointer to Settings)
 *EXPORT : table(2D array of empty board)
 *ASSERTION : Create an empty board
 ***************************************************************************/
 
Board** createBoard(Settings* inSettings)
{
    int i,j;
    
    /*Allocate board with valid width and height */
    Board **table = (Board**)malloc(inSettings->rows * sizeof(Board*));
    for(i = 0; i < inSettings->rows; i++)
    {
        table[i] = (Board*)malloc(inSettings->columns * sizeof(Board));
    }

    /*Initialise the board by setting the board to be empty and all entries
     * unoccupied with the state to 0 */
    for(i = 0; i < inSettings->rows; i++)
    {
        for(j = 0; j < inSettings->columns; j++)
        {
            table[i][j].symbol = " ";
            table[i][j].state = 0;
        }
    }

    return table;
}

/****************************************************************************
 *SUBMODULE : changeSettings 
 *IMPORT : inSettings (Pointer to Settings)
 *EXPORT :  none
 *ASSERTION : Settings of the game are changed according to valid user input
 ***************************************************************************/
 
void changeSettings(Settings* inSettings)
{
    /*Used for valid user input from terminal*/
    char check;
    int c;

    printf("Enter width : \n");

    while((scanf("%d%c",&inSettings->columns,&check) == 0) || (inSettings->columns < 1) || (check != '\n' ))
    {
        /*User must enter a poisitive width */
        /*If width is inputted in a wrong format */
        /*check ensures that enter is pressed alongwith integer*/
    
        fprintf(stderr,"Invalid width please enter again : \n"); 
        printf("Enter width : \n");
               
        /*Taken from slide 38 Lecture 6 :Input and Output */
        while((c=getchar()) != '\n' && (c != EOF))
        {
            /*  Clear the buffer stdin by assiging each character of stdin to c */
            /* Tried to use fflush(stdin) didnt work since the behaviour is undefined */
        }    
        
    }
     
    printf("Enter height : \n");
    while((scanf("%d%c",&inSettings->rows,&check) == 0) || (inSettings->rows < 1) || (check != '\n' ))
    {
        /*User must enter a poisitive height */
        /*If height is inputted in a wrong format */
        /*check ensures that enter is pressed alongwith integer*/
   
        fprintf(stderr,"Invalid height please enter again : \n"); 
        printf("Enter height : \n");
               
        /*Taken from slide 38 Lecture 6 :Input and Output */
        while((c=getchar()) != '\n' && (c != EOF))
        {
            /*  Clear the buffer stdin by assiging each character of stdin to c */
            /* Tried to use fflush(stdin) didnt work since the behaviour is undefined */
        }    
        
    }
 
    printf("Enter matching win number : \n");

    while((scanf("%d%c",&inSettings->win,&check) == 0) || (inSettings->win < 0) || (check != '\n' ))
    {
        /*User must enter a poisitive win */
        /*If win is inputted in a wrong format */
        /*check ensures that enter is pressed alongwith integer*/
        fprintf(stderr,"Invalid matching win number please enter again : \n"); 
        printf("Enter matching win number : \n");
               
        /*Taken from slide 38 Lecture 6 :Input and Output */
        while((c=getchar()) != '\n' && (c != EOF))
        {
            /*  Clear the buffer stdin by assiging each character of stdin to c */
            /* Tried to use fflush(stdin) didnt work since the behaviour is undefined */
        }    
        
    }

}

