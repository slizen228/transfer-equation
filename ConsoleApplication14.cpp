#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>


using namespace std;

double u(double x, double t) {
	return pow(x + 0.1, 2) - (sin(2 * M_PI * t)) / 2 + x - 3.5 * t;
}

double f(double x, double t) {
	return -M_PI * cos(2 * M_PI * t) - 3.164 + 0.56 * x;
}
double fi(double x) {
	return pow(x + 0.1, 2) + x;//u(x, 0)
}
double g1(double t) {
	return pow(0.1, 2) - 0.5 * (sin(2 * M_PI * t)) - 3.5 * t; //  u(0, t)
}

int main() {
	int N, J;
	ofstream file("value.txt");
	ofstream fout("value_function.txt");


	double tao = 0.005;
	double h;
	double a = 0.28;

	cout << "h>" << a * tao << endl;
	cin >> h;

	N = 1 / h;
	J = 1 / tao;

	double A = (a * tao) / h;
	double B = 1 - A;

	double* old_layer = new double[N + 1];
	double* new_layer = new double[N + 1];

	double cur, delta;
	double maxim = 0;

	for (int i = 0; i < N + 1; i++) {
		old_layer[i] = fi(h * i);
		file << old_layer[i] << " ";
		fout << u(h * i, 0) << " ";
	}
	file << endl;
	fout << endl;

	for (int j = 1; j < J + 1; j++) {
		new_layer[0] = g1(j * tao);
		file << new_layer[0] << " ";
		fout << u(0, tao * j) << " ";

		for (int k = 1; k < N + 1; k++) {
			new_layer[k] = B * old_layer[k] + A * old_layer[k-1] + f(k * h, (j-1) * tao) * tao;
			cur = u(h * k, tao * j);

			delta = abs(cur - new_layer[k]);
			if (delta > maxim) {
				maxim = delta;
			}

			file << new_layer[k] << " ";
			fout << cur << " ";
		}
		file << endl;
		fout << endl;
		for (int t = 0; t < N + 1; t++) {
			old_layer[t] = new_layer[t];
		}
	}

	cout << fixed << setprecision(6)<< maxim << endl;
	cout << (tao + h) << endl;
	delete[] old_layer;
	delete[] new_layer;
}