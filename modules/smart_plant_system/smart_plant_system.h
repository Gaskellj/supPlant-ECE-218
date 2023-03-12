//=====[#include guards - begin]===============================================

#ifndef _SMART_PLANT_SYSTEM_H_
#define _SMART_PLANT_SYSTEM_H_

//=====[Declaration of public defines]=========================================

#define SYSTEM_TIME_INCREMENT_MS   10

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void lightAndValveInit();
void smartPlantSystemInit();
void smartPlantSystemUpdate();

bool smartPlantSystemToggle();

//=====[#include guards - end]=================================================

#endif // _SMART_HOME_SYSTEM_H_