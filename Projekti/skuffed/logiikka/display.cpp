#include "display.h"


const int serialInputPin = 8;   // DS
const int outEnablePin = 9;     // OE
const int latchClockPin = 10;   // STCP
const int shiftClockPin = 11;   // SHCP
const int resetPin = 12;        // MR


void initializeDisplay(void) {
  
  
  pinMode(resetPin, OUTPUT);
  pinMode(shiftClockPin, OUTPUT);
  pinMode(latchClockPin, OUTPUT);
  pinMode(outEnablePin, OUTPUT);
  pinMode(serialInputPin, OUTPUT);
  

  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW);
  digitalWrite(shiftClockPin, LOW);
  digitalWrite(latchClockPin, LOW);
  digitalWrite(outEnablePin, LOW);
  digitalWrite(resetPin, HIGH);
  
}

void writeByte(uint8_t byte, bool last) {
  
  //Serial.print("Writing byte: ");
  //Serial.println(byte);
  for (int i = 0; i < 8; i++) {
    digitalWrite(shiftClockPin, HIGH);
    digitalWrite(serialInputPin, (byte & (1 << i)));
    digitalWrite(shiftClockPin, LOW);
    /*digitalWrite(shiftClockPin, HIGH);
    digitalWrite(shiftClockPin, LOW);*/
    
  }
  if (last) {
    digitalWrite(latchClockPin, HIGH);
    digitalWrite(latchClockPin, LOW);
    digitalWrite(serialInputPin, LOW);
  }
}


void pulseClock(void) {
  digitalWrite(shiftClockPin, HIGH);
  delayMicroseconds(100); 
  digitalWrite(shiftClockPin, LOW);
 
}


void writeHighAndLowNumber(uint8_t tens, uint8_t ones) {
  uint8_t segmentsTens = 0;
  uint8_t segmentsOnes = 0;

switch (tens){
    case 0: segmentsTens = 0b01111110; break;
    case 1: segmentsTens = 0b00110000; break;
    case 2: segmentsTens = 0b01101101; break;
    case 3: segmentsTens = 0b01111001; break;
    case 4: segmentsTens = 0b00110011; break;
    case 5: segmentsTens = 0b01011011; break;
    case 6: segmentsTens = 0b01011111; break;
    case 7: segmentsTens = 0b01110000; break;
    case 8: segmentsTens = 0b01111111; break;
    case 9: segmentsTens = 0b01111011; break;
    default: segmentsTens = 0; break; }

    switch (ones){
    case 0: segmentsOnes = 0b01011111; break;
    case 1: segmentsOnes = 0b00010001; break;
    case 2: segmentsOnes = 0b00101111; break;
    case 3: segmentsOnes = 0b00111011; break;
    case 4: segmentsOnes = 0b01110001; break;
    case 5: segmentsOnes = 0b01111010; break;
    case 6: segmentsOnes = 0b01111110; break;
    case 7: segmentsOnes = 0b00010011; break;
    case 8: segmentsOnes = 0b01111111; break;
    case 9: segmentsOnes = 0b01111011; break;
    default: segmentsOnes = 0; break; }

  //digitalWrite(shiftClockPin, HIGH);
  writeByte(segmentsTens, false);
  //pulseClock();
  //digitalWrite(shiftClockPin, LOW);
  
  //digitalWrite(shiftClockPin, HIGH);
  writeByte(segmentsOnes, true);
  //pulseClock();
  //digitalWrite(shiftClockPin, LOW);
}

void showResult(byte result) {
  Serial.print("Showing result: ");
  Serial.println(result);
  Serial.println();
  uint8_t tens = result / 10;
  uint8_t ones = result % 10;
  writeHighAndLowNumber(tens, ones);
  
}