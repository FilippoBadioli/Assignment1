#ifndef __LEVELMANAGER__
#define __LEVELMANAGER__

#include "Arduino.h"

void levelup();

void gamelost();

int checkDifficulty();

String printDifficulty();

float getFactor();

int getLevel();

float getDiffFactor();

#endif