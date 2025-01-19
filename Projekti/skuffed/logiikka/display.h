#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

extern const int resetPin;
extern const int shiftClockPin;
extern const int latchClockPin;
extern const int outEnablePin;
extern const int serialInputPin;

void initializeDisplay(void);
void writeByte(uint8_t byte, bool last);
void writeByte(uint8_t tens, uint8_t ones);
void writeHighAndLowNumber(uint8_t tens, uint8_t ones);
void showResult(byte result);
void pulseClock(void);

#endif
