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

// Updated the LCD display if a new plant is selected or the last plant is locked in
// If a plant is locked in the initialiser functions are called for the water valve and light
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
        
        if (currentIndex >= NUMBER_OF_PLANTS){
            currentIndex = 0;
        }

        setCurrentIndex(currentIndex);

        char* c = getPlant();

        displayStringWrite(c);

        updated = false;
    }

}

//=====[Implementations of private functions]==================================

// Displays the plant
// Informs the user of how they can cycle the plant
// If the plant is locked in then displays locked in
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

    displayStringWrite(c);

}

// Interrupt for the cycle button to ensure it can be pressed at any time in the system running
// Increments the current index in the plant array so the next plant can be displayed or used
static void cycleButtonCallback()
{
    if (cyclable) {
        currentIndex ++;
        updated = true;
    }
}

// Interrupt for the confirm button to ensure it can be pressed at any time in the system running
// Makes cyclable and locked false and true resepctively so the system knows if a plant has been selected
static void confirmButtonCallback()
{
    cyclable = false;
    updated = true;
    locked = true;
}
