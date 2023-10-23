#include "LevelManager.h"
#include "Arduino.h"
#include "ButtonManager.h"
#include "math.h"

#define CONS 0.85;
#define POT_VAL_MAX 1024
#define POT_STEP 256
#define RED 11

int level = 1;
float factor = 1;

//Function called when a game is won, increases the level count and modifies the time factor
void levelup() {
  level++;
  Serial.print("Congratulations, you advance to the level ");
  Serial.println(level);
  clearButtonsSequence();
  factor = factor * CONS;
}

//Function called when a game is lost, resets the level count
void gamelost() {
  Serial.print("Game over, your score is: ");
  Serial.println(level);
  level = 1;
  clearButtonsSequence();
  digitalWrite(RED, HIGH);
  delay(10000);
}

//Returns a string explaining what the current difficulty is
String printDifficulty() {
  switch (checkDifficulty())
  {
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

//checks the potentiometer value and translates it into a value ranging from 1 to 4
int checkDifficulty() {
  int diff = analogRead(A5);
  if (diff >= 0 && diff < POT_VAL_MAX)
  {
    return (diff / POT_STEP) + 1;
  }
}

//returns the decreasing time factor based on level
float getFactor() {
  return factor;
}

//returns the current level
int getLevel() {
  return level;
}

//Returns the decreasing time factor based on difficulty
float getDiffFactor() {
  float diffFactor = (1 / pow(checkDifficulty(), 0.30));
  return diffFactor;
}