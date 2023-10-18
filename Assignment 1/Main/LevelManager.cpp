#include "LevelManager.h"
#include "Arduino.h"
#include "ButtonManager.h"
#include "math.h"

#define CONS 0.85;
#define POT_VAL_MAX 1024
#define POT_STEP 256

int level = 1;
float factor = 1;
 
void levelup() {
  level++;
  Serial.print("Congratulations, you advance to the level ");
  Serial.println(level);
  clearButtonsSequence();
  factor = factor * CONS;
}

void gamelost() {
  Serial.println("You lost, game will restart");
  level = 1;
  clearButtonsSequence();
}

String printDifficulty() {
  switch(checkDifficulty()) {
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
  if (diff >= 0 && diff < POT_VAL_MAX) {
    return (diff / POT_STEP) + 1;
  }

}

float getFactor() {
  return factor;
}

int getLevel() {
  return level;
}

float getDiff() {
  float diffFactor = (1 / pow(checkDifficulty(), 1/3));
  Serial.println(diffFactor);
  
  return diffFactor;
}