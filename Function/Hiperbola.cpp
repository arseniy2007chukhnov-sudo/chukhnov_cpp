#include "Function.h"
#include <iostream>

Hiperbola::Hiperbola(double k1) {
	if (k1 != 0)
		k = k1;
}

double Hiperbola::find_y(double x) const {
	if (x != 0)
		return k / x;
}

double Hiperbola::find_min(double x1, double x2, double step) const {
	double mini = NAN;
	if (x1 != 0 and x2 != 0)
		mini = find_y(x1);
	else if (x1 == 0 and x2 != 0) {
		x1 += 0.001;
		mini = find_y(x1);
	}
	else if (x2 == 0 and x1 != 0) {
		x2 -= 0.001;
		mini = find_y(x1);
	}
	else
	{
		x1 += 0.001;
		x2 -= 0.001;
		mini = find_y(x1);
	}

	for (x1; x1 <= x2; x1 += step) {
		if (x1 == 0)
			continue;
		if (find_y(x1) < mini)
			mini = find_y(x1);
	}
	return mini;
}

double Hiperbola::find_max(double x1, double x2, double step) const {
	double maxi = NAN;
	if (x1 != 0 and x2 != 0)
		maxi = find_y(x1);
	else if (x1 == 0 and x2 != 0) {
		x1 += 0.001;
		double maxi = find_y(x1);
	}
	else if (x2 == 0 and x1 != 0) {
		x2 -= 0.001;
		double maxi = find_y(x1);
	}
	else
	{
		x1 += 0.001;
		x2 -= 0.001;
		double maxi = find_y(x1);
	}

	for (x1; x1 <= x2; x1 += step) {
		if (find_y(x1) > maxi)
			maxi = find_y(x1);
	}
	return maxi;
}

double Hiperbola::integ(double x) const{
	return (k * (log(abs(x))));
}

double Hiperbola::diff(double x) const{
	return -(k / (x * x));
}

void Hiperbola::name() {
	std::cout << "Гипербола" << std::endl;
}