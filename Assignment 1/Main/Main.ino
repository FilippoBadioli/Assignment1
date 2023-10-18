// C++ code
#include <stdlib.h>
#include <time.h>
#include <avr/sleep.h>
#include "GameManager.h"
#include "ArrayManager.h"
#include "ButtonManager.h"
#include "LevelManager.h"

#define FIRST_BUTTON_PIN 6
#define LAST_BUTTON_PIN 9
#define NUM_BUTTON 4
#define RED 11
#define B1 9
#define B2 8
#define B3 6
#define B4 7

#define NUM_LEDS 4
#define FIRST_LED_PIN 2
#define LAST_LED_PIN 5
#define G1 2
#define G2 3
#define G3 4
#define G4 5

const int buttonPins[NUM_BUTTON] = {9, 8, 6, 7};
const int ledPins[NUM_LEDS] = {2, 3, 4, 5};

int turn_off_led_difficult = 800; //easy di default
int sequenza[4];
int fade = 5;
int brightness = 0;
bool wantGame = false; //settare a false di default
int prevButtonState=LOW;
bool isInDeepSleeping = false;
int solutionTime;

void pciSetup(byte pin)
{
  *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
  PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
  PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

ISR (PCINT0_vect) // handle pin change interrupt for D8 to D13 here
 {    
     digitalWrite(13,digitalRead(B2) and digitalRead(B1));
 }
ISR (PCINT2_vect) // handle pin change interrupt for D0 to D7 here
 {
     digitalWrite(13,digitalRead(B4) and digitalRead(B3));
 }  

void setup()
{

  pciSetup(B4);
  pciSetup(B3);
  pciSetup(B2);
  pciSetup(B1);

  for(int i = 0; i<NUM_BUTTON; i++){
    pciSetup(buttonPins[i]);
  }

  for(int i = 0; i<NUM_BUTTON; i++ ){
    attachInterrupt(digitalPinToInterrupt(buttonPins[i]), wakeUp, LOW);
  }
  
  Serial.begin(9600);
  for(int i=0; i<NUM_LEDS; i++){
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(i,LOW);
  }
  for(int i = 0; i<NUM_BUTTON; i++){
  	pinMode(buttonPins[i], INPUT);
  }
  
  pinMode(RED, OUTPUT);
  
  
}



void loop()
{
  for(int i = 0; i <= NUM_LEDS; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  if(getLevel() == 1) {
    wantGame=false;
    Serial.println("Welcome to the Restore the Light Game. Press Key B1 to Start");
    fadeFun();
    unsigned long startTime = millis();
    //trascorro i primi 10 secondi per vedere se viene premuto un tasto
    delay(200);
    while (millis() - startTime < 10000 && !wantGame) {
    fadeFun();
    wantGame = isB1Pressed();
    delay(10);
  }

  }
  
  
  //se non viene premuto un tasto, va in sleep mode
  if(wantGame==false){
    digitalWrite(RED, LOW);
    delay(200);
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
	wantGame=false;
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

  for(int i = FIRST_BUTTON_PIN; i<=LAST_BUTTON_PIN; i++ ){
    attachInterrupt(i, wakeUp, LOW);
  }

  sleep_mode();
  sleep_disable();
  Serial.println("Wake Up");

  for(int i = FIRST_BUTTON_PIN; i<=LAST_BUTTON_PIN; i++ ){
    detachInterrupt(i);
  }
}