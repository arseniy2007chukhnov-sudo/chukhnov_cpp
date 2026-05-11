#include "Shape.h"
using namespace std;
const double PI = acos(-1.0);

double Shape::calc_dist(point pt1, point pt2) {
	return sqrt(((pt2.x - pt1.x) * (pt2.x - pt1.x)) + ((pt2.y - pt1.y) * (pt2.y - pt1.y)));
}
Circle::Circle(point pt, double r) {
	center = pt;
	rad = r;
}
double Circle::calc_area() {
	return PI * rad * rad;
}
double Circle::calc_perimeter() {
	return PI * 2 * rad;
}
void Circle::name() {
	cout << "This is a Circle" << endl;
}


Ellips::Ellips(point pt, double r_a, double r_b) 
	: Circle(pt, 0)
{
	center = pt;
	if (r_a > r_b)
	{
		rad_a = r_a;
		rad_b = r_b;
	}
	else
	{
		rad_b = r_a;
		rad_a = r_b;
	}
}
double Ellips::calc_area() {
	return PI * rad_a * rad_b;
}
double Ellips::calc_perimeter() {
	double h = (((rad_a - rad_b) * (rad_a - rad_b)) / ((rad_a + rad_b) * (rad_a + rad_b)));
	return PI * (rad_a + rad_b) * (1 + (3 * h) / (10 + sqrt(4 - 3 * h)));
}
void Ellips::name() {
	cout << "This is an Ellips" << endl;
}


Triangle::Triangle(point point1, point point2, point point3) {
	pt1 = point1;
	pt2 = point2;
	pt3 = point3;
	side1 = calc_dist(pt1, pt2);
	side2 = calc_dist(pt2, pt3);
	side3 = calc_dist(pt3, pt1);
	p = (side1 + side2 + side3) / 2;
}
double Triangle::calc_area() {
	return sqrt(p * (p - side1) * (p - side2) * (p - side3));
}
double Triangle::calc_perimeter() {
	return side1 + side2 + side3;
}
void Triangle::name() {
	cout << "This is a Triangle" << endl;
}


Rectangle::Rectangle(point point1, point point2, point point3, point point4) {
	pt1 = point1;
	pt2 = point2;
	pt3 = point3;
	pt4 = point4;
	side1 = calc_dist(pt1, pt2);
	side2 = calc_dist(pt2, pt3);
	side3 = calc_dist(pt3, pt4);
	side4 = calc_dist(pt4, pt1);
}

double Rectangle::calc_area() {
	return side1 * side2;
}

double Rectangle::calc_perimeter() {
	return side1 + side2 + side3 + side4;
}

void Rectangle::name() {
	cout << "This is a Rectangle" << endl;
}

Polygonum::Polygonum(point* points, int count) {
	n = count;
	pts = new point[n];
	for (int i = 0; i < n; i++) {
		pts[i] = points[i];
	}
}

Polygonum::~Polygonum() {
	delete[] pts;
}

double Polygonum::calc_perimeter() {
	double per = 0;
	for (int i = 0; i < n; i++) {
		per += calc_dist(pts[i], pts[(i + 1) % n]);
	}
	return per;
}

double Polygonum::calc_area() {
	double area = 0;
	for (int i = 0; i < n; i++) {
		area += pts[i].x * pts[(i + 1) % n].y;
		area -= pts[(i + 1) % n].x * pts[i].y;
	}
	return abs(area) / 2.0;
}

void Polygonum::name() {
	cout << "This is a Polygonum" << endl;
}