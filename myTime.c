/*****************************************************************************
 * Author : Mahmudul Hossain
 * Date : 16/10/2019
 * Purpose : Determine current time and date
 * **************************************************************************/



#include <time.h>

/****************************************************************************
 *SUBMODULE : calcTime 
 *IMPORT : hour(Pointer to an integer), min(Pointer to an Integer), 
           day(Pointer to an Integer), month(Pointer to an Integer)
 *EXPORT : none
 *ASSERTION : Allocate the current time to the imported variables
              which will then be used as a filename to store the logs
 ***************************************************************************/
 


void calcTime(int *hour, int *min, int *day, int *month)
{
    /*Obtained from : https://www.techiedelight.com/print-current-date-and-time-in-c/
     * (Accessed on : 16/10/2019) */
    time_t moment = time(0);
    struct tm *current = localtime(&moment);
 
    *hour = current -> tm_hour;
    *min = current -> tm_min;
    *day = current -> tm_mday;
    *month = current -> tm_mon + 1;
        
}
