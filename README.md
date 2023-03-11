# supPlant-ECE-218

#### Project By: James Gaskell, Asher Zive, Daniel Pacheco

## Outline

This project tackles the challenge of caring for a plant whilst on vacation and helps people that are not good at caring for plants (often forgetting to water them or providing bad lighting conditions) to keep their plants alive through automation. In an ideal scenario the user can set the system up by selecting their plant type and leave the system running for an extended period of time without requiring attention or input. 

The system will water the plant when the soil is dry based on a watering schedule unique to the plant, and will provide light to the plant if the room is dark and the plant has not recieved enough light in the day.

The user can troubleshoot using the serial monitor where an arry of measurements and events will be be shown to the user upon pressing the respective button. The user can manually water and provide light to the plant and will also activate the automation feature by pressing 'S' (indicating Start).

## Conditions

### Simple Conditions

|Function|Trigger|Behaviour|
|--------|---------|------------|
|Get date and time|2 on the serial monitor|The current system time is outputted|
|Get stored events|3 on the serial monitor|The system's events (lighting, watering etc.) are outputted|
|Get light reading|4 on the serial monitor|The current LDR reading is displayed between 0 and 1|
|Get moisture reading|5 on the serial monitor|The moisture sensor is displayed between 0 and 1|
|Cycle the current plant|Press the left button (in relation to the display)|A different plant is displayed on the LCD|
|Lock in the current plant|Press the right button (in relation to the display)|The current plant and LOCKED IN is displayed on the LCD|
|Get current plant|'p' on the serial monitor|The current plant is displayed|
|Get time under light|'l' on the serial monitor|The amount of light the plant needs in minutes is displayed|
|Get water period|'w' on the serial monitor|The time in between waters for the plant in minutes is displayed|

### Complex conditions

- #### The user turns the light on and off using serial monitor

If the user enters '6' on the serial monitor the light will turn on and remain on, an event message will be displayed on the serial monitor. When the user enters '7' on the serial monitor the light will turn off.

NOTE: Due to hardware constraints of the motor controller the light cannot be on at the same time as the valve is open, therefore if the valve is open the light cannot be turned on


- #### The user opens and closes the valve using serial monitor

If the user enters '8' on the serial monitor the valve will be opened, an event message will be displayed on the serial monitor, and water will flow through the dispersion head. When the user enters '9' on the serial monitor the valve will close and water will stop flowing.

NOTE: Due to hardware constraints of the motor controller, if the light is on when '8' is entered, the light is turned off and if this is the case the light is turned back on when the watering stops


- #### The user presses 's' on the serial monitor

The automatic plant system is activated and an event message is displayed on the serial monitor to inform the user. 


## Automatic Plant System

- Each plant has a hard coded amount of light and water it needs to thrive

#### Auto Watering

The watering system uses time increment along with the plant's water requirement to open the valve periodically (for the dracaena test plant this means watering every 2 minutes). The watering lasts 30 seconds and then the valve closes and water stops flowing. 

The watering only takes place if the soil is dry (currently set to a moisture reading of 0.2) in case the plant does not absorb as much water for any reason or the plant recieves some other water source in the meantime.

NOTE: if the light is currently on (as with the manual method) the light will be switched off when the valve opens and switched back on when the valve closes.

#### Auto Lighting

The lighting system uses the current date and time to check whether the light needs to be turned on or not. Each light has a time under light which keeps track of the time the plant has been exposed to light for the day (whether it be natural or artificial).

The system checks if the time under light and the current time of the day allows enough remaining time to ensure the plant recieves enough natural light if this is not the case, and the room is dark (as per the ldr reading), the artificial light is turned on.

NOTE: The lamp will not turn on whilst the valve is open (as with the manual method), in which case this is covered as the loop will update the lamp to on after the valve is closed
