#include "buttons.h"

/* Taulukko johon määritellään kytkimien alustava tila, 
ennen kuin varsinaiset kytkimien arvot luetaan */
volatile bool buttonState[] = {HIGH, HIGH, HIGH, HIGH, HIGH};  // Alkutila on HIGH eli true (ei painettu)

// Määritellään taulukko johon varastoidaan jokaisen kytkimen painalluksen aika 
volatile unsigned long buttonStartTime[] = {0, 0, 0, 0, 0};  // Aluksi aika on 0

// Määritellään aika, jonka aikana napinpainalluksen tulee pysyä vakaana 
const unsigned long debounceTime = 15;  // Aikaväliä voi säätää tarvittaessa (pelissä 30)

// Funktio joka määrittelee kytkimet ja kytkinten keskeytykset
void initButtonsAndButtonInterrupts(void)
{
  // Laitetaan kaikille kytkimille sisäinen vastus päälle
  pinMode(firstPin, INPUT_PULLUP);
  pinMode(secondPin, INPUT_PULLUP);
  pinMode(thirdPin, INPUT_PULLUP);
  pinMode(lastPin, INPUT_PULLUP);
  pinMode(gameStartPin, INPUT_PULLUP);

  /* Mahdollistetaan keskeytykset D-porteissa (Arduinon pinnit 2-6, 11-13) */
  PCICR |= (1 << PCIE2); 

  /* Mahdollistetaan maskirekisterin 2 avulla keskeytysten laukaiseminen kun pinnien PCINT23-PCINT18 
  (PD2-PD7 eli arduinon pinnit 2-6) tila muuttuu */
  PCMSK2 |= (1 << PCINT18); // Pinni 2
  PCMSK2 |= (1 << PCINT19); // Pinni 3
  PCMSK2 |= (1 << PCINT20); // Pinni 4
  PCMSK2 |= (1 << PCINT21); // Pinni 5
  PCMSK2 |= (1 << PCINT22); // Pinni 6

  // Sallitaan globaalit keskeytykset
  sei();  
}
