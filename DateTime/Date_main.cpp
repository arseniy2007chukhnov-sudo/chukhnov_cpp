#include <iostream>
#include "Date.h"
#include <locale.h>
#include <algorithm>
using namespace std;
void quickSort(Date *arr, int first, int last);
int main()
{
    setlocale(LC_ALL, "Russian");
    Date a(2000, 4, 1), b(2001, 12, 15, 23, 54, 33);
    cout << "Тест разницы дат(Должно быть чуть меньше двух лет):" << endl;
    cout << a - b << endl;
    cout << "Тест(прибавление двух дней к дате a):" << endl;
    a += 2;
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

    cout << "Тест строкового конструктора: " << endl;
    Date d1("1995-01-01");
    Date d2("2023-12-25T14:30:00");
    cout << "Дата из строки (только дата): " << d1 << endl;
    cout << "Дата из строки (дата+время): " << d2 << endl;

    cout << "Быстрая сортировка дат из Приложения №1: " << endl;
    const int N = 26;
    Date dates[N] = {
        Date("1995-01-01"), Date("1994-04-26"), Date("1992-12-05"), Date("1994-07-12"), Date("1993-09-11"),
        Date("1992-07-21"), Date("1997-06-29"), Date("1997-02-06"), Date("1995-10-31"), Date("1993-08-18"),
        Date("1995-03-02"), Date("1996-08-12"), Date("1997-01-28"), Date("1995-12-15"), Date("1997-06-09"),
        Date("1993-11-10"), Date("1994-07-05"), Date("1993-06-06"), Date("1997-08-21"), Date("1996-09-28"),
        Date("1993-01-14"), Date("1992-10-02"), Date("1997-06-13"), Date("1996-08-18"), Date("1994-06-08"),
        Date("1993-05-04")
    };

    cout << "До сортировки:" << endl;
    for (int i = 0; i < N; ++i)
        cout << dates[i] << " ";
    cout << endl;

    quickSort(dates, 0, N - 1);

    cout << "После сортировки:" << endl;
    for (int i = 0; i < N; ++i) 
        cout << dates[i] << " ";
    cout << endl;
    return 0;
}
void quickSort(Date *arr, int first, int last) {
    if (first < last) {
        Date pivot = arr[last];
        int i = first - 1;
        for (int j = first; j <= last - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[last]);
        int pi = i + 1;
        quickSort(arr, first, pi - 1);
        quickSort(arr, pi + 1, last);
    }
}