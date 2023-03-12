//=====[Libraries]=============================================================

#include "arm_book_lib.h"

#include "smart_plant_system.h"
#include "pc_serial_com.h"
#include "grow_light.h"
#include "user_interface.h"
#include "water_valve.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

bool SystemActive = false;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

// Initialisers taken out into their own method so they can be called independent of the other inits
void lightAndValveInit()
{
    lightInit();
    waterValveInit();
}

void smartPlantSystemInit()
{
    userInterfaceInit();
    pcSerialComInit();
    lightAndValveInit();
}

// Program loop
// Only calls the update functions for light and water valve if the auto system is active
void smartPlantSystemUpdate()
{
    pcSerialComUpdate();
    userInterfaceDisplayUpdate();
    if (SystemActive) {
        waterValveUpdate();
        growLightUpdate();
    }
    //lightUpdate(1);
    //eventLogUpdate();
    //delay(SYSTEM_TIME_INCREMENT_MS);
}

// Toggles wether the automatic system is active
// This will determine which update functions are called by the code
bool smartPlantSystemToggle()
{
    SystemActive = !SystemActive;
    return SystemActive;
}

//=====[Implementations of private functions]==================================
