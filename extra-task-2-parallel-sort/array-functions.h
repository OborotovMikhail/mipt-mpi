#pragma once

#include <stdio.h>
#include <stdlib.h>

// Verify that the array is sorted
int arrayVerify(int *array, size_t n);

// Print the array
void arrayPrint(int *array, size_t n);

// Initialize the array with integers from 1 to n
void arrayInit(int *array, size_t n);

// Shuffle elements of the array in random order
void arrayShuffle(int *array, size_t n);

// Copy the array elements to another array
void arrayCopy(int *array, int *arrayNew, size_t n);