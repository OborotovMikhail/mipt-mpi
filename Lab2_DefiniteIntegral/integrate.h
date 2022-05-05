#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "argStruct.h"

// Function that integrates the function given to it (single-thread version)
// xMin, xMax - integration limits
// stepsNum - number of integration steps between xMin and xMax
double integrate(double func(double x), double xMin, double xMax, int stepsNum);

// Thread version of integration function
// Arguments are described in the argStruct.h
void* integrateThread(void *arguments);