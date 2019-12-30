#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
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

MonticuloBinomial<int>* crearMonticulo(int n) {
	MonticuloBinomial<int>* m = new MonticuloBinomial<int>();

	for (int i = 0; i < n; i++) {
		int numero = rand() % 100;
		m->insertar(numero);
	}

	return m;
}

int main() {
	srand(time(NULL));

	//int n = 1000;
	//int elementos = 1000;
	//double t_total = 0;

	//MonticuloBinomial<int>* m = crearMonticulo(elementos);
	//for (int i = 0; i < n; i++) {
	//	LARGE_INTEGER frecuencia;
	//	LARGE_INTEGER ini;
	//	LARGE_INTEGER fin;

	//	QueryPerformanceFrequency(&frecuencia);
 //   	QueryPerformanceCounter(&ini);
	//	m->borraMin();
	//	QueryPerformanceCounter(&fin);
	//	double tiempo = (double)(fin.QuadPart - ini.QuadPart) / frecuencia.QuadPart * 1000; //

	//	cout << elementos << " elementos, iter: " << i << " Tiempo: " << tiempo << endl;
	//	t_total += tiempo;
	//	elementos--;

	//}
	//delete m;

	//cout << endl << "ELEMENTOS: " << elementos << ", TIEMPO MEDIO: " << t_total / n << endl;

	 ofstream archivo;
	 archivo.open("tiempos.dat");
	 archivo << "#   X   Y" << endl;

	 //archivo.open("tiempos.dat", ios::app);

	 int elementos;
	 int n = 1000;

	 for (elementos = 1; elementos < 1000; elementos += 10) {
		 double t_total = 0;

	 	for (int i = 0; i < n; i++) {
	 		MonticuloBinomial<int>* m1 = crearMonticulo(elementos);
			MonticuloBinomial<int>* m2 = crearMonticulo(elementos);

			LARGE_INTEGER frecuencia;
			LARGE_INTEGER ini;
			LARGE_INTEGER fin;

	 		QueryPerformanceFrequency(&frecuencia);
    		QueryPerformanceCounter(&ini);
			m1 = m1->unir(m1, m2);
	 		QueryPerformanceCounter(&fin);

			double tiempo = (double)(fin.QuadPart - ini.QuadPart) / frecuencia.QuadPart * 1000; //

	 		//cout << elementos << " elementos, iter: " << i << " Tiempo: " << tiempo << endl;
	 		t_total += tiempo;

	 		delete m1;
			delete m2;
	 	}

	 	cout << endl << "ELEMENTOS: " << elementos << ", TIEMPO MEDIO: " << t_total / n << endl;

	 	archivo << "  " << elementos << "   " << t_total / n << endl;
	 }

	 archivo.close();

	system("PAUSE");
	return 0;
}