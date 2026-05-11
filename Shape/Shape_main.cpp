#include "Shape.h"
#include <vector>
#include <locale.h>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    point a;
    a.x = 3;
    a.y = 3;
    Circle cir(a, 2); // Создаём круг с радиусом 2
    cir.name();
    cout << "Площадь круга cir: ";
    cout << cir.calc_area() << endl;
    cout << "Периметр круга cir: ";
    cout << cir.calc_perimeter() << endl;

    Ellips ell(a, 1, 3);
    ell.name();
    cout << "Площадь эллипса ell: ";
    cout << ell.calc_area() << endl;
    cout << "Периметр эллипса ell: ";
    cout << ell.calc_perimeter() << endl;

    point b, c;
    b.x = 6;
    b.y = 3;
    c.x = 4;
    c.y = 1;
    Triangle tri(a, b, c);
    tri.name();
    cout << "Площадь треугольника tri: ";
    cout << tri.calc_area() << endl;
    cout << "Периметр трекгольника tri: ";
    cout << tri.calc_perimeter() << endl;

    point d, e;
    d.x = 6;
    d.y = 1;
    e.x = 3;
    e.y = 1;
    Rectangle rect(a, b, d, e);
    rect.name();
    cout << "Площадь прямоугольника rect: ";
    cout << rect.calc_area() << endl;
    cout << "Периметр прямоугольника rect: ";
    cout << rect.calc_perimeter() << endl;


    point poly_pts[5] = {
    {0, 0},
    {4, 0},
    {5, 2},
    {2, 4},
    {0, 2}
    };
    Polygonum poly(poly_pts, 5);
    poly.name();
    cout << "Площадь многоугольника poly: ";
    cout << poly.calc_area() << endl;
    cout << "Периметр многоугольника poly: ";
    cout << poly.calc_perimeter() << endl;

    cout << "Проверка полиморфизма: " << endl;
    vector<Shape*> v = { &cir, &ell, &tri, &rect, &poly };
    for (int i = 0; i < size(v); i++) {
        v[i]->name();
    }
    return 0;
}

