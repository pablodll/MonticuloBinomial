#include <iostream>
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
	Nodo<int>* x1 = new Nodo<int>(2);
	Nodo<int>* x2 = new Nodo<int>(3);
	MonticuloBinomial<int>* m1 = new MonticuloBinomial<int>(x1);
	MonticuloBinomial<int>* m2 = new MonticuloBinomial<int>(x2);

	mostrar(m1->cabeza());
	mostrar(m1->minimo());
	//mostrar(m2->minimo());

	m1->insertar(1);
	mostrar(m1->cabeza());
	mostrar(m1->minimo());

	m1->insertar(3);
	mostrar(m1->cabeza());
	mostrar(m1->minimo());


	//mostrar(MonticuloBinomial<int>::unir(m1, m2)->minimo());
	//mostrar(m_fusion->minimo());
	//mostrar(m_fusion->minimo()->_hermano);

	// Nodo<int>* min = m->minimo();

	// mostrar(min);
	// m->decrecerClave(min, 2);
	// mostrar(min);

	system("PAUSE");
	return 0;
}