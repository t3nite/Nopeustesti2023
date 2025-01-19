#ifndef TOPTEN_H
#define TOPTEN_H

struct TopTen {
  volatile int list[10];
  int index;
  bool flagShow;
  bool flagAdd;
  bool flagVictory;
  bool flagNew;
};

TopTen toptenShow(TopTen &topten);
TopTen toptenAdd(TopTen &topten, int points);
TopTen toptenInitialize(TopTen &topten);

#endif