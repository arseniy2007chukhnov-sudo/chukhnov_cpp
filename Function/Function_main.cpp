#include <iostream>
#include "Function.h"
#include <vector>
#include <locale.h>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    Hiperbola a(2);
    cout << a.find_y(2) << endl;
    Parabola b(3, 2, -5);
    cout << b.find_y(3) << endl;
    Exponenta c(4, 5, 6);
    cout << c.find_y(3) << endl;
    cout << "Минимум гиперболы a на промежутке от -1 до 5: " << a.find_min(-1, 5) << endl;
    cout << "Максимум гиперболы a на промежутке от -1 до 5: " << a.find_max(-1, 5) << endl;
    cout << "Минимум параболы b на промежутке от -5 до 10: " << b.find_min(-5, 10) << endl;
    cout << "Максимум параболы b на промежутке от -5 до 10: " << b.find_max(-5, 10) << endl;
    cout << "Минимум экспоненты c на промежутке от -4 до 3: " << c.find_min(-4, 3) << endl;
    cout << "Максимум экспоненты c на промежутке от -4 до 3: " << c.find_max(-4, 3) << endl;
    vector<Function*> Functions = { &a, &b, &c };
    for (int i = 0; i < 3; i++) {
        cout << "Интеграл ";
        Functions[i]->name();
        cout << " при x = 2: " << Functions[i]->integ(2) << endl;
        cout << "Дифференциал ";
        Functions[i]->name();
        cout << " при x = 5: " << Functions[i]->diff(2) << endl;
    }
    return 0;
}
