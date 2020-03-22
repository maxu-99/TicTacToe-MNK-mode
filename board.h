/*****************************************************************************
 * Author : Mahmudul Hossain
 * Date : 20/10/2019
 * Purpose : Stores all the user defined variables
 * **************************************************************************/


/*Board struct used to store X or O entries of each player 
 * which will be allocated later on when a game initiates*/
typedef struct
{
    /* X or O or " " */
    char* symbol;

    /* 1 for occupied and 0 for empty */
    int state;
} Board;

/*Stores the log entries entered by a player 
 * which will then be stored in a linked list for printing to a file 
 * and displaying to the user*/
typedef struct
{
    /*Game number from beginning */
    int gameNum;

    /*Record the move number entered on each game */
    int turn;

    /*Player making the move is either X or O */
    char* player;

    /*X co-ordinate entered by player */
    int x;

    /*Y co-ordinate enter by player */
    int y;
} log;

/*Stores the current settings of the game, used to allocate dimensions of the
 * 2D Board and also used to determine the final winner of the game*/
typedef struct
{
    /*Height of the board */
    int rows;

    /*Width of the board */
    int columns;

    /*Number of matching symbols to win */
    int win;
}Settings;


