#include "function.h"

#include <math.h>

double func(double x) {
	return sin(1 / x);
}

double funcDerivative(double x) {
	return (-cos(1 / x) / (x * x));
}