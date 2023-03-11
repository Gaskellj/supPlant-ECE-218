# supPlant-ECE-218

## Project By: James Gaskell, Asher Zive, Daniel Pacheco

## Outline

This project tackles the challenge of caring for a plant whilst on vacation and helps people that are not good at caring for plants (often forgetting to water them or providing bad lighting conditions) to keep their plants alive through automation. In an ideal scenario the user can set the system up by selecting their plant type and leave the system running for an extended period of time without requiring attention or input. 

The system will water the plant when the soil is dry based on a watering schedule unique to the plant, and will provide light to the plant if the room is dark and the plant has not recieved enough light in the day.

The user can troubleshoot using the serial monitor where an arry of measurements and events will be be shown to the user upon pressing the respective button. The user can manually water and provide light to the plant and will also aci=tivate the automation feature by pressing 'S' (indicating Start).

## Conditions

#### Simple Conditions

|Function|Trigger|Behaviour|
|--------|---------|------------|
|Get date and time|2 on the serial monitor|The current system time is outputted|
|Get stored events|3 on the serial monitor|The system's events (lighting, watering etc.) are outputted|
|Get light reading|4 on the serial monitor|The current LDR reading is displayed between 0 and 1|
|Get moisture reading|5 on the serial monitor|The moisture sensor is displayed between 0 and 1|
|Cycle the current plant|Press the left button (in relation to the display)|A different plant is displayed on the LCD|
|Lock in the current button|Press the right button (in relation to the display)|The current plant and LOCKED IN is displayed on the LCD|
|Incorrect Passcode Display|Yes|Yes|
|Three Attempts|Yes|Yes|
|System Lockout|Yes|Yes|
|System Reset|Yes|Yes|
|View Code|Yes|Yes|
|Change Code|No|Yes|

#### The user turns the light on and off using serial monitor

If the user enters '6' on the serial monitor the light will turn on and remain on. When the user enters '7' on the serial monitor the light will turn off.

NOTE: Due to hardware constraints of the motor controller the light cannot be on at the same time as the valve is open, therefore if the valve is open the light cannot be turned on

#### The user opens and closes the valve using serial monitor

If the user enters '8' on the serial monitor the valve will be opened and water will flow through the dispersion head. When the user enters '9' on the serial monitor the valve will close and water will stop flowing.

NOTE: Due to hardware constraints of the motor controller, if the light is on when '8' is entered, the light is turned off and if this is the case the light is turned back on when the watering stops

