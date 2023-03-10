//=====[Libraries]=============================================================

#include <cstring>
#include <iostream>
#include <string> 

#include "mbed.h"
#include "arm_book_lib.h"


#include "user_interface.h"

#include "smart_plant_system.h"
#include "display.h"
#include "pc_serial_com.h"
#include "plant_selector.h"
#include "event_log.h"
#include "water_valve.h"
#include "grow_light.h"

//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 1000

//=====[Declaration of private data types]=====================================


//=====[Declaration and initialization of public global objects]===============

InterruptIn cycleButton(PG_1);
InterruptIn confirmButton(PF_9);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static int currentIndex = 0;
static bool cyclable = true;
static bool updated = false;
static bool locked = false;

//string plants[] = { "Azalea", "Blossom", "Olive", "Poppy", "Dracaena" };



//=====[Declarations (prototypes) of private functions]========================

static void userInterfaceDisplayInit();
static void cycleButtonCallback();
static void confirmButtonCallback();

//=====[Implementations of public functions]===================================

void userInterfaceInit()
{
    cycleButton.mode(PullUp);
    confirmButton.mode(PullUp);

    cycleButton.fall(&cycleButtonCallback);
    confirmButton.fall(&confirmButtonCallback);

    userInterfaceDisplayInit();

}

void userInterfaceDisplayUpdate()
{
    if (updated){
        userInterfaceDisplayInit();

        if (locked){
            const char* string = getPlant();
            plantChangeWrite(string);
            lightInit();
            waterValveInit();
            locked = false;
        }

        displayCharPositionWrite ( 6,0 );
        
        if (currentIndex > NUMBER_OF_PLANTS){
            currentIndex = 0;
        }

        setCurrentIndex(currentIndex);

        char* c = getPlant();

        displayStringWrite(c);

        updated = false;
    }

}

//=====[Implementations of private functions]==================================

static void userInterfaceDisplayInit()
{
    displayInit();
     
    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "Plant: " );

    if (cyclable){
        displayCharPositionWrite ( 0,1 );
        displayStringWrite( "LEFT BTN CYCLE" );
    } else {
        displayCharPositionWrite ( 0,1 );
        displayStringWrite( "LOCKED IN" );
    }

    displayCharPositionWrite ( 6,0 );

    setCurrentIndex(currentIndex);

    char* c = getPlant();

    //char* c = const_cast<char*>(plants[currentIndex].c_str());

    displayStringWrite(c);

}

static void cycleButtonCallback()
{
    if (cyclable) {
        currentIndex ++;
        updated = true;
    }
}

static void confirmButtonCallback()
{
    cyclable = false;
    updated = true;
    locked = true;
    //char* c = const_cast<char*>(plants[currentIndex].c_str());
    //plantChangeWrite(c); 
}
