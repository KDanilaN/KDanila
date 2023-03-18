#include <iostream>
#include "rational.h" 
using namespace std;
int main(){
	setlocale(LC_ALL, "Russian");
	int n;
	cout << "количество дробей " << endl;
	cin >> n;
	rational* mas = new rational[n];
	int a, b;
	for (int i = 0; i < n; i++){
		cout << "значения дроби " << i + 1 << endl;
		cin >> a >> b;
		mas[i].set(a, b);
	}
	cout << "\n";
	for (int i = 0; i < n; i++){
		cout << "дробь " << i + 1 << endl;
		mas[i].show();
	}
	cout << "\n";
	int i1, i2;
	cout << "сложение " << endl;
	cin >> i1 >> i2;
	i1 = i1 - 1;
	i2 = i2 - 1;
	cout << "\n";
	mas[i1].show();
	cout << " + ";
	mas[i2].show();
	cout << " = ";
	(mas[i1] + mas[i2]).show();
	cout << "\n";
	cout << "вычитание " << endl;
	cin >> i1 >> i2; i1 = i1 - 1; i2 = i2 - 1;
	cout << "\n";
	mas[i1].show();
	cout << " - ";
	mas[i2].show();
	cout << " = ";
	(mas[i1] - mas[i2]).show();
	cout << "\n";
	cout << "прибавления единицы " << endl;
	cin >> i1;
	i1 = i1 - 1;
	cout << "\n";
	mas[i1].show();
	cout << " + " << endl;
	cout << " = " << endl;
	rational xr = mas[i1];
	(++xr).show();
	cout << "\n";
	cout << "проверка на равенство " << endl;
	cin >> i1 >> i2;
	i1 = i1 - 1;
	i2 = i2 - 1;
	cout << "\n";
	mas[i1].show();
	cout << " == ";
	mas[i2].show();
	if (mas[i1] == mas[i2]) {
		cout << "равны" << endl;
	}
	else {
		cout << "не равны" << endl;
	}
	cout << "\n";
	cout << "сравнение " << endl;
	cin >> i1 >> i2;
	i1 = i1 - 1;
	i2 = i2 - 1;
	cout << "\n";
	mas[i1].show();
	cout << " > ";
	mas[i2].show();
	if (mas[i1] > mas[i2]) {
		cout << "2>1 " << endl;
	}
	else {
		cout << "1>2" << endl;
	}
	cout << "\n";
	delete[] mas;
	return 0;
}
