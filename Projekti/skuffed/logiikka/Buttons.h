#ifndef BUTTONS_H
#define BUTTONS_H

#include <arduino.h>

// Declare arrays and constants as extern to make them accessible in other files
extern volatile bool buttonState[];
extern volatile unsigned long buttonStartTime[];
extern const unsigned long debounceTime;

const byte firstPin = 2; // First PinChangeInterrupt on D-bus
const byte secondPin = 3; // Second PinChangeInterrupt on D-bus
const byte thirdPin = 4; // Third PinChangeInterrupt on D-bus
const byte lastPin =  5; // Last PinChangeInterrupt on D-bus
const byte gameStartPin = 6; // Starts the game

/* 
  initButtonsAndButtonInterrupts subroutine is called from Setup() function
  during the initialization of Speden Spelit. This function does the following:
  1) Initializes 4 button pins for the game = Arduino pins 2,3,4,5
  2) Initializes 1 button pin for starting the game = Aruino pin 6
  3) Enables PinChangeInterrupt on D-bus in a way that interrupt
     is generated whenever some of pins 2,3,4,5,6 is connected to LOW state

*/
void initButtonsAndButtonInterrupts(void);

#endif