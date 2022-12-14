#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "arrayFunctions.h"

#define UP 1
#define DOWN 0

void swap(int *a, int *b);

void bitonicSeqMerge(int *array, int start, int BseqSize, int direction);

void bitonicSeqSort(int *array, int start, int length, int direction);

void sortSequential(int *array, int length, int direction);

void sortParallel(int *array, int length, int direction, int subSection);

void* bitonicParSort(void *input);

void bitonicPar(int start, int length, int *array, int direction, int subSection);