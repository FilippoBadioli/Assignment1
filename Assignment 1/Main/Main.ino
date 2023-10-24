/*
  - authors: Mattia Flamigni, Filippo Badioli
  - mail: mattia.flamigni4@studio.unibo.it, filippo.badioli@studio.unibo.it
  - date: 2020-10-15
  - summary: Main file for the Restore the Light game. It manages the game flow and the sleep mode.
*/

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

int turn_off_led_difficult = 800; // easy di default
int sequenza[4];
int fade = 5;
int brightness = 0;
bool wantGame = false; // settare a false di default
int prevButtonState = LOW;
bool isInDeepSleeping = false;
int solutionTime;

void pciSetup(byte pin) {
  *digitalPinToPCMSK(pin) |= bit(digitalPinToPCMSKbit(pin)); // enable pin
  PCIFR |= bit(digitalPinToPCICRbit(pin));                   // clear any outstanding interrupt
  PCICR |= bit(digitalPinToPCICRbit(pin));                   // enable interrupt for the group
}

// handle pin change interrupt for D8 to D13 here
ISR(PCINT0_vect) {
  digitalWrite(13, digitalRead(B2) and digitalRead(B1));
}
// handle pin change interrupt for D0 to D7 here
ISR(PCINT2_vect) {
  digitalWrite(13, digitalRead(B4) and digitalRead(B3));
}

void setup() {
  for (int i = 0; i < NUM_BUTTON; i++)
  {
    pciSetup(buttonPins[i]);
  }

  for (int i = 0; i < NUM_BUTTON; i++)
  {
    attachInterrupt(digitalPinToInterrupt(buttonPins[i]), wakeUp, LOW);
  }

  Serial.begin(9600);
  for (int i = 0; i < NUM_LEDS; i++)
  {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(i, LOW);
  }
  for (int i = 0; i < NUM_BUTTON; i++)
  {
    pinMode(buttonPins[i], INPUT);
  }

  pinMode(RED, OUTPUT);
}

void loop()
{
  // Turn off all LEDs
  for (int i = 0; i < NUM_LEDS; i++)
  {
    digitalWrite(ledPins[i], LOW);
  }

  int level = getLevel();

  if (level == 1)
  {
    wantGame = false;
    Serial.println("\nWelcome to the Restore the Light Game. Press Key B1 to Start");
    fadeFun();

    unsigned long startTime = millis();
    // Attendiamo 10 secondi per vedere se viene premuto un tasto
    while (millis() - startTime < 10000 && !wantGame)
    {
      fadeFun();
      wantGame = isB1Pressed();
      delay(10);
    }
  }

  // Se nessun tasto viene premuto, attiva la modalità sleep
  if (!wantGame)
  {
    digitalWrite(RED, LOW);
    delay(200);
    sleepNow();
  }

  // Se viene premuto un tasto, lampeggia X millisecondi e avvia il gioco
  if (wantGame)
  {
    for (int i = 500; i > 0; i--)
    {
      fadeFun();
      delay(5);
    }
    game();
  }
}


void wakeUp()
{
  wantGame = false;
}

void fadeFun()
{
  analogWrite(RED, brightness);
  brightness = brightness + fade;

  if (brightness == 255 || brightness == 0)
  {
    fade = -fade;
  }
}

void sleepNow()
{
  Serial.println("Sleeping");
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();

  for (int i = FIRST_BUTTON_PIN; i <= LAST_BUTTON_PIN; i++)
  {
    attachInterrupt(i, wakeUp, LOW);
  }

  sleep_mode();
  sleep_disable();
  Serial.println("Wake Up");

  for (int i = FIRST_BUTTON_PIN; i <= LAST_BUTTON_PIN; i++)
  {
    detachInterrupt(i);
  }
}