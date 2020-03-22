/*****************************************************************************
 * Author : Mahmudul Hossain
 * Date : 09/10/2019
 * Purpose : Carry out all the file input output operation for tic tac toe
 * **************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "LinkedList.h"
#include "myTime.h"
#define FALSE 0
#define TRUE !FALSE
#include <ctype.h>

#define BUFFSIZE 256


#include "board.h"

/****************************************************************************
 *SUBMODULE : readFile 
 *IMPORT : filename (string), rows,columns and win (Pointers to integer)
 *EXPORT : num (Integer) used a flag to determine condition of read operation,
           valid rows,columns and wins values pass by reference
 *ASSERTION : Valid settings are read and assigned to the pointers
 ***************************************************************************/
 
/* Reads the settings.txt file */
/* On succesfully reading the file, it returns TRUE else FALSE */

/*file format : M=%d (columns)
 *              N=%d (rows)
 *              K=%d (win)
 *              can be in any order */

int readFile(char* filename, int *rows, int *columns, int *win)
{
    FILE* fptr = fopen(filename, "r");

    /*Initially set the read operation to be failed */
    int num = FALSE;

    /*First character to be read from each line which has to be M,N or K */
    char value;

    /*Store the integer value each character stores temporarily */
    int temp;

    /*Determines if exactly two variables are read and assigned */
    int read;

    /*Must set values to variable exactly 3 times else the read operation is
     * considered as failure */
    int readCount = 0;

    if(fptr != NULL)
    {
        /*Read till end of file */
        while(!(feof(fptr)))
        {
            /*Store the character and value in temporarily after reading 
             * from line */
            read = fscanf(fptr,"%c=%d\n",&value,&temp);
            
            
            if((ferror(fptr)) || (read != 2))
            {
                perror("Error in file format : \n");
                num = FALSE; 
            }
			
			value = toupper(value);
            /*Assign values to rows,columns and win to matching value*/
            if(value == 'M')
            {
                *columns = temp;
                num = TRUE; 
                readCount++;
            }
            else if(value == 'N')
            {
                *rows = temp;
                num = TRUE;   
                readCount++;
            }
            else if(value == 'K')
            {
                *win = temp;
                num = TRUE;      
                readCount++;
            }
            /*If value does not match MNK then error */
            else
            {
                fprintf(stderr,"Error in file format : \n");
                num = FALSE; 
            }
            
        }

        /*Rows and columns must be positive for valid memory  to
         * be allocated when running the program */
        if((*rows < 1) || (*columns < 1) ||(*win < 0) || (readCount != 3))
        {
            num = FALSE;
        }

        fclose(fptr);
    } 
    else
    {
        perror("Error in handling file : \n");
    }   

    return num; 
}

/****************************************************************************
 *SUBMODULE : writeFile
 *IMPORT : inSettings (Pointer to Settings), recordLog (Pointer to LinkedList)
 *EXPORT : none
 *ASSERTION : Write settings and logs for each game to a file with a specific 
              file name
 ***************************************************************************/
 
void writeFile(Settings* inSettings, LinkedList* recordLog)
{
    /*Store the current time */
    int hour, min, day, month;
    log* newLog;

    /*current node starts from the head of the linked list */
    LinkedListNode* current = recordLog -> head;


    char filename [BUFFSIZE];

    FILE* fptr;
    
    /*Determine the current time which is to be used as file name */
    calcTime(&hour,&min,&day,&month);

    /*Update the filename by parsing values of variables in a specific
     * format string*/
    sprintf(filename,"MNK_%d-%d-%d_%d-%d_%d-%d.log",inSettings->rows,inSettings->columns,inSettings->win,hour,min,day,month);
    
   
    fptr = fopen(filename,"w");

    /*The logs are saved in file exactly the same way they are outputted 
     * to the user*/
    if(fptr != NULL)
    {
        /*Start by printing the settings */
        fprintf(fptr,"%s\n","SETTINGS");
        fprintf(fptr,"\tM : %d\n",inSettings->rows);
        fprintf(fptr,"\tN : %d\n",inSettings->columns);
        fprintf(fptr,"\tK : %d\n",inSettings->win);

        /*Save logs from the beginning */
        while(current != NULL)
        {
            newLog = (log*)(current -> data);
            /*Repeat until end of linked list */
            if(newLog != NULL)
            { 
                if(newLog -> turn == 1)
                {
                    fprintf(fptr,"GAME : %d\n", newLog -> gameNum);
                }
                fprintf(fptr,"\tTurn : %d\n", newLog -> turn);
                fprintf(fptr,"\tPlayer : %s\n", newLog -> player);
                fprintf(fptr,"\tLocation : %d,%d\n", newLog -> x, newLog -> y);
            } 
            
                   
            current = current -> next;

        }

        /*Error handling if any problems arised during saving logs to the file */
        if(ferror(fptr))
        {
            perror("Error handling file : \n");
        }

        fclose(fptr);

        printf("Logs saved successfully \n");
    }
    else
    {
        perror("Error writing file : \n");
    }
}
    

