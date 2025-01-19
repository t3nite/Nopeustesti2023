#include "sound.h"
#include <Arduino.h>


int buzzerPin = 7;

void soundInitialize() {
  pinMode(buzzerPin, OUTPUT);
  soundStart();
}

void buzzer(int iterations, int highDelay, int lowDelay) {
  unsigned char i;
  for (i=0; i<iterations; i++) {
    digitalWrite(buzzerPin, HIGH);
    delay(highDelay);
    digitalWrite(buzzerPin, LOW);
    delay(lowDelay);
  }
}

void buzzer(int iterations, int delay) {
  buzzer(iterations, delay, delay);
}


void soundStart() {
  int i;
  for (i=0; i<2; i++) {
    buzzer(35, 2);
    buzzer(20, 3);
  }
  buzzer(40, 2);
}

void soundTrue() {
  buzzer(10, 2);
}

void soundFalse() {
  buzzer(60, 8);
}

void soundLoss() {
  buzzer(45, 5);
  buzzer(35, 6);
  buzzer(50, 8);
}

void soundVictory() {
  int i;
  buzzer(45, 3);
  buzzer(32, 3);
  buzzer(80, 2);
  for (i=0; i<10; i++) {
    buzzer(50, 1);
    buzzer(50, 0);
  }
}
