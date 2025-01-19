#include "topten.h"
#include <Arduino.h>
#include "display.h"
#include "sound.h"


TopTen toptenShow(TopTen &topten) {
  /*Serial.print("TopTen: ");
  Serial.print(topten.index);
  Serial.print(" - ");
  Serial.println(topten.list[topten.index]);*/

  showResult(topten.list[topten.index]);

  if (topten.index < 9) {
    topten.index = topten.index + 1;
  } else {
    topten.index = 0;
    topten.flagShow = false;
    Serial.println();
  }

  return topten;
}

TopTen toptenAdd(TopTen &topten, int points) {
  int i = 9;

  if (points < topten.list[9]) {
    soundLoss();
    return topten;
  }
  
  while (i >= 0 && topten.list[i] < points) {
    topten.list[i + 1] = topten.list[i];
    i--;
  }

  topten.list[i + 1] = points;
  topten.flagVictory = true;

  soundVictory();

  return topten;
}

TopTen toptenInitialize(TopTen &topten) {
  for (int i=0; i<10; i++) {
    topten.list[i] = 0;
  }
  topten.index = 0;
  topten.flagShow = false;
  topten.flagAdd = false;
  topten.flagVictory = false;
}