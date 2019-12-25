#ifndef BINOMIAL_H
#define BINOMIAL_H

#include <iostream>

/*
 * Nodo: Clase que implementa un nodo del monticulo binomial
*/
template <class T>
class Nodo {
public:
	// CONSTRUCTOR: crea un nodo vacio
	Nodo() : _padre(NULL), _hijo(NULL), _hermano(NULL), _grado(0) {}

	// CONSTRUCTOR: crea un nodo con clave
	Nodo(const T clave) : _clave(clave), _padre(NULL), _hijo(NULL), _hermano(NULL), _grado(0) {}

	// CONSTRUCTOR: crea un nodo con clave y padre
	Nodo(const T clave, Nodo<T>* padre) : _clave(clave), _padre(padre), _hijo(NULL), _hermano(NULL), _grado(0) {}

	// DESTRUCTOR
	~Nodo() {
		delete _hijo;
		delete _hermano;
	}

	/*
	 * intercambia_claves: Intercambia las claves de dos nodos
	 *                     (usada en decrecer_clave)
	*/
	static void intercambia_claves(Nodo<T>* x, Nodo<T>* y){
		T temp = y->_clave;
		y->_clave = x->_clave;
		x->_clave = temp;
	}
		
	T _clave;
	int _grado;
	Nodo<T>* _padre;
	Nodo<T>* _hijo;
	Nodo<T>* _hermano;
};

/*
 * MonticuloBinomial: Clase que implementa el monticulo binomial 
 * 				      formado por elementos de la clase Nodo
*/
template <class T>
class MonticuloBinomial {
private:
	Nodo<T>* _cabeza; // Puntero a la cabeza del monticulo
	Nodo<T>* _min; // Puntero al elemento minimo del momticulo

public:
	/*
	 * CONSTRUCTOR: Crea un monticulo binomial vacio
	*/
	MonticuloBinomial() : _cabeza(NULL), _min(NULL) {}

	/*
	 * CONSTRUCTOR: Crea un monticulo binomial con un elemento
	*/
	MonticuloBinomial(Nodo<T>* x) : _cabeza(x), _min(x) {}

	// DESTRUCTOR
	~MonticuloBinomial() {
		delete _cabeza;
		delete _min;
	}

	/*
	 * insertar: Inserta un nuevo elemento en el monticulo
	 *           Para ello crea un monticulo auxiliar con el elemento a insertar 
	 * 			 y lo une con el monticulo principal
	 * 
	 * Parametros: Clave a insertar
	 * Retorno: void
	*/
	void insertar(T clave){
		// Creamos un nodo con la clave a insertar (y todos sus punteros sin inicializar)
		Nodo<T>* x = new Nodo<T>(clave);

		// Creamos un monticulo auxiliar con el nuevo nodo
		MonticuloBinomial<T>* m_aux = new MonticuloBinomial<T>(x);
		
		// Unimos los dos monticulos
		MonticuloBinomial<T>* m_union = unir(this, m_aux);
		this->_cabeza = m_union->_cabeza;
		this->_min = m_union->_min;

		// Actualizamos el minimo
		if(_min->_clave > clave) {
			_min = x;
		}
	}

	/*
	 * minimo: Devuelve un puntero al minimo elemento del monticulo
	 * 
	 * Parametros: void
	 * Retorno: Puntero al minimo elemento del monticulo
	*/
	Nodo<T>* minimo(){
		return _min;
	}

	Nodo<T>* cabeza(){
		return _cabeza;
	}

	/*
	 * borraMin: Borra el elemento minimo del monticulo y devuelve su clave
	 * 			 Busca el nuevo minimo del monticulo
	 * 
	 * Parametros: void
	 * Retorno: Clave del minimo extraido
	*/
	T borraMin(){
		MonticuloBinomial<T> m = new MonticuloBinomial<T>();

	}

	/*
	 * decrecerClave: Decrece la clave indicada
	 * 
	 * Parametros: Puntero al nodo con la clave a decrecer, nuevo valor de la clave
	 * Retorno: void
	*/
	void decrecerClave(Nodo<T>* clave, T nueva_clave){
		// Si la clave nueva es mayor -> Error
		if(nueva_clave > clave->_clave){
			std::cerr << "ERROR: Nueva clave mayor que la anterior" << std::endl;
			return;
		}

		// Decrecemos la clave
		clave->_clave = nueva_clave;

		// Flotamos la nueva clave hasta que este en correcta relacion con sus hijos
		// (La clave debe ser menor que sus hijos)
		Nodo<T>* actual = clave;
		Nodo<T>* padre = actual->_padre;
		while(padre != NULL && actual->_clave < padre->_clave){
			// Intercambiamos las claves
			Nodo<T>::intercambia_claves(actual, padre);

			// Subimos al siguiente padre
			actual = padre;
			padre = actual->_padre;
		}
	}

