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
int pin[]={5, 4, 3, 2};
int button[]={6,7,8,9};
int difficulty;
bool win;

void game(){
  
  //Spengo tutte le luci e metto in output "GO!"
  for(int i = 0; i < NUM_PIN; i++){
  	digitalWrite(pin[i], LOW);
  }
  Serial.println("GO!");
  Serial.print("Welcome to level ");
  Serial.print(getLevel());
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
  generateRandom(sequence);
  
  //Invertire l'array
  reverseArray(sequence, expectedSequence, 4);

  for(int i = 0; i<NUM_PIN; i++){
    Serial.println(sequence[i]);
  }
  Serial.println(getFactor() * getDiff());
  //Spegnimento dei LED uno alla volta
  for(int i = 0; i<NUM_PIN; i++){
    delay(TURNOFFTIME * getFactor() * getDiff());
    Serial.println(getFactor());
    Serial.println("sium");
    int j = sequence[i];
    digitalWrite(j, LOW);
  } 
 
 
  /*Pressione pulsanti e memorizzazione ordine*/
  getSequence();
  
  //Controllo sequenze e decisione risultato
  win = checkButtonsSequence(expectedSequence);
  
  if(win) {
    levelup();
  }
  else {
    gamelost();
  }  
}

