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

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void smartPlantSystemInit()
{
    userInterfaceInit();
    lightInit();
    waterValveInit();
    pcSerialComInit();
}

void smartPlantSystemUpdate()
{
    pcSerialComUpdate();
    userInterfaceDisplayUpdate();
    waterValveUpdate();
    growLightUpdate();
    //lightUpdate(1);
    //eventLogUpdate();
    //delay(SYSTEM_TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================
