#include "ButtonManager.h"
#include "Arduino.h"

bool buttonState1 = LOW;
bool buttonState2 = LOW;
bool buttonState3 = LOW;
bool buttonState4 = LOW;

int pressedButtonsNum = 0;
int buttonSequence[4];



bool isB1Pressed(){
  int b1 = digitalRead(9);
  if(b1==HIGH){
    Serial.println("pressed");
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

bool debounceButton(bool previousState, int pin) {
  bool state;
  previousState = digitalRead(pin);
  for(int counter = 0; counter < 20; counter++) {
    delay(1);
    state = digitalRead(pin);
    if(state != previousState){
      counter = 0;
      previousState = state;
    }
  }
  return state; 
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
  while(pressedButtonsNum < 4 && elapsedTime < 10000) {
      if(debounceButton(buttonState1, 6) == HIGH && buttonState1 == LOW) {
      	buttonSequence[buttonIndex++] = 2;
        pressedButtonsNum++;
      }
      if(debounceButton(buttonState2, 7) == HIGH && buttonState2 == LOW) {
      	buttonSequence[buttonIndex++] = 3;
        pressedButtonsNum++;
      }
      if(debounceButton(buttonState3, 8) == HIGH && buttonState3 == LOW) {
      	buttonSequence[buttonIndex++] = 4;
        pressedButtonsNum++;
      }
      if(debounceButton(buttonState4, 9) == HIGH && buttonState4 == LOW) {
      	buttonSequence[buttonIndex++] = 5;
        pressedButtonsNum++;
      }
    for(int i=0;i<4;i++) {
      	Serial.println(buttonSequence[i]);
      }
      Serial.println("\n");
      elapsedTime = millis() - startTime;
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
