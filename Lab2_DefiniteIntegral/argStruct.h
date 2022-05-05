#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "function.h"

// Structure of arguments passed to a thread
typedef struct threadArgs {
	int id; // Thread id
	funcPointer func; // Poiter to a function to be integrated
	double xMin;
	double xMax;
	int stepsNum;
	double integral; // The calculated integral (result)
} threadArgs;