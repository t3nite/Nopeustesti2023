//Jos Buttons.h ei ole määritelty niin määritellään
#ifndef BUTTONS_H
#define BUTTONS_H

#include <arduino.h>

// Määritellään muuttujat extern-muuttujiksi jotta niitä voidaan käyttää muissa tiedostoissa 
extern volatile bool buttonState[];
//unsigned long on 32-bittinen positiivinen kokonaisluku
extern volatile unsigned long buttonStartTime[];
extern const unsigned long debounceTime;

//8-bittiset vakiot joiden arvo ei muutu
const byte firstPin = 2; // Kytkin 1
const byte secondPin = 3; // Kytkin 2
const byte thirdPin = 4; // Kytkin 3
const byte lastPin =  5; // Kytkin 4
const byte gameStartPin = 6; // Aloittaa pelin

/* 
  initButtonsAndButtonInterrupts subroutine is called from Setup() function
  during the initialization of Speden Spelit. This function does the following:
  1) Initializes 4 button pins for the game = Arduino pins 2,3,4,5
  2) Initializes 1 button pin for starting the game = Aruino pin 6
  3) Enables PinChangeInterrupt on D-bus in a way that interrupt
     is generated whenever some of pins 2,3,4,5,6 is connected to LOW state
*/

//Funktion prototyyppi
void initButtonsAndButtonInterrupts(void);

//Varmistetaan että tiedosto sisällytetään vain kerran
#endif