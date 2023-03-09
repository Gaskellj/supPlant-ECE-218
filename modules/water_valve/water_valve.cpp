#include "mbed.h"
#include "arm_book_lib.h"

DigitalInOut valvePin(PF_2);

void waterValveInit()
{
    valvePin.mode(OpenDrain);
    valvePin.output();
    valvePin = LOW;
    
}

void closeValve()
{
    valvePin.output();
    valvePin = LOW;
}

void openValve()
{
    valvePin.input();
}