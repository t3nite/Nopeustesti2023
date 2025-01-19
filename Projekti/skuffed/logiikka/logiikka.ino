#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "topten.h"
#include "sound.h"
#include <avr/interrupt.h>
#include <avr/io.h>


int randomNumber;
  volatile uint8_t buttonPressCount = 0;
  bool gameIsOn = false;
  int randomNumbers[100]; // Taulukko random geneeroiduille numeroille
  int userNumbers[100]; // Taulukko pelaajan painalluksille
  volatile bool timeToCheckGameStatus = false;
  int userIndex = 0; //Kayttajan tayttamat 
  TopTen topten;
  int points = 0;
  int correctButtonPresses = 0;

void setup()
{
  Serial.begin(9600);

  void stopTheGame();
  initializeLeds();
  initializeDisplay();
  initButtonsAndButtonInterrupts();
  initializeLeds();
  soundInitialize();
  toptenInitialize(topten);
  int lokigfunktion ();

  for (int i = firstPin; i <= gameStartPin; i++)
  {
    buttonState[i] =  digitalRead(i) == LOW;
  }
}


void loop() {

  if (timeToCheckGameStatus) {
    checkGame(buttonPressCount);
    timeToCheckGameStatus = false;
  }

  if (topten.flagShow) {
    toptenShow(topten);
  }
}

ISR(PCINT2_vect) {

  // Iterate through the button pins 2-6
  for (int i = firstPin; i <= gameStartPin; i++)
  {
    // Read the current state of the button
    bool currentState = digitalRead(i);

    // Check if the button is pressed and was not pressed previously
    if (currentState == LOW && buttonState[i])
    {
      // Button pressed, record the start time and set button state to pressed
      buttonStartTime[i] = millis();
      buttonState[i] = true; 
    }
    // Check if the button is released and was pressed previously
    else if (currentState == HIGH && !buttonState[i])
    {
      // Button released, check for stable state after debounce time
      if (millis() - buttonStartTime[i] > debounceTime)
      {
        //
        buttonState[i] = false;
      }
    }
  }
}
   /*
     Here you implement logic for handling
	 interrupts from 2,3,4,5 pins for Game push buttons
	 and for pin 6 for start Game push button.
   */

   void lokigfunktion () {


   if (buttonState[6] == true) {
     void startTheGame();
  } else {
    // Check if any of the buttons 2-5 are pressed when their corresponding LED is HIGH
    if ((buttonState[2] == LOW && digitalRead(A2) == HIGH) ||
        (buttonState[3] == LOW && digitalRead(A3) == HIGH) ||
        (buttonState[4] == LOW && digitalRead(A4) == HIGH) ||
        (buttonState[5] == LOW && digitalRead(A5) == HIGH)) {
      // Increase the score by 1
      points++;
    } else if ((buttonState[2] == LOW && digitalRead(A2) == LOW) ||
               (buttonState[3] == LOW && digitalRead(A3) == LOW) ||
               (buttonState[4] == LOW && digitalRead(A4) == LOW) ||
               (buttonState[5] == LOW && digitalRead(A5) == LOW)) {
      // If the LED is LOW while the button corresponding to it is LOW, stop the game
      void stopTheGame();
    }
  }
}




ISR(TIMER1_COMPA_vect)
{ 
  // Arvotaan luku 0-3 väliltä
  randomNumber = random(0, 4);
  Serial.println("randomNumber");

  // Lisätään painalluskerta kokonaislaskuriin
  buttonPressCount++;

  // Jos oikeita painalluskertoja kymmenen, pienennetään keskeytysväliä
  if(buttonPressCount >= 10)
  {
    OCR1A = 0.9 * OCR1A;
    if (OCR1A == 0) {
      void stopTheGame();
{
  gameIsOn = false;
  // Stop Timer1
  TCCR1B = 0;
  buttonPressCount = 0;

  toptenAdd(topten, points);
  topten.flagShow = true;
}
    }
  }

  // Tallennetaan random numerot taulukkoon
  randomNumbers[buttonPressCount - 1] = randomNumber;

  // Random luku on arvottu, sytytetään sen mukainen LED
  setLed(randomNumber);
}


void checkGame(byte nbrOfButtonPush)
{
  int correctButtonPresses = 0;

  for (int i= 0; i < nbrOfButtonPush; i++)
  {
    if (randomNumbers[i] == userNumbers[i])
    {
      correctButtonPresses++;
      points = correctButtonPresses;
    }
    else
    {
      stopTheGame();
      clearAllLeds();
      Serial.println("Last button press invalid. Stopping the game.");
      soundFalse();
    }
  }
  showResult(correctButtonPresses);
}


void initializeTimer(void)
{
  cli(); // Disabloidaan keskeytykset

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = 15624;

  TIMSK1 |= (1 << OCIE1A);

  // Timer on CTC (Clear Timer on Compare Match), prescaler 1024
  TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);

  sei(); // Enable interrupts
}


void initializeGame()
{
	// Alustetaan randomNumbers ja userNumbers taulukko
  for (int i = 0; i < 100; i++)
  {
    randomNumbers[i] = -1;
  }
  for (int i = 0; i < 100; i++)
  {
    userNumbers[i] = -1;
  }
  // Alustetaan indeksi
  userIndex = 0;

  clearAllLeds();
}