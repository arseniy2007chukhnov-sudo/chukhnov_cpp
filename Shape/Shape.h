#pragma once
#include <iostream>
#include <cmath>

struct point {
	double x, y;
};

class Shape {
public:
	virtual double calc_area() = 0;
	virtual double calc_perimeter() = 0;
	virtual void name() = 0;
	virtual ~Shape() {};
	double calc_dist(point pt1, point pt2);
};

class Circle: public Shape {
protected:
	point center;
	double rad;
public:
	Circle(point pt, double rad);
	double calc_area();
	double calc_perimeter();
	void name();
};

class Ellips : public Circle {
	double rad_a, rad_b;
public:
	Ellips(point pt, double r_a, double r_b);
	double calc_area();
	double calc_perimeter();
	void name();
};

class Triangle : public Shape {
	point pt1, pt2, pt3;
	double side1, side2, side3, p;
public: 
	Triangle(point point1, point point2, point point3);
	double calc_area();
	double calc_perimeter();
	void name();
};

class Rectangle : public Shape {
	point pt1, pt2, pt3, pt4;
	double side1, side2, side3, side4;
public:
	Rectangle(point point1, point point2, point point3, point point4);
	double calc_area();
	double calc_perimeter();
	void name();
};

class Polygonum : public Shape {
	point* pts;
	int n; 

public:
	Polygonum(point* points, int count);
	~Polygonum();

	double calc_area();
	double calc_perimeter();
	void name();
};