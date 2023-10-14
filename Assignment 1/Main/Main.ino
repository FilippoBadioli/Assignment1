// C++ code
#include <stdlib.h>
#include <time.h>
#include <avr/sleep.h>
#include "GameManager.h"
#include "ArrayManager.h"
#include "ButtonManager.h"
#include "LevelManager.h"

#define RED 11

int turn_off_led_difficult = 800; //easy di default
int sequenza[4];
int fade = 5;
int brightness = 0;
bool wantGame = false; //settare a false di default
int prevButtonState=LOW;
bool isInDeepSleeping = false;
int solutionTime;

void setup()
{
  attachInterrupt(digitalPinToInterrupt(9), wakeUp, LOW);
  attachInterrupt(digitalPinToInterrupt(8), wakeUp, LOW);
  attachInterrupt(digitalPinToInterrupt(7), wakeUp, LOW);
  attachInterrupt(digitalPinToInterrupt(6), wakeUp, LOW);
  Serial.begin(9600);
  Serial.println();
  for(int i=2; i<6; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i,LOW);
  }
  for(int i = 6; i<10; i++){
  	pinMode(i, INPUT);
  }
  
  pinMode(RED, OUTPUT);
  
  
}



void loop()
{
  for(int i = 2; i < 6; i++) {
    digitalWrite(i, LOW);
  }
  if(getLevel() == 1) {
    wantGame=false;
    Serial.println("Welcome to the Restore the Light Game. Press Key B1 to Start");
    fadeFun();
    unsigned long startTime = millis();
    //trascorro i primi 10 secondi per vedere se viene premuto un tasto
    while (millis() - startTime < 10000 && !wantGame) {
    fadeFun();
    wantGame = isB1Pressed();
    delay(10);
}

  }
  
  
  //se non viene premuto un tasto, va in sleep mode
  if(wantGame==false){
    sleepNow();
  }
  
  //se premuto un qualsiasi tasto, lampeggia Xs e parte il gioco
  if(wantGame){
    for(int i=500; i>0; i--){
      fadeFun();
      delay(5);
    }
    game();
  }
}

void wakeUp(){
	wantGame=true;
}


void fadeFun(){
  analogWrite(RED, brightness);
  brightness=brightness + fade;
  
  if(brightness==255 || brightness == 0){
    fade = -fade;
  }
}

void sleepNow(){
  Serial.println("Sleeping");
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();

  attachInterrupt(9, wakeUp, LOW);
  attachInterrupt(8, wakeUp, LOW);
  attachInterrupt(7, wakeUp, LOW);
  attachInterrupt(6, wakeUp, LOW);

  sleep_mode();
  sleep_disable();
  Serial.println("Wake Up");
  detachInterrupt(9);
  detachInterrupt(8);
  detachInterrupt(7);
  detachInterrupt(6);
}