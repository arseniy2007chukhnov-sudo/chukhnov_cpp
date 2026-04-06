#include <iostream>
#include "Date.h"
using namespace std;

int main()
{
    Date a(2000, 4, 1), b(2001, 12, 15, 23, 54, 33);
    cout << a - b << endl;
    a += 2;
    cout << a.day << endl;
    cout << a << endl;
    cout << b << endl;
    return 0;
}
