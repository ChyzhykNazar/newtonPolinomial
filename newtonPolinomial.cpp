/*Для функції f (x) = sin (x) + x скласти таблицю значень.
На основі складеної таблиці побудувати інтерполяційний поліном Ньютона. Порівняти значення інтерполяційних
поліномів в точках х = -7,7; -5,5; -2,2; зі значеннями точної функції, оцінити точність наближення.*/

/*For function f(x) = sin (x) + x entered table.
Newton interpolation polynomial are initiated on the basis of the compiled table. Compare the values ​​of interpolation
polinomial in dot's x = х = -7,7; -5,5; -2,2; with the values ​​of the exact function, estimate the accuracy of the approximation.*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

//function
double func(double x) {
	return sin(x) + x;
}

//output of vector elements for solved methods
void print(vector<double> vec, vector<double> x) {
	for (int i = 0; i < vec.size(); i++) {
		cout << "Solution in point: " << x[i] << " = " << vec[i] << endl;
	}
	cout << endl;
}

//output of vector elements
void print(vector<double> vec) {
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}
	cout << endl;
}

//output of error between the exact and found value
void eps(vector<double> vec, vector<double> x) {
	for (int i = 0; i < vec.size(); i++) {
		cout << "Precision in point: " << x[i] << " = " << setw(10) << abs(abs(vec[i]) - abs(func(x[i]))) << endl;
	}
}

//Newton Polinomial without step
void polinomNewton(vector<double> x, vector<double> _x, vector<double> _y) {
	cout << endl << "________Answer method of Newton multipliers________________" << endl;
	vector<double> result;
	vector<double> temp;
	int size = _y.size();
	double** difor = new double* [size];
	for (int i = 0; i < size; i++) {
		difor[i] = new double[size + 1];
	}
	for (int i = 0; i < size; i++) {
		difor[0][i] = _y[i];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 1; j < size - i; j++) {
			difor[i + 1][j - 1] = (difor[i][j - 1] - difor[i][j]) / (_x[j - 1] - _x[j + i]);	
		}
	}
	for (int j = 0; j < size; j++) {
		temp.push_back(difor[j][0]);						
	}
	for (int j = 0; j < size; j++) {
		delete[] difor[j];							
	}
	for (int i = 0; i < x.size(); i++) {
		double sum = temp[0];
		for (int j = 1; j < size; j++) {
			double mul = 1;
			for (int k = 0; k < j; k++) {
				mul *= (x[i] - _x[k]);
			}
			sum += temp[j] * mul;
		}
		result.push_back(sum);
	}
	print(result, x);
	eps(result, x);
}

int main()
{
	double xTemp;
	double yTemp;
	vector<double> _x;
	vector<double> _y;
	vector<double> x;
	ifstream file("data.txt");
	while (!file.eof()) {
		file >> xTemp >> yTemp;
		_x.push_back(xTemp);
		_y.push_back(yTemp);
	}
	file.close();
	ifstream fileEx("newtonPolinomial.txt");
	while (!fileEx.eof()) {
		fileEx >> xTemp;
		x.push_back(xTemp);
	}
	fileEx.close();
	cout << "x: ";
	print(_x);
	cout << "y: ";
	print(_y);
	cout << "Dots: ";
	print(x);
	cout << endl;
	polinomNewton(x, _x, _y);
}