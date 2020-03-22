/*****************************************************************************
 * Author : Mahmudul Hossain
 * Date : 09/10/2019
 * Purpose : Start the tic tac toe game
 * **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "board.h"
#include "file.h"
#include "display.h"
#include "game.h"
#include "logger.h"

#include "operation.h"


/****************************************************************************
 *SUBMODULE : operation 
 *IMPORT : rows (Integer), columns(Integer), win(Integer)
 *EXPORT : none
 *ASSERTION : Imports valid settings and carry out specific operations entered
              by the user
 ***************************************************************************/
 
void operation(int rows, int columns, int win)
{
    /*User input to carry out specific operations */
    int choice;
    
    /*Determine the maximum number of options to display to the user, depends on 
     * the conditional compilation */
    int max;

    /*Keep record of the logs entered during the game */
    /*LinkedList taken from prac07 UCP submission date : 
     * link :
     */
    LinkedList* recordLog;

    /*2D array of Board struct to store the entries entered by players */
    Board** table;

    /*Allocate memory and assign valid settings to inSettings which will be 
     * passed into several functions, reduces the number of parameters to 
     * import */
    Settings* inSettings = (Settings*)malloc(sizeof(Settings));
    inSettings -> rows = rows;
    inSettings -> columns = columns;
    inSettings -> win = win;

    /*Assign recordLog with an empty linked list */
    recordLog = createLinkedList();

    /*If Editor is defined then allow user to change settings by choosing 
     * 5th opton */
    /*If not defined then display 4 options without the change settings 
     * option */    
    #ifdef Editor
    max = 5;
    #else 
    max = 4;
    #endif

    do
    {
        /*Display main menu to the user */
        menu();
        
        /*Assign choice with a valid option */
        validChoice(&choice,max);

        switch(choice)
        {
             case 0 :
                /*Exit the program */
                printf("Good bye ! \n");
                break;

            case 1 :

                /*Initialise the platfrom where tic tac toe is going to be 
                 * played based on settings*/
                table = createBoard(inSettings);

                /*Start the game */
                play(table,inSettings,recordLog);  
                break;

            case 2 : 

                /*Display the current settings of the game */
                displaySettings(inSettings);
                break;

            case 3 :
                /*Display the current settings*/
                displayFile(inSettings); 
                /*Display all the logs of each game */
                printLinkedList(recordLog,&printLog);
                break;

            case 4 : 
                /*Allow user to write logs to file only if conditional compilation
                 * Secret=1 is not defined */
                #ifndef Secret    
                writeFile(inSettings, recordLog);  
         
                #else
                /*If defined then output an error to the user */
                printf("Disabled \n");      
                #endif  
                break;
            
            /*If Editor=1 is defined during conditional compilation, then
             * allow user to change settings of the game */
            #ifdef Editor
            case 5 :    
                changeSettings(inSettings);
                break;
            #endif
                   }

    }while(choice != 0);

    /*Free memory allocated for linked list before exiting progam */
    freeLinkedList(recordLog,&freeLog);
    
    /*Free allocated memory for settings before exiting program */
    free(inSettings);
}

/****************************************************************************
 *SUBMODULE : validChoice 
 *IMPORT : choice (Pointer to int), max (Integer)
 *EXPORT : choice
 *ASSERTION : A valid choice is entered by user
 ***************************************************************************/
 
void validChoice(int* choice,int max)
{
   
    /*Used in input validation from the terminal */
    int c;  
    char check;


    /*If choice is inputted in a wrong format or if not within range */
    /*check ensures that enter is pressed alongwith integer*/
    while((scanf("%d%c",choice,&check) == 0) || (*choice < 0) || (*choice > max) || (check != '\n' ))
    {
        fprintf(stderr,"Invalid choice please enter again : \n");
        
        /*Display main menu to user */ 
        menu();
               
        /*Taken from slide 38 Lecture 6 :Input and Output */
        while((c=getchar()) != '\n' && (c != EOF))
        {
            /*  Clear the buffer stdin by reading each character of stdin to c */
            /* Tried to use fflush(stdin) didnt work since the behaviour is undefined */
        }    
        
    }
 
}
