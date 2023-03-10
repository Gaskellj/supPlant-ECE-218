#include "mbed.h"
#include "arm_book_lib.h"

#include "moisture_sensor.h"
#include "water_valve.h"
#include "event_log.h"
#include "plant_selector.h"

DigitalInOut valvePin(PF_2);

#define INCREMENT 1

int valveOpenTime = 0;
int systemBlockedTime = 0;
bool systemBlocked = false;
bool valveOpen = false;

static void incrementTime();
static void incrementSystemBlocked();
static void getSystemBlockedTime();

void waterValveInit()
{
    valvePin.mode(OpenDrain);
    valvePin.output();
    valvePin = LOW;
    getSystemBlockedTime();
    
}

void waterValveUpdate()
{
    if (!systemBlocked && !valveOpen && (moistureSensorRead() < 0.2)) {
        openValve();
        valveOpen = true;
    } else if (valveOpen){
        valveOpenTime += INCREMENT;
        if (valveOpenTime >= 1600000){
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

void getSystemBlockedTime()
{
    int minutes = getWaterSchedule();
    systemBlockedTime = minutes * 3200000;
}


void closeValve()
{
    valvePin.output();
    valvePin = LOW;
    valveOpen = false;
    systemBlocked = true;
    valveOpenTime = 0;
    eventLogWrite(false, "IRRIGATION");
}

void openValve()
{
    valvePin.input();
    eventLogWrite(true, "IRRIGATION");
}