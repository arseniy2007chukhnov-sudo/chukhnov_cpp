#include <iostream>
#include "Rational.h"

using namespace std;

int main()
{
    Rational a(1, 2), b(-1, 6);
    cout << "a=" << a << " b=" << b << " a+b=" << a + b << endl;
    cout << "a(" << a << ") *= b(" << b << ")" << endl;
    a *= b;
    cout << "a=" << a << " b=" << b << " a-b=";
    a -= b;
    cout <<a << endl;

    Rational c = 3;
    cout << "b=" << b << " c=" << c << " b/c=" << b / c << endl;
    return 0;
}
