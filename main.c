/*****************************************************************************
 * Author : Mahmudul Hossain
 * Date : 20/10/2019
 * Purpose : Start the tic tac toe game
 * **************************************************************************/



#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FILE_H
#define FILE_H
#include "file.h"
#endif

#include "operation.h"

#define FALSE 0
#define TRUE !FALSE


/****************************************************************************
 *SUBMODULE : main
 *IMPORT : argument count, argument array
 *EXPORT : integer
 *ASSERTION : Takes in arguments from terminal, determining the settings of 
              the game and start the program
 ***************************************************************************/
 

int main(int argc, char* argv[])
{
    /*Initialise settings of the game to invalid */
    int rows = -1, columns = -1, win = -1; 
    if(argc == 2)
    {
        /*Read the settings file and assign the settings of the game in file is valid */
        if(readFile(argv[1],&rows, &columns, &win))
        {
            /* Start the program */
            operation(rows,columns,win);   
        }
        else
        {
            fprintf(stderr,"settings file is invalid\n");
        }     

    }
    else
    {
        fprintf(stderr,"Need exactly two arguments :\n");
        fprintf(stderr,"./EXEC <settings_file>\n");
        
    }

    return 0;
}

