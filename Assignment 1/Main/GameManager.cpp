#include "GameManager.h"
#include "Arduino.h"

void game(){
  
  difficulty = checkDifficulty();
  
  //Spengo tutte le luci e metto in output "GO!"
  for(int i = 0; i < NUM_PIN; i++){
  	digitalWrite(pin[i], LOW);
  }
  Serial.println("GO!");
  Serial.print("Welcome to level ");
  Serial.print(level);
  Serial.print(", you are playing in ");
  Serial.print(printDifficulty());
  Serial.println(" mode");
  delay(5000);
  
  //Accendo i LED
  for(int i = 0; i < NUM_PIN; i++){
  	digitalWrite(pin[i], HIGH);
  }
  digitalWrite(RED, LOW);
  delay(2000);
  
  //Mescolare l'array
  generateRandom();
  
  //Invertire l'array
  reverseArray(sequence, expectedSequence, 4);
  
  for(int i = 0; i<NUM_PIN; i++){
    Serial.println(sequence[i]);
  }
  
  //Spegnimento dei LED uno alla volta
  for(int i = 0; i<NUM_PIN; i++){
    delay(200);
    int j = sequence[i];
    digitalWrite(j, LOW);
    delay(turn_off_led_difficult); //modificando questo i led si spengono piu velocemente
  } 
 
 
  /*Pressione pulsanti e memorizzazione ordine*/
  
  int buttonIndex = 0;
  while(pressedButtonsNum < 4 && solutionTime < 10000) {
      if(debounceButton(buttonState1, 6) == HIGH && buttonState1 == LOW) {
      	buttonSequence[buttonIndex++] = 2;
        pressedButtonsNum++;
      }
      if(debounceButton(buttonState2, 7) == HIGH && buttonState2 == LOW) {
      	buttonSequence[buttonIndex++] = 3;
        pressedButtonsNum++;
      }
      if(debounceButton(buttonState3, 8) == HIGH && buttonState3 == LOW) {
      	buttonSequence[buttonIndex++] = 4;
        pressedButtonsNum++;
      }
      if(debounceButton(buttonState4, 9) == HIGH && buttonState4 == LOW) {
      	buttonSequence[buttonIndex++] = 5;
        pressedButtonsNum++;
      }
    for(int i=0;i<4;i++) {
      	Serial.println(buttonSequence[i]);
      }
      Serial.println("\n");
  }
  
  //Controllo sequenze e decisione risultato
  win = true;
  for(int i = 0; i < 4; i++) {
    if(buttonSequence[i] != expectedSequence[i]) {
      win = false;
    }
  }
  if(win) {
    levelup();
  }
  else {
    gamelost();
  } 
}