#include <iostream>
#include <string>
#include <algorithm>
#include "Header.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	BinomialHeap *bh = new BinomialHeap();
	cout << "������� 10 ��������� ����: " << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << "������� " << i+1 << "-� �������: ";
		int value;
		cin >> value;
		bh->insert(value);
	}
	bh->print();
	char ch;
	do
	{
		cout << "\n��������� ��������:" << endl;
		cout << "1. ��������" << endl;
		cout << "2. �������" << endl;
		int choice;
		cout << "������� �����: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			int ins;
			cout << "������� ������������� ������� ��� �������: ";
			cin >> ins;
			bh->insert(ins);
			break;
		case 2:
			bh->extractMin();
			break;
		default:
			cout << "������������ ������!" << endl;
			break;
		}
		bh->print();
		cout << "\n����������? (������� y ��� n): " << endl;
		cin >> ch;
		if (ch == 'n') return 0;
	} while (ch == 'y');

	delete bh;

	system("pause");
	return 0;
}