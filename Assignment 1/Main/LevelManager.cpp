#include "LevelManager.h"
#include "Arduino.h"
#include "ButtonManager.h"

int level = 1;
float factor = 1;
 
void levelup() {
  level++;
  Serial.print("Congratulations, you advance to the level ");
  Serial.println(level);
  clearButtonsSequence();
  factor = factor * 0.85;
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

float getFactor() {
  return factor;
}

int getLevel() {
  return level;
}