#include <iostream>
#include "Line.h"
#include <locale.h>
#include <ctime>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
	cout << "Введите N(количество элементов) и k" << endl;
	int N, k;
	cout << "N = ";
	cin >> N;
	cout << "k = ";
	cin >> k;
	LineListCyc<int> joseph;
	joseph.insertFirst(1);
	LineListElem<int>* current = joseph.getStart();
	for (int i = 2; i <= N; i++) {
		joseph.insertAfter(current, i);
		current = current->getNext();
	}

	current = joseph.getStart();
	unsigned int start_t, end_t;

	start_t = clock();
	while (current->getNext() != current)
	{
		for (int i = 0; i < k-2; i++)
			current = current->getNext();

		joseph.deleteAfter(current);

		current = current->getNext();
	}
	end_t = clock();
	cout << "Ответ: " << joseph << endl;
	cout << "Выполнилось за: " << end_t - start_t << " ms";
    return 0;
}
