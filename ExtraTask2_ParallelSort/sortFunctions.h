#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "arrayFunctions.h"

#define UP 0
#define DOWN 1

void swap(int *a, int *b);

void bitonicSeqMerge(int *array, int start, int BseqSize, int direction);

void bitonicSeqSort(int *array, int start, int length, int direction);

void sortSequential(int *array, int length, int direction);

void bitonicPar(int start, int length, int *array, int direction, int m);