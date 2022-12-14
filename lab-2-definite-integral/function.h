#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// A pointer to the "double func(double x)" function
// Used in the thread argument structure
typedef double (*funcPointer)(double);

// A function to be integrated
double func(double x);

// Derivative of the function to be integrated
// (used for deciding the intervals of integration)
double funcDerivative(double x);