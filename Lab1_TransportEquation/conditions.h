#pragma once

#include <stdio.h>
#include <stdlib.h>

// Condition function for coodrinate x
// Returns the value of the U(x, 0) function
float conditionX(float x);

// Condition function for time T
// Returns the value of the U(0, t) function
float conditionT(float T);

// Initializes the conditions for coordinate x
void conditionsInit(float* data, int K, int M, float tau, float h);