#include "ButtonManager.h"
#include "Arduino.h"

void isB1Pressed(){
  int b1 = digitalRead(9);
  if(b1==HIGH){
    Serial.println("pressed");
    wantGame = true;
     //Serial.println("PARTIAMO");
  }
}

bool genericButtonPressed(){
  if (digitalRead(9) == HIGH || digitalRead(8) == HIGH ||
      digitalRead(6) == HIGH || digitalRead(7) == HIGH) {
    wantGame = true; // Imposta la variabile wantGame a true se uno dei pulsanti viene premuto
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