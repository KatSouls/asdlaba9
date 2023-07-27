#include <iostream>
#include <string>
#include <algorithm>
#include "Header.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	BinomialHeap *bh = new BinomialHeap();
	cout << "введите 10 элементов кучи: " << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << "введите " << i+1 << "-й элемент: ";
		int value;
		cin >> value;
		bh->insert(value);
	}
	bh->print();
	char ch;
	do
	{
		cout << "\nДоступные операции:" << endl;
		cout << "1. Добавить" << endl;
		cout << "2. Удалить" << endl;
		int choice;
		cout << "Введите номер: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			int ins;
			cout << "Введите целочисленный элемент для вставки: ";
			cin >> ins;
			bh->insert(ins);
			break;
		case 2:
			bh->extractMin();
			break;
		default:
			cout << "Неправильный символ!" << endl;
			break;
		}
		bh->print();
		cout << "\nПродолжить? (Введите y или n): " << endl;
		cin >> ch;
		if (ch == 'n') return 0;
	} while (ch == 'y');

	delete bh;

	system("pause");
	return 0;
}