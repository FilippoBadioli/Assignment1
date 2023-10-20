#include "GameManager.h"
#include "Arduino.h"
#include "LevelManager.h"
#include "ArrayManager.h"
#include "ButtonManager.h"

#define NUM_PIN 4
#define NUM_BUTTON 4
#define FIRST_PIN 2
#define LAST_PIN 5
#define RED 11

int TURNOFFTIME = 8000;
int sequence[4];
int expectedSequence[4];
int pin[] = {5, 4, 3, 2};
int button[] = {6, 7, 8, 9};
int difficulty;
bool win;

//Functions that manages all the proceeding of the game
void game()
{

  //Turns off all the leds and prints the current level and difficulty
  for (int i = 0; i < NUM_PIN; i++)
  {
    digitalWrite(pin[i], LOW);
  }
  Serial.println("GO!");
  Serial.print("Welcome to level ");
  Serial.print(getLevel());
  Serial.print(", you are playing in ");
  Serial.print(printDifficulty());
  Serial.println(" mode");
  delay(5000);

  //Turn on the green leds
  for (int i = 0; i < NUM_PIN; i++)
  {
    digitalWrite(pin[i], HIGH);
  }
  digitalWrite(RED, LOW);
  delay(2000);

  //Scrambles the array
  generateRandom(sequence);

  //Reverts the array
  reverseArray(sequence, expectedSequence, 4);

  //Turns off the leds one by one
  for (int i = 0; i < NUM_PIN; i++)
  {
    delay(TURNOFFTIME * getFactor() * getDiffFactor());
    int j = sequence[i];
    digitalWrite(j, LOW);
  }

  getSequence();

  //Check sequence and decides on the result
  win = checkButtonsSequence(expectedSequence);

  //If win is true than the game goes on the next level, else it resets
  if (win)
  {
    levelup();
  }
  else
  {
    gamelost();
  }
}
