#include "ButtonManager.h"
#include "Arduino.h"
#include "LevelManager.h"

#define B1 9
#define B2 8
#define B3 6
#define B4 7
#define DEBOUNCEDELAY 50.
#define NUM_BUTTON 4
#define DEFAULT_DELAY 170

const int TURNONTIME = 20000;
int pressedButtonsNum = 0;
int buttonSequence[4];
long lastDebounceTime = 0;



bool isB1Pressed(){
  if(digitalRead(B1) == HIGH){
    return true;
  }
  else {
    return false;
  }
}


bool genericButtonPressed() {
  return (digitalRead(B1) == HIGH || digitalRead(B2) == HIGH ||
          digitalRead(B3) == HIGH || digitalRead(B4) == HIGH);
}



bool debounceButton(int pin) {
  int buttonState = digitalRead(pin);
  if(millis() - lastDebounceTime > DEBOUNCEDELAY){
    if(buttonState == HIGH){
      lastDebounceTime = millis();
      return true;
    }
  }
  return false;
}

void clearButtonsSequence() {
  for(int i = 0; i < NUM_BUTTON; i++) {
    buttonSequence[i] = 0;
  }
  pressedButtonsNum = 0;
}

void getSequence() {
  int buttonIndex = 0;
  int startTime = millis();
  int elapsedTime = 0;
  while(pressedButtonsNum < NUM_BUTTON && elapsedTime < TURNONTIME * getFactor() * getDiff()) {
      if(debounceButton(B3) == HIGH ) {
      	buttonSequence[buttonIndex++] = 2;
        digitalWrite(2, HIGH);
        pressedButtonsNum++;
      }
      if(debounceButton(B4) == HIGH ) {
      	buttonSequence[buttonIndex++] = 3;
        digitalWrite(3, HIGH);
        pressedButtonsNum++;
      }
      if(debounceButton(B2) == HIGH ) {
      	buttonSequence[buttonIndex++] = 4;
        digitalWrite(4, HIGH);
        pressedButtonsNum++;
      }
      if(debounceButton(B1) == HIGH ) {
      	buttonSequence[buttonIndex++] = 5;
        digitalWrite(5, HIGH);
        pressedButtonsNum++;
      }
    for(int i=0;i<NUM_BUTTON;i++) {
      	Serial.println(buttonSequence[i]);
      }
      Serial.println("\n");
      elapsedTime = millis() - startTime;
      delay(DEFAULT_DELAY);
  }
}

bool checkButtonsSequence(int expectedSequence[NUM_BUTTON]) {
  for(int i = 0; i < NUM_BUTTON; i++) {
    if(buttonSequence[i] != expectedSequence[i]) {
      return false;
    }
  }
  return true;
}
