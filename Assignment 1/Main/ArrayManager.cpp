#include "ArrayManager.h"
#include "Arduino.h"

#define NUM_PIN 4
#define NUM_BUTTON 4
#define FIRST_PIN 2
#define LAST_PIN 5
#define RED 11
#define POT_PIN A0

//Generate random numbers, check duplicates and save
void generateRandom(int sequence[4])
{
  //Generates a seed based on an analog pin
  int seed = analogRead(POT_PIN);

  //Initializes the random number generator based on the seed read in the analog pin
  srand(seed);

  for (int i = 0; i < NUM_PIN; i++)
  {
    int r;
    do
    {
      r = rand() % (LAST_PIN - FIRST_PIN + 1) + FIRST_PIN;
    } while (isDuplicate(r, sequence, i)); //Keeps on generating until it gets to an unique number
    sequence[i] = r;
  }
}

//Checks if the number is already in the sequence
int isDuplicate(int num, int arr[], int size)
{
  for (int i = 0; i < size; i++)
  {
    if (arr[i] == num)
    {
      return 1; //Found a duplicate
    }
  }
  return 0; //No duplicates found
}

//Reverts the array and saves it in the destination array
void reverseArray(int arr[], int dest[], int length)
{
  int i, j; 
  for (i = length - 1, j = 0; i >= 0; i--, j++)
  {
    dest[j] = arr[i];
  }
}
