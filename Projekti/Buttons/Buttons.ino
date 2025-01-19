/*Tämä koodi tulostaa sarjamonitorille mitä yhdestä viidestä kytkimestä on painettu, 
ja huolehtii siitä, että kytkinvärähtely ei aiheuta useita ei haluttuja napinpainalluksia*/

// Mukaan sisällytettävät kirjastot
#include <Arduino.h>
#include "buttons.h"

void setup() {
  //Käynnistää sarjaportille viestinnän (voi kommunikoida tietokoneen kanssa) nopeudella 9600 bittiä sekunnissa
  Serial.begin(9600);

  // Odotetaan 1 sekunti järjestelmän vakautumista
  delay(1000);

  for (int i = firstPin; i <= gameStartPin; i++) {
    /*Tässä rivissä digitalRead(i) palauttaa kytkimen pinnin tilan. 
    Jos kytkimen pinnin tila on HIGH, mikä tarkoittaa että kytkin ei ole painettuna, 
    ehto digitalRead(i) == HIGH on tosi. 
    Tällöin buttonState[i] asetetaan arvoksi true, mikä tarkoittaa, 
    että kytkin ei ole painettuna. */
    buttonState[i] = digitalRead(i) == HIGH;
  }
  // Kutsutaan funktio Buttons.cpp-tiedosta
  initButtonsAndButtonInterrupts(); 
}

void loop() {}

// Keskeytyspalvelurutiini joka käsittelee muutoksia Arduinon pinneillä 2-6 
ISR(PCINT2_vect) {

    // Iteroidaan kytkimet 2-6 läpi
    for(int i = firstPin; i <= gameStartPin; i++) {
    /* Luetaan kytkimen nykyinen tila: true (LOW), jos kytkin on painettu
     tai false (HIGH), jos kytkin ei ole painettuna (INPUT_PULLUP-vastuksen ansiosta).*/
    bool currentState = digitalRead(i);

    // Tarkistetaan onko kytkin siirtynyt HIGH-tilaan ja se ei ollut HIGH aiemmin
    if (currentState == HIGH && !buttonState[i]) {
      // Kytkintä on juuri painettu. Tallennetaan aloitusaika millisekunteina taulukkoon ja asetetaan kytkimen tila HIGH
      buttonStartTime[i] = millis();
      buttonState[i] = true; 
    }

    // Tarkistetaan onko kytkin LOW ja se oli aiemmin HIGH
    else if (currentState == LOW && buttonState[i]) {
      // Tarkistetaan onko kulunut tarpeeksi aikaa kytkinvärähtelyn jälkeen. 
    if (millis() - buttonStartTime[i] > debounceTime) {
        // Tulosta painetun kytkimen numero
        Serial.print("Painettu kytkintä nro ");
        Serial.println(i);
      }
      //Nollataan kytkimen tila seuraavaa painallusta varten
      buttonState[i] = false;  
    }
  }    
  }