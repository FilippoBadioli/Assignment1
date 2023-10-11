// C++ code
#include <stdlib.h>
#include <time.h>
#include <avr/sleep.h>
#include "GameManager.h"
#include "ArrayManager.h"
#include "ButtonManager.h"
#include "LevelManager.h"

#define NUM_PIN 4
#define NUM_BUTTON 4
#define FIRST_PIN 2
#define LAST_PIN 5
#define RED 11

int turn_off_led_difficult = 800; //easy di default

int pin[]={5, 4, 3, 2};
int button[]={6,7,8,9};
int sequence[4];
int expectedSequence[4];
int sequenza[4];
int fade = 5;
int brightness = 0;
bool wantGame = false; //settare a false di default
int prevButtonState=LOW;
bool isInDeepSleeping = false;
int pressedButtonsNum = 0;
int buttonSequence[4];
int solutionTime;
int level;
int difficulty;

bool buttonState1 = LOW;
bool buttonState2 = LOW;
bool buttonState3 = LOW;
bool buttonState4 = LOW;

bool win;

void setup()
{
  attachInterrupt(digitalPinToInterrupt(9), wakeUp, RISING);
  attachInterrupt(digitalPinToInterrupt(8), wakeUp, LOW);
  attachInterrupt(digitalPinToInterrupt(7), wakeUp, LOW);
  attachInterrupt(digitalPinToInterrupt(6), wakeUp, LOW);
  level = 1;
  wantGame=false;
  Serial.begin(9600);
  for(int i=2; i<6; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i,LOW);
  }
  for(int i = 6; i<10; i++){
  	pinMode(i, INPUT);
  }
  
  pinMode(RED, OUTPUT);
  //analogWrite(11,HIGH);
  
  Serial.println("Welcome to the Restore the Light Game. Press Key B1 to Start");
  //srand(time(NULL));
  
  fadeFun();
}

void loop()
{
  if(isInDeepSleeping==false){
    //10s start
    for(int i = 1000; i>0 && wantGame==false; i--){
      fadeFun();
      isB1Pressed();
      delay(10);
    }
  }
  
  //deep sleeping
  digitalWrite(RED, LOW);
  isInDeepSleeping=true;
  
  //Serial.println(wantGame);
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  attachInterrupt(digitalPinToInterrupt(9), wakeUp, RISING);
  sleep_mode();
  sleep_disable();
  detachInterrupt(digitalPinToInterrupt(9));
  
  //se premuto un qualsiasi tasto, lampeggia Xs e parte il gioco
  if(wantGame){
    for(int i=500; i>0; i--){
      fadeFun();
      delay(5);
    }
  }

    if(wantGame==true){ //diventa true quando B1 viene premuto
  		game();
    }
}

void wakeUp(){
  Serial.println("Wake");
	wantGame=true;
}


void fadeFun(){
  analogWrite(RED, brightness);
  brightness=brightness + fade;
  
  if(brightness==255 || brightness == 0){
    fade = -fade;
  }
}

String printDifficulty() {
  switch(difficulty) {
    case 1:
    return "easy";
    break;
    
    case 2:
    return "medium";
    break;
    
    case 3:
    return "hard";
    break;
    
    case 4:
    return "impossible";
    break;
  }
}

int checkDifficulty() {
  int diff = analogRead(A5);
  
  if(diff >= 0 && diff <256) {
    return 1;
  }
  else if(diff >= 256 && diff < 512) {
    return 2;
  }
  else if(diff >= 512 && diff < 768) {
    return 3;
  }
  else if(diff >= 768 && diff < 1024) {
    return 4;
  }
}


