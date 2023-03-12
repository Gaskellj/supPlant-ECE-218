//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include <string>

#include "grow_light.h"

#include "smart_plant_system.h"
#include "ldr_sensor.h"
#include "event_log.h"
#include "water_valve.h"
#include "plant_selector.h"
#include "date_and_time.h"

#include "pc_serial_com.h"


//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============


DigitalInOut lightPin(PE_3);


//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool lightState = OFF;
static bool manualTurnOn = false;

static int lightRequirement;

static bool autoSystemActive = false;

static int timeUnderLight;

static int prevMinute;

//=====[Declarations (prototypes) of private functions]========================

static void lightUpdate();
static int retrieveTimeMins();
static bool checkAutoSystemActive();

//=====[Implementations of public functions]===================================

void lightInit()
{
    lightPin.mode(OpenDrain);
    lightPin.output();
    lightPin = LOW;
    lightRequirement = getLightRequirement();
    timeUnderLight = 0;
    prevMinute = (hoursRead() * 60) + minutesRead();
}

void offLight()
{
    lightPin.output();
    lightPin = LOW;
    lightStateWrite(OFF);
    eventLogWrite(false, "GROWTH_LIGHT");
}

void onLight()
{
    if (!(getValveStatus())){
        lightPin.input();
        lightStateWrite(ON);
        eventLogWrite(true, "GROWTH_LIGHT");
    }
}

void growLightUpdate()
{
    if (checkAutoSystemActive()){
        if (ldrSensorRead() > 0.15 && !lightState){
            onLight();
        } else if (ldrSensorRead() < 0.05 && lightState && !manualTurnOn){
            offLight();
        }
    }
}

bool lightStateRead()
{
    return lightState;
}

void lightStateWrite(bool state)
{
    lightState = state;
}

void manualTurnOnWrite(bool status)
{
    if (status){
        manualTurnOn = true;
    } else {
        manualTurnOn = false;
    }
}

int retrieveTimeMins()
{
    int hours = hoursRead();
    int mins = minutesRead();
    mins += hours * 60;
    if (mins != prevMinute){
        prevMinute = mins;
        if ((!lightState && ldrSensorRead() < 0.05) || (lightState)){
            timeUnderLight++;
        }
    }
    if (mins == 0){
        timeUnderLight = 0;
    }
    return mins;
}

static bool checkAutoSystemActive()
{
    if (retrieveTimeMins() > (1440 - lightRequirement + timeUnderLight)) {
        return true;
    } else {
        return false;
    }
}


//=====[Implementations of private functions]==================================