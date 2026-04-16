#include <iostream>
#include "Date.h"
#include <locale.h>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    Date a(2000, 4, 1), b(2001, 12, 15, 23, 54, 33);
    cout << "Тест разницы дат(Должно быть чуть меньше двух лет):" << endl;
    cout << a - b << endl;
    a += 2;
    cout << "Тест(прибавление двух дней к дате a):" << endl;

    cout << a.day << endl;
    cout << "Тест формата вывода:" << endl;

    cout << a << endl;
    cout << b << endl;
    cout << "Тест операторов сравнения:" << endl;
    cout << (a != b) << endl; // Эти операторы перегружены и проверять те, на которых они основаны нет смысла
    cout << (a >= b) << endl;
    cout << (a <= b) << endl;
    cout << "Тест оператора присваивания:" << endl;
    a = b;
    cout << (a == b) << endl; // Хотя тут проверяется и оператор сравнивания
    cout << "Тест вывод даты следующей Пасхи после даты c:" << endl;

    Date c(2026, 6, 12);
    cout << c.get_easter() << endl;
    return 0;
}
