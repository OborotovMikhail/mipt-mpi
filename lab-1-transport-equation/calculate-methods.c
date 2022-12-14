#include "calculateMethods.h"

float func(float t, float x) { 
	return t * x;
}

void calcRectangle(float* data, int k, int m, int K, int M, float tau, float h) {
	if ((k <= K && m <= M) || (k != 0 && m != 0)) {
		if(tau != h) {
			data[k * (M + 1) + m] = func((k - 0.5)*tau , (m + 0.5)*h ) * 2 * tau * h + (h + tau) * data[(k - 1) * (M + 1) + m - 1] + (h - tau) * (data[(k - 1) * (M + 1) + m] + (tau-h)*data[k * (M + 1) + m - 1])/(h - tau);
		} else {
			data[k * (M + 1) + m] = 0;
		}
	} else {
		printf("Error calculating using rectangle method\n");
		exit(1);
	}
}