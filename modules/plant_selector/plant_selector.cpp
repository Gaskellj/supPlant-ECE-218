//=====[Libraries]=============================================================
#include <cstring>
#include <iostream>
#include <string> 

#include "mbed.h"
#include "arm_book_lib.h"

#include "plant_selector.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============


//=====[Declaration of external public global variables]=======================


//=====[Declaration and initialization of public global variables]=============

string plants[] = { "Azalea", "Blossom", "Olive", "Poppy", "Dracaena" };
float waterSchedule[] = { 400, 150, 360, 450, 2}; // These are the times in minutes between waters for theplants
int lightRequirement[] = {600, 800, 1200, 650, 1439}; //These are the times in minutes that the plants need light for

//=====[Declaration and initialization of private global variables]============

int currentIndex = 0;


//=====[Declarations (prototypes) of private functions]========================


//=====[Implementations of public functions]===================================

// Getter methods to retrieve the information about the current plant selected

void setCurrentIndex(int Index)
{
    currentIndex = Index;
}

char* getPlant()
{
    return const_cast<char*>(plants[currentIndex].c_str());
}

int getWaterSchedule()
{
    return (waterSchedule[currentIndex]);
}

int getLightRequirement()
{
    return (lightRequirement[currentIndex]);
}

//=====[Implementations of private functions]==================================