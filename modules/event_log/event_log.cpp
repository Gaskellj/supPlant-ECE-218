//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "event_log.h"


//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

typedef struct systemEvent {
    time_t seconds;
    char typeOfEvent[EVENT_LOG_NAME_MAX_LENGTH];
} systemEvent_t;

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool valveState    = OFF;
static bool lightState    = OFF; 
static int eventsIndex     = 0;
static systemEvent_t arrayOfStoredEvents[EVENT_LOG_MAX_STORAGE];

//=====[Declarations (prototypes) of private functions]========================

static void eventLogElementStateUpdate( bool lastState,
                                        bool currentState,
                                        const char* elementName );

//=====[Implementations of public functions]===================================

void eventLogUpdate()
{
}

int eventLogNumberOfStoredEvents()
{
    return eventsIndex;
}

void eventLogRead( int index, char* str )
{
    str[0] = '\0';
    strcat( str, "Event = " );
    strcat( str, arrayOfStoredEvents[index].typeOfEvent );
    strcat( str, "\r\nDate and Time = " );
    strcat( str, ctime(&arrayOfStoredEvents[index].seconds) );
    strcat( str, "\r\n" );
}

void eventLogWrite( bool currentState, const char* elementName )
{
    //char eventAndStateStr[EVENT_LOG_NAME_MAX_LENGTH] = "";

    //strcat( eventAndStateStr, elementName );
    //if ( currentState ) {
        //strcat( eventAndStateStr, "_ON" );
    //} else {
        //strcat( eventAndStateStr, "_OFF" );
    //}

    //arrayOfStoredEvents[eventsIndex].seconds = time(NULL);
    //strcpy( arrayOfStoredEvents[eventsIndex].typeOfEvent, eventAndStateStr );
    //if ( eventsIndex < EVENT_LOG_MAX_STORAGE -1 ) {
       //eventsIndex++;
    //} else {
        //eventsIndex = 0;
    //}

    //pcSerialComStringWrite(eventAndStateStr);
    //pcSerialComStringWrite("\r\n");
}

//=====[Implementations of private functions]==================================

static void eventLogElementStateUpdate( bool lastState,
                                        bool currentState,
                                        const char* elementName )
{
    if ( lastState != currentState ) {        
        eventLogWrite( currentState, elementName );       
    }
}