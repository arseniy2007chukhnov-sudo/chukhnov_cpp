#include "Function.h"
#include <iostream>

Parabola::Parabola(double a, double b, double c) : a(a), b(b), c(c) {}

double Parabola::find_y(double x) const {
	return (x * x * a + x * b + c);
}

double Parabola::find_min(double x1, double x2, double step) const {
	double mini = find_y(x1);

	for (x1; x1 <= x2; x1 += step) {
		if (find_y(x1) < mini)
			mini = find_y(x1);
	}
	return mini;
}

double Parabola::find_max(double x1, double x2, double step) const {
	double maxi = find_y(x1);

	for (x1; x1 <= x2; x1 += step) {
		if (find_y(x1) > maxi)
			maxi = find_y(x1);
	}
	return maxi;
}

double Parabola::integ(double x) const {
	return ((a *(x * x * x) / 3) + (b *(x * x) / 2) + (c * x));
}

double Parabola::diff(double x) const {
	return ((2 * a * x) + b);
}

void Parabola::name() {
	std::cout << "Парабола" << std::endl;
}