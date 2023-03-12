//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include <string>

#include "grow_light.h"

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

// The function that runs some the smatPlantSystem when the auto system is active
// checks the light sensor reading and the light state to decide wether the light should be on or off
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

//=====[Implementations of private functions]==================================


// retrieves the current time from date_and_time
// converts the time to minutes
// increments timeUnderLight which is the total time the plant has recieved light for
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

// Checks if the auto system needs to be activated
// Calculates if there is enough time in the day for the plant to recieve its light naturally
// If there is not enough time in the day the automatic system is started so the plant will be lit for the remainder of the day
static bool checkAutoSystemActive()
{
    if (retrieveTimeMins() > (1440 - lightRequirement + timeUnderLight)) {
        return true;
    } else {
        return false;
    }
}