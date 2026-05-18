#pragma once
#include <cmath>


class Function {
public:
	virtual double find_y(double x) const = 0;
	virtual double find_min(double x1, double x2, double step = 0.001) const = 0;
	virtual double find_max(double x1, double x2, double step = 0.001) const = 0;
	virtual double integ(double x) const = 0;
	virtual double diff(double x) const = 0;
	virtual ~Function() = default;
	virtual void name() = 0;
};


class Hiperbola : public Function {
	double k;
public:
	Hiperbola(double k1);
	double find_y(double x) const;
	double find_min(double x1, double x2, double step = 0.001) const;
	double find_max(double x1, double x2, double step = 0.001) const;
	double integ(double x) const;
	double diff(double x) const;
	void name();
};

class Parabola : public Function {
	double a, b, c;
public:
	Parabola(double a, double b, double c);
	double find_y(double x) const;
	double find_min(double x1, double x2, double step = 0.001) const;
	double find_max(double x1, double x2, double step = 0.001) const;
	double integ(double x) const;
	double diff(double x) const;
	void name();
};

class Exponenta : public Function {
	double a, b, c;
public:
	Exponenta(double a, double b, double c);
	double find_y(double x) const;
	double find_min(double x1, double x2, double step = 0.001) const;
	double find_max(double x1, double x2, double step = 0.001) const;
	double integ(double x) const;
	double diff(double x) const;
	void name();
};