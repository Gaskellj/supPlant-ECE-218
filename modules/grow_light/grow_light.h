//=====[#include guards - begin]===============================================

#ifndef _GROW_LIGHT_H_
#define _GROW_LIGHT_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void lightInit();
void onLight();
void offLight();
bool lightStateRead();
void lightStateWrite(bool state);

//=====[#include guards - end]=================================================

#endif // _GROW_LIGHT_H_