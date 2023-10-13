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

  //usando millis() fai trascorrere 10 secondi
  

    //int i = 100;
    for(int i = 1000; i>0 && wantGame==false; i--){
      fadeFun();
      wantGame = isB1Pressed();
      
      delay(10);
    }
  Serial.println("dovrebbe dormire");
  //se in 10 secondi non viene premuto alcun tasto, richiama la funzione sleepNow()
  if(wantGame==false){
    sleepNow();
  }
  
  
  
  wantGame=true;
  
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
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();

  attachInterrupt(9, wakeUp, LOW);

  sleep_mode();
  sleep_disable();
  Serial.println("Wake Up");
  detachInterrupt(9);
}