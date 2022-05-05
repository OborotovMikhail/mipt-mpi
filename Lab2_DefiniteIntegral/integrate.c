#include "integrate.h"

double integrate(double func(double x), double xMin, double xMax, int stepsNum) {
	double x, xStep, integral = 0;
	xStep = (xMax - xMin) / stepsNum; // Calculating x step value

	for (int i = 0; i < stepsNum; i++) {
		// Calculating one element and adding to the integral
		x = xMin + i * xStep;
		integral += (func(x) + func(x + xStep)) * xStep / 2;
	}

	return integral;
}

void* integrateThread(void *arguments) {
	struct timespec timeStart, timeEnd; // Starting and ending time points
	double timeElapsed; // Elapsed time variable
	clock_gettime(CLOCK_MONOTONIC, &timeStart); // Getting start time

	threadArgs *args = (threadArgs*) arguments; // Changing argument structure type

	double x, xStep;

	xStep = (args->xMax - args->xMin) / args->stepsNum; // Calculating x step value

	for (int i = 0; i < args->stepsNum; i++) {
		// Calculating one element and adding to the integral
		x = args->xMin + i * xStep;
		args->integral += (args->func(x) + args->func(x + xStep)) * xStep / 2;
	}

	clock_gettime(CLOCK_MONOTONIC, &timeEnd); // Getting End time

	timeElapsed = timeEnd.tv_sec - timeStart.tv_sec; // Converting time
	timeElapsed += (timeEnd.tv_nsec - timeStart.tv_nsec) / 1000000000.0; // Converting time
	args->time = timeElapsed;

	return(0); // Returning a value for the pthread_join to pick up
}