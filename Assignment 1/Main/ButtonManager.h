#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H

bool isB1Pressed();
bool debounceButton(int pin);
void clearButtonsSequence();
void getSequence();
bool checkButtonsSequence(int expectedSequence[4]);

#endif