#include <iostream>
#include <Windows.h>
#include <time.h>
#include "MonticuloBinomial.h"
using namespace std;

void mostrar(Nodo<int>* x) {
	cout << "NODO: " << x << endl;
	cout << "Clave: " << x->_clave << endl;
	cout << "Grado: " << x->_grado << endl;
	cout << "Hermano: " << x->_hermano << endl;
	cout << "Padre: " << x->_padre << endl;
	cout << "Hijo: " << x->_hijo << endl;
	cout << endl;
}

int main() {
	//Nodo<int>* x1 = new Nodo<int>(2);
	//Nodo<int>* x2 = new Nodo<int>(3);
	//MonticuloBinomial<int>* m2 = new MonticuloBinomial<int>(x2);

	double t_total = 0;
	int j = 0;

	for (j = 0; j < 1000; j++) {
		MonticuloBinomial<int>* m1 = new MonticuloBinomial<int>();

		unsigned long long int start = GetTickCount();

		for (int i = 0; i < j; i++) {
			m1->insertar(i);
		}

		unsigned long long int end = GetTickCount();

		int time = end - start;
		t_total += time;
		cout << "N = " << j << ", TIME: " << time << "ms" << endl << endl;

		delete m1;
	}

	cout << "TOTAL TIME: " << t_total / j << "ms" << endl;

	system("PAUSE");
	return 0;
}