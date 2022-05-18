#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "arrayFunctions.h"

#define UP 0
#define DOWN 1

void mergeUp(int *array, size_t arraySize);

void mergeDown(int *array, size_t arraySize);

void sortSequential(int *array, size_t arraySize);

void swap(int *a, int *b);

void bitonicSeq(int start, int length, int *seq, int direction);

void bitonicPar(int start, int length, int *seq, int direction, int m);