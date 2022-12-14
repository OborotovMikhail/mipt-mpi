#include "conditions.h"

float conditionX(float x) {
	return x;
}

float conditionT(float t) {
	return t;
}

void conditionsInit(float* data, int K, int M, float tau, float h) {
	for (int k = 0; k <= K ; k++) {
		data[k * (M + 1)] = conditionT(k * tau);
	}
	for (int m = 1; m <= M ; m++) {
		data[m] = conditionX(m * h);
	}
}