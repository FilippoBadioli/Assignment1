#include "ButtonManager.h"
#include "Arduino.h"
#include "LevelManager.h"

#define B1 9
#define B2 8
#define B3 6
#define B4 7
#define DEBOUNCEDELAY 150.
#define NUM_BUTTON 4
#define DEFAULT_DELAY 170

const int TURNONTIME = 20000;
int pressedButtonsNum = 0;
int buttonSequence[4];
long lastDebounceTime = 0;
bool debug = false; //only for debug purpose

//Checks if the button called B1 gets pressed
bool isB1Pressed()
{
  return digitalRead(B1) == HIGH;
}

//Function that ignores the bouncing of buttons
bool debounceButton(int pin)
{
  int buttonState = digitalRead(pin);
  if (millis() - lastDebounceTime > DEBOUNCEDELAY)
  {
    if (buttonState == HIGH)
    {
      lastDebounceTime = millis();
      return true;
    }
  }
  return false;
}

//Function that clears the current cached sequence of buttons pressed
void clearButtonsSequence()
{ 
  memset(buttonSequence, 0, sizeof(buttonSequence));
  pressedButtonsNum = 0;
}


//Called to get in input the sequence of pressed buttons
void getSequence()
{
  const int buttonPins[NUM_BUTTON] = {B3, B4, B2, B1};
  const int buttonValues[NUM_BUTTON] = {2, 3, 4, 5};
  int buttonIndex = 0;
  int startTime = millis();
  int elapsedTime = 0;

  while (pressedButtonsNum < NUM_BUTTON && elapsedTime < TURNONTIME * getFactor() * getDiffFactor())
  {
    for (int i = 0; i < NUM_BUTTON; i++)
    {
      if (debounceButton(buttonPins[i]) == HIGH)
      {
        buttonSequence[buttonIndex++] = buttonValues[i];
        digitalWrite(buttonValues[i], HIGH);
        pressedButtonsNum++;
      }
      if(debug){
        Serial.println(buttonSequence[i]);
      }
    }

    elapsedTime = millis() - startTime;
    delay(DEFAULT_DELAY);
  }
}


//Checks if the sequence of pressed buttons is equal to the expected sequence
bool checkButtonsSequence(int expectedSequence[NUM_BUTTON])
{
  for (int i = 0; i < NUM_BUTTON; i++)
  {
    if (buttonSequence[i] != expectedSequence[i])
    {
      return false;
    }
  }
  return true;
}