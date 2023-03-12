//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include <string>

#include "date_and_time.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

char* dateAndTimeRead()
{
    time_t epochSeconds;
    epochSeconds = time(NULL);
    return ctime(&epochSeconds);    
}


// Reads the current time from the RTC
// Takes the part of the string that represents the hours
// Uses the ascii to derive the value of the characters and returns it
int hoursRead()
{
    char* dateAndTime = dateAndTimeRead();
    char hoursTenColumn[100] = "" ;
    memcpy(hoursTenColumn, &dateAndTime[11], 1);
    int hours = (int(hoursTenColumn[0] - 48) * 10);
    char hoursSinglesColumn[100] = "";
    memcpy(hoursSinglesColumn, &dateAndTime[12], 1);
    hours += (int(hoursSinglesColumn[0] - 48));
    return(hours);

}

// Reads the current time from the RTC
// Takes the part of the string that represents the minutes
// Uses the ascii to derive the value of the characters and returns it
int minutesRead()
{
    char* dateAndTime = dateAndTimeRead();
    char minsTenColumn[100] = "" ;
    memcpy(minsTenColumn, &dateAndTime[14], 1);
    int mins = (int(minsTenColumn[0] - 48) * 10);
    char minsSinglesColumn[100] = "";
    memcpy(minsSinglesColumn, &dateAndTime[15], 1);
    mins += (int(minsSinglesColumn[0] - 48));
    return(mins);
}

void dateAndTimeWrite( int year, int month, int day, 
                       int hour, int minute, int second )
{
    struct tm rtcTime;

    rtcTime.tm_year = year - 1900;
    rtcTime.tm_mon  = month - 1;
    rtcTime.tm_mday = day;
    rtcTime.tm_hour = hour;
    rtcTime.tm_min  = minute;
    rtcTime.tm_sec  = second;

    rtcTime.tm_isdst = -1;

    set_time( mktime( &rtcTime ) );
}

//=====[Implementations of private functions]==================================