	/*
	 * unir: Une dos monticulos en uno solo
	 * 
	 * Parametros: Primer monticulo de la union, segundo monticulo de la union
	 * Retorno: Monticulo union
	*/
	static MonticuloBinomial<T>* unir(MonticuloBinomial<T>* m1, MonticuloBinomial<T>* m2){
		// Creamos un nuevo monticulo surgido de la fusion de m1 y m2
		MonticuloBinomial<T>* m_union = fusion(m1, m2);

		// Si el nuevo monticulo es vacio -> fin de la union
		if(m_union->_cabeza == NULL){
			return m_union;
		}

		Nodo<T>* anterior = NULL;
		Nodo<T>* actual = m_union->_cabeza;
		Nodo<T>* siguiente = actual->_hermano;

		while(siguiente != NULL){
			// Caso 1: Dos arboles de dstinto grado seguidos
			// Caso 2: Tres arboles del mismo grado seguidos
			if((actual->_grado != siguiente->_grado) || 
				(siguiente->_hermano != NULL && siguiente->_hermano->_grado == actual->_grado)){
				anterior = actual;
				actual = siguiente;
			}
			// Caso 3: Dos arboles de mismo grado seguidos y clave del primero <= clave del segundo
			else if(actual->_clave <= siguiente->_clave){
				actual->_hermano = siguiente->_hermano;
				link(siguiente, actual);
			}
			// Caso 4: Dos arboles de mismo grado seguidos y clave del segundo > clave del primero
			else if(anterior == NULL){
				m_union->_cabeza = siguiente;
				link(actual, siguiente);
				actual = siguiente;
			}
			else{
				anterior->_hermano = siguiente;
				link(actual, siguiente);
				actual = siguiente;
			}
			siguiente = actual->_hermano; 
		}

		return m_union;
	}

private:
	/*
	 * link: une dos arboles binomiales 
	 *       (usada en la union de monticulos)
	 * 
	 * Parametros: Puntero a raiz de cada arbol
	 * Retorno: void
	*/	
	static void link(Nodo<T>* x, Nodo<T>* y){
		x->_padre = y;
		x->_hermano = y->_hijo;
		y->_hijo = x;
		y->_grado = y->_grado + 1;
	}

	/*
	 * fusion: Une los arboles de dos monticulos en uno solo
	 *         manteniendo el orden de los grados de cada arbol 
	 *         y el orden de las claves (de menor a mayor)
	 * 
	 *        (usada en la union de monticulos)
	 * 
	 * Parametros: Primer monticulo a unir, segundo monticulo a unir
	 * Retorno: Cabeza del monticulo fusionado
	*/
	static MonticuloBinomial<T>* fusion(MonticuloBinomial<T>* m1, MonticuloBinomial<T>* m2){
		MonticuloBinomial<T>* m_fusion = new MonticuloBinomial<T>(); // Monticulo resultante de la fusion

		Nodo<T>* actual = NULL; // Puntero al nodo que vamos a añadir a la fusion
		Nodo<T>* anterior = NULL; // Puntero al ultimo nodo que hemos añadido a la fusion
		Nodo<T>* siguiente = NULL; // Puntero al siguiente elemento a añadir a la fusion

		Nodo<T>* temp = NULL;

		// Elegimos la menor de las cabezas como la cabeza de la union
		if(m1->_cabeza->_grado <= m2->_cabeza->_clave){
			m_fusion->_cabeza = m1->_cabeza;
			m_fusion->_min = m_fusion->_cabeza; // Al ser el primer elemento que insertamos sera el minimo
			siguiente = m2->_cabeza;
		}
		else{
			m_fusion->_cabeza = m2->_cabeza;
			m_fusion->_min = m_fusion->_cabeza; // Al ser el primer elemento que insertamos sera el minimo
			siguiente = m1->_cabeza;
		}

		actual = m_fusion->_cabeza;

		while(siguiente != NULL) {

			// Si el nodo actual es de menor grado que el siguiente lo insertamos y pasamos al siguiente nodo
			if(actual->_grado <= siguiente->_grado){
				// Comprobamos si el nuevo nodo es menor que el minimo
				m_fusion->_min = (actual->_clave < m_fusion->_min->_clave) ? actual : m_fusion->_min;
				
				// Añadimos el nodo y pasamos al siguiente
				temp = actual->_hermano;
				actual->_hermano = siguiente;
				anterior = actual;
				actual = siguiente;
				siguiente = temp;
			}
			// Si el nodo actual es de mayor grado que el siguiente tenemos que meter el siguiente entre medias
			else{
				if(anterior != NULL){ // Si ya habiamos añadido un nodo anteriormente
					anterior->_hermano = siguiente;
				}
				else{ // Si solo habiamos añadido la cabeza
					m_fusion->_cabeza = siguiente;
				}

				// Comprobamos si el nuevo nodo es menor que el minimo
				m_fusion->_min = (siguiente->_clave < m_fusion->_min->_clave) ? siguiente : m_fusion->_min;

				temp = siguiente->_hermano;
				siguiente->_hermano = actual;
				anterior = siguiente;
				siguiente = temp;
			}
		}

		return m_fusion;
	}

};

#endif