#include "LevelManager.h"
#include "Arduino.h"
 
void levelup() {
  level++;
  Serial.print("Congratulations, you advance to the level ");
  Serial.println(level);
  pressedButtonsNum = 0;
  for(int i = 0; i < 4; i++) {
    buttonSequence[i] = 0;
  }
  
  if(turn_off_led_difficult>400){ //limitata velocita di spegnimnento
  	turn_off_led_difficult=turn_off_led_difficult-100;
  }
  game();
}

void gamelost() {
  Serial.println("You lost, game will restart");
  level = 1;
  pressedButtonsNum = 0;  
}