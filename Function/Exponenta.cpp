#include "Function.h"
#include <iostream>

Exponenta::Exponenta(double a, double b, double c) : a(a), b(b), c(c) {}

double Exponenta::find_y(double x) const {
	return (a * exp(b * x + c));
}

double Exponenta::find_min(double x1, double x2, double step) const {
	double mini = find_y(x1);

	for (x1; x1 <= x2; x1 += step) {
		if (find_y(x1) < mini)
			mini = find_y(x1);
	}
	return mini;
}

double Exponenta::find_max(double x1, double x2, double step) const {
	double maxi = find_y(x1);

	for (x1; x1 <= x2; x1 += step) {
		if (find_y(x1) > maxi)
			maxi = find_y(x1);
	}
	return maxi;
}

double Exponenta::integ(double x) const {
	return (a * (1 / b) * exp(b * x + c));
}

double Exponenta::diff(double x) const {
	return (a * b * exp(b * x + c));
}

void Exponenta::name() {
	std::cout << "Ёкспонента" << std::endl;
}