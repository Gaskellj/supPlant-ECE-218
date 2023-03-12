#include "mbed.h"
#include "arm_book_lib.h"

#include "moisture_sensor.h"
#include "water_valve.h"
#include "event_log.h"
#include "plant_selector.h"
#include "grow_light.h"

DigitalInOut valvePin(PF_2);

#define INCREMENT 1

int valveOpenTime;
int systemBlockedTime;
bool systemBlocked;
bool valveOpen;
bool lightShutOff = false;



static void getSystemBlockedTime();

//=====[Implementations of public functions]==================================

// Vartables in the Init so they are set at their original values when the plant is changed

void waterValveInit()
{
    valveOpenTime = 0;
    systemBlocked = true;
    getSystemBlockedTime();
    valveOpen = false;
    valvePin.mode(OpenDrain);
    valvePin.output();
    valvePin = LOW;
    
}

// The update function called by the smart_plant_system
// Opens or closes the valve based on predefined conditions
// Only runs if the auto system is active
// After the plant is watered, locks the watering system for amount of time between the waters of the plant
void waterValveUpdate()
{
    if (!systemBlocked && !valveOpen && (moistureSensorRead() < 0.2)) {
        openValve();
    } else if (valveOpen){
        valveOpenTime += INCREMENT;
        if (valveOpenTime >= 370000){ // Hard coded 370000 represents 30 seconds to the system as 370000 cycles takes that time
            closeValve();
        }
    }
    if (systemBlocked){
        systemBlockedTime -= INCREMENT;
        if (systemBlockedTime <= 0){
            systemBlocked = false;
            getSystemBlockedTime();
        }
    }
}

bool getValveStatus()
{
    return valveOpen;
}

// Checks if the light had to be shut off
// If the light did have to be shut off, then it turns on the light after the valve is closed
void closeValve()
{
    valveOpen = false;
    if (lightShutOff) {
        onLight();
        lightShutOff = false;
    }
    valvePin.output();
    valvePin = LOW;
    systemBlocked = true;
    valveOpenTime = 0;
    eventLogWrite(false, "IRRIGATION");
}

// Turns off the light if it is on
// Opens the valve
void openValve()
{
    if (lightStateRead() == ON){
        offLight();
        lightShutOff = true;
    }
    valveOpen = true;
    valvePin.input();
    eventLogWrite(true, "IRRIGATION");
}

//=====[Implementations of private functions]==================================

// Gets the system blocked time by multiplying the plant's water minutes (the time between waters) by a system minute
// 740000 is hard coded as this is a timed system minute. i.e. the system has 740000 cycles of this code in a minute
void getSystemBlockedTime()
{
    int minutes = getWaterSchedule();
    systemBlockedTime = minutes * 740000; //timed system minute
}