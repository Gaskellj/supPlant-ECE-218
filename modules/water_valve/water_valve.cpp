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

void waterValveUpdate()
{
    if (!systemBlocked && !valveOpen && (moistureSensorRead() < 0.2)) {
        openValve();
    } else if (valveOpen){
        valveOpenTime += INCREMENT;
        if (valveOpenTime >= 370000){
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

void getSystemBlockedTime()
{
    int minutes = getWaterSchedule();
    systemBlockedTime = minutes * 740000; //timed system minute
}