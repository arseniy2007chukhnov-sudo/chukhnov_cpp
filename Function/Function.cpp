#include "Function.h"

Hiperbola::Hiperbola(double k1) {
	if (k1 != 0)
		k = k1;
}

double Hiperbola::find_y(double x) const {
	if (x != 0)
		return k / x;
}

double Hiperbola::find_min(double x1, double x2, double step = 0.001) const {
	double min = x1;
	for (x1, x1 <= x2, x1 += step) {
		if (x1 < min)
			min = x1;
	}
	return min;
}