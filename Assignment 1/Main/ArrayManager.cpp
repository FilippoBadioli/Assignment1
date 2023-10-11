#include "ArrayManager.h"
#include "Arduino.h"

/*generate, check duplicate and save*/
void generateRandom(){
  // Leggi il valore da un pin analogico (ad esempio A0)
  int seed = analogRead(A0);
  
  // Inizializza il generatore di numeri casuali con il valore letto dal pin analogico
  srand(seed);
  
  for (int i = 0; i < NUM_PIN; i++) {
    int r;
    do {
      r = rand() % (LAST_PIN - FIRST_PIN + 1) + FIRST_PIN;
    } while (isDuplicate(r, sequence, i)); // Continua a generare finché non si ottiene un numero unico
    sequence[i] = r;
  }
}

int isDuplicate(int num, int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == num) {
            return 1; // Trovato un duplicato
        }
    }
    return 0; // Nessun duplicato trovato
}

void reverseArray(int arr[], int dest[], int length) {
    int i, j;

    // Inverti l'array e salvalo nell'array di destinazione
    for (i = length - 1, j = 0; i >= 0; i--, j++) {
        dest[j] = arr[i];
    }
}
