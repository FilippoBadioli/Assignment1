#include "ButtonManager.h"
#include "Arduino.h"
#include "LevelManager.h"

const int TURNONTIME = 10000;
bool buttonState1 = LOW;
bool buttonState2 = LOW;
bool buttonState3 = LOW;
bool buttonState4 = LOW;
int pressedButtonsNum = 0;
int buttonSequence[4];



bool isB1Pressed(){
  if(digitalRead(9) == HIGH){
    return true;
  }
  else {
    return false;
  }
}

bool genericButtonPressed(){
  if (digitalRead(9) == HIGH || digitalRead(8) == HIGH ||
      digitalRead(6) == HIGH || digitalRead(7) == HIGH) {
    return true;
  }
  return false;
}

long lastDebounceTime = 0;
long debounceDelay = 50;
bool debounceButton(bool previousState, int pin) {
  int buttonState = digitalRead(pin);
  if(millis() - lastDebounceTime > debounceDelay){
    if(buttonState == HIGH){
      lastDebounceTime = millis();
      return true;
    }
  }
  return false;
}

void clearButtonsSequence() {
  for(int i = 0; i < 4; i++) {
    buttonSequence[i] = 0;
  }
  pressedButtonsNum = 0;
}

void getSequence() {
  int buttonIndex = 0;
  int startTime = millis();
  int elapsedTime = 0;
  while(pressedButtonsNum < 4 && elapsedTime < TURNONTIME * getFactor()) {
      if(debounceButton(buttonState1, 6) == HIGH ) {
      	buttonSequence[buttonIndex++] = 2;
        digitalWrite(2, HIGH);
        pressedButtonsNum++;
      }
      if(debounceButton(buttonState2, 7) == HIGH ) {
      	buttonSequence[buttonIndex++] = 3;
        digitalWrite(3, HIGH);
        pressedButtonsNum++;
      }
      if(debounceButton(buttonState3, 8) == HIGH ) {
      	buttonSequence[buttonIndex++] = 4;
        digitalWrite(4, HIGH);
        pressedButtonsNum++;
      }
      if(debounceButton(buttonState4, 9) == HIGH ) {
      	buttonSequence[buttonIndex++] = 5;
        digitalWrite(5, HIGH);
        pressedButtonsNum++;
      }
    for(int i=0;i<4;i++) {
      	Serial.println(buttonSequence[i]);
      }
      Serial.println("\n");
      elapsedTime = millis() - startTime;
      delay(200);
  }
}

bool checkButtonsSequence(int expectedSequence[4]) {
  for(int i = 0; i < 4; i++) {
    if(buttonSequence[i] != expectedSequence[i]) {
      return false;
    }
  }
  return true;
}
