//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "grow_light.h"

#include "smart_plant_system.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============


DigitalInOut lightPin(PE_3);


//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool lightState = OFF;

//=====[Declarations (prototypes) of private functions]========================

static void lightUpdate();

//=====[Implementations of public functions]===================================

void lightInit()
{
    lightPin.mode(OpenDrain);
    lightPin.output();
    lightPin = LOW;
    
}

void offLight()
{
    lightPin.output();
    lightPin = LOW;
    lightStateWrite(OFF);
}

void onLight()
{
    lightPin.input();
    lightStateWrite(ON);
}

bool lightStateRead()
{
    return lightState;
}

void lightStateWrite(bool state)
{
    lightState = state;
}


//=====[Implementations of private functions]==================================