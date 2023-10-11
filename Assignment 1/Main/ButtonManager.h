#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H 

bool isB1Pressed();
bool genericButtonPressed();
bool debounceButton(bool previousState, int pin);
void clearButtonsSequence();
void getSequence();
bool checkButtonsSequence(int expectedSequence[4]);

#endif