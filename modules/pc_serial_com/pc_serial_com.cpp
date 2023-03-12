//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "smart_plant_system.h"
#include "pc_serial_com.h"
#include "event_log.h"
#include "date_and_time.h"
#include "ldr_sensor.h"
#include "grow_light.h"
#include "moisture_sensor.h"
#include "water_valve.h"
#include "plant_selector.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

typedef enum{
    PC_SERIAL_COMMANDS,
    PC_SERIAL_GET_CODE,
    PC_SERIAL_SAVE_NEW_CODE,
} pcSerialComMode_t;

//=====[Declaration and initialization of public global objects]===============

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static pcSerialComMode_t pcSerialComMode = PC_SERIAL_COMMANDS;

//=====[Declarations (prototypes) of private functions]========================

static void pcSerialComStringRead( char* str, int strLength );

static void pcSerialComCommandUpdate( char receivedChar );

static void availableCommands();
static void commandSetDateAndTime();
static void commandShowDateAndTime();
static void commandShowStoredEvents();
static void commandShowLightReading();
static void commandShowMoistureReading();
static void commandUpdateLight(int status);
static void commandOpenWaterValve();
static void commandCloseWaterValve();
static void commandSystemToggle();
static void commandPlantWrite();
static void commandLightWrite();
static void commandWaterWrite();

//=====[Implementations of public functions]===================================

void pcSerialComInit()
{
    availableCommands();
}

char pcSerialComCharRead()
{
    char receivedChar = '\0';
    if( uartUsb.readable() ) {
        uartUsb.read( &receivedChar, 1 );
    }
    return receivedChar;
}

void pcSerialComStringWrite( const char* str )
{
    uartUsb.write( str, strlen(str) );
}

void pcSerialComUpdate()
{
    char receivedChar = pcSerialComCharRead();
    if( receivedChar != '\0' ) {
        switch ( pcSerialComMode ) {
            case PC_SERIAL_COMMANDS:
                pcSerialComCommandUpdate( receivedChar );
            break;

            default:
                pcSerialComMode = PC_SERIAL_COMMANDS;
            break;
        }
    }    
}

//=====[Implementations of private functions]==================================

static void pcSerialComStringRead( char* str, int strLength )
{
    int strIndex;
    for ( strIndex = 0; strIndex < strLength; strIndex++) {
        uartUsb.read( &str[strIndex] , 1 );
        uartUsb.write( &str[strIndex] ,1 );
    }
    str[strLength]='\0';
}


static void pcSerialComCommandUpdate( char receivedChar )
{
    switch (receivedChar) {
        case '1': commandSetDateAndTime(); break;
        case '2': commandShowDateAndTime(); break;
        case '3': commandShowStoredEvents(); break;
        case '4': commandShowLightReading(); break;
        case '5': commandShowMoistureReading(); break;
        case '6': commandUpdateLight(1); break;
        case '7': commandUpdateLight(0); break;
        case '8': commandOpenWaterValve(); break;
        case '9': commandCloseWaterValve(); break;
        case 'S': case 's': commandSystemToggle(); break;
        case 'P': case 'p': commandPlantWrite(); break;
        case 'L': case 'l': commandLightWrite(); break;
        case 'W': case 'w': commandWaterWrite(); break;
        default: availableCommands(); break;
    } 
}

static void availableCommands()
{
    pcSerialComStringWrite( "Press '1' to set the date and time\r\n" );
    pcSerialComStringWrite( "Press '2' to get the date and time\r\n" );
    pcSerialComStringWrite( "Press '3' to get the stored events\r\n" );
    pcSerialComStringWrite( "Press '4' to get the current light reading\r\n");
    pcSerialComStringWrite( "Press '5' to get the current moisture sensor reading\r\n");
    pcSerialComStringWrite( "Press '6' to turn on the light\r\n");
    pcSerialComStringWrite( "Press '7' to turn off the light\r\n");
    pcSerialComStringWrite( "Press '8' to open the water valve\r\n");
    pcSerialComStringWrite( "Press '9' to close the water valve\r\n");
    pcSerialComStringWrite( "Press 'S' or 's' to start or stop the automatic system\r\n");
    pcSerialComStringWrite( "Press 'P' or 'p' to get the current plant\r\n");
    pcSerialComStringWrite( "Press 'L' or 'l' to get the time under light in mins\r\n");
    pcSerialComStringWrite( "Press 'W' or 'w' to get the time between waters in mins\r\n");
    pcSerialComStringWrite( "\r\n" );
}

static void commandSetDateAndTime()
{
    char year[5] = "";
    char month[3] = "";
    char day[3] = "";
    char hour[3] = "";
    char minute[3] = "";
    char second[3] = "";
    
    pcSerialComStringWrite("\r\nType four digits for the current year (YYYY): ");
    pcSerialComStringRead( year, 4);
    pcSerialComStringWrite("\r\n");

    pcSerialComStringWrite("Type two digits for the current month (01-12): ");
    pcSerialComStringRead( month, 2);
    pcSerialComStringWrite("\r\n");

    pcSerialComStringWrite("Type two digits for the current day (01-31): ");
    pcSerialComStringRead( day, 2);
    pcSerialComStringWrite("\r\n");

    pcSerialComStringWrite("Type two digits for the current hour (00-23): ");
    pcSerialComStringRead( hour, 2);
    pcSerialComStringWrite("\r\n");

    pcSerialComStringWrite("Type two digits for the current minutes (00-59): ");
    pcSerialComStringRead( minute, 2);
    pcSerialComStringWrite("\r\n");

    pcSerialComStringWrite("Type two digits for the current seconds (00-59): ");
    pcSerialComStringRead( second, 2);
    pcSerialComStringWrite("\r\n");
    
    pcSerialComStringWrite("Date and time has been set\r\n");

    dateAndTimeWrite( atoi(year), atoi(month), atoi(day), 
        atoi(hour), atoi(minute), atoi(second) );
}

static void commandShowDateAndTime()
{
    char str[100] = "";
    sprintf ( str, "Date and Time = %s", dateAndTimeRead() );
    pcSerialComStringWrite( str );
    pcSerialComStringWrite("\r\n");
}

static void commandShowStoredEvents()
{
    char str[EVENT_STR_LENGTH] = "";
    int i;
    for (i = 0; i < eventLogNumberOfStoredEvents(); i++) {
        eventLogRead( i, str );
        pcSerialComStringWrite( str );   
        pcSerialComStringWrite( "\r\n" );                    
    }
}

static void commandShowLightReading()
{
    char str[100] = "";
    sprintf ( str, "Current Light Reading = %.2f", ldrSensorRead() );
    pcSerialComStringWrite( str );
    pcSerialComStringWrite("\r\n");
}

static void commandShowMoistureReading()
{
    char str[100] = "";
    sprintf ( str, "Current Moisture Reading = %.2f", moistureSensorRead() );
    pcSerialComStringWrite( str );
    pcSerialComStringWrite("\r\n");
}

static void commandUpdateLight(int status)
{
    if (status == 1){
        onLight();
        manualTurnOnWrite(true);
    } else {
        offLight();
        manualTurnOnWrite(false);
    }
}

static void commandOpenWaterValve()
{
    openValve();
}

static void commandCloseWaterValve()
{
    closeValve();
}

// Re initialises the watering and lighting system if the auto system is active
// Writes a message to the event log
static void commandSystemToggle()
{
    bool SystemOn = smartPlantSystemToggle();
    lightAndValveInit();
    char* eventString = "AUTO SYSTEM";
    eventLogWrite(SystemOn, eventString);
    pcSerialComStringWrite("\r\n");
}

// Writes the current plant to the event log
static void commandPlantWrite()
{
    char str[100] = "";
    sprintf ( str, "Current Plant= %s", getPlant() );
    pcSerialComStringWrite( str );
    pcSerialComStringWrite("\r\n");
}

static void commandLightWrite()
{
    char str[100] = "";
    sprintf ( str, "Required Light in Mins= %d", getLightRequirement() );
    pcSerialComStringWrite( str );
    pcSerialComStringWrite("\r\n");
}

static void commandWaterWrite()
{
    char str[100] = "";
    sprintf ( str, "Required Water in Mins= %d", getWaterSchedule() );
    pcSerialComStringWrite( str );
    pcSerialComStringWrite("\r\n");
}