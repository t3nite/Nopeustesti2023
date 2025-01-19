#include "leds.h"

/*
  initializeLeds() subroutine intializes analog pins A2,A3,A4,A5
  to be used as outputs. Speden Spelit leds are connected to those
  pins.  
*/

void initializeLeds()
{
  
    pinMode(A2,OUTPUT);

    pinMode(A3,OUTPUT);

    pinMode(A4,OUTPUT);

    pinMode(A5,OUTPUT);
// see requirements for this function from leds.h
}

/*
  setLed(byte) sets correct led number given as 0,1,2 or 3
  led number 0 corresponds to led connected at Arduino pin A2
  led number 1 => Arduino pin A3
  led number 2 => Arduino pin A4
  led number 3 => Arduino pin A5
  
  parameters:
  byte ledNumber is 0,1,2 or 3
*/

void setLed(byte ledNumber)
{
    switch(ledNumber){
        case 0:
        digitalWrite(A2, HIGH);
        break;

        case 1:
        digitalWrite(A3, HIGH);
        break;

        case 2:
        digitalWrite(A4, HIGH);
        break;

        case 3:
        digitalWrite(A5, HIGH);
        break;

    }
// see requirements for this function from leds.h

}

/*
  clearAllLeds(void) subroutine clears all leds
*/

void clearAllLeds()
{
    digitalWrite(A2, HIGH);

    digitalWrite(A3, HIGH);

    digitalWrite(A4, HIGH);

    digitalWrite(A5, HIGH);
// see requirements for this function from leds.h
 
}

/*
  setAllLeds subroutine sets all leds
*/
void setAllLeds()
{
    digitalWrite(A2, LOW);

    digitalWrite(A3, LOW);

    digitalWrite(A4, LOW);

    digitalWrite(A5, LOW);
// see requirements for this function from leds.h
}
