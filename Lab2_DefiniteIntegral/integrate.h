#pragma once

#include <stdio.h>
#include <stdlib.h>

// Function that integrates the function given to it
// xMin, xMax - integration limits
// stepsNum - number of integration steps between xMin and xMax
double integrate(double func(double x), double xMin, double xMax, int stepsNum);