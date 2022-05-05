#include "integrate.h"

double integrate(double func(double x), double xMin, double xMax, int stepsNum) {
	double x, xStep, integral = 0;
	xStep = (xMax - xMin) / stepsNum; // Calculating x step value

	for (int i = 0; i < stepsNum; i++) {
		x = xMin + i * xStep;
		integral += (func(x) + func(x + xStep)) * xStep / 2;
	}

	return integral;
}

void* integrateThread(void *arguments) {
	threadArgs *args = (threadArgs*) arguments;
	printf("I am thread, my id is %d\n", args->id); // Debug

	return(0); // Returning a value for the pthread_join to pick up
}