#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure of arguments passed to a thread
typedef struct threadArgs {
	int id; // Thread id
	int* array; // Array pointer
	double time; // Time of the calculation
} threadArgs;