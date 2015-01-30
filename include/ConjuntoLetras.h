#ifndef __ConjuntoLetras_h__
#define __ConjuntoLetras_h__

#include <set>
#include <iostream>
#include "Letra.h"

using namespace std;

/**
   @brief T.D.A. CojuntoLetras
   
   El tipo de dato abstracto ConjuntoLetras representa una colección de objetos de la clase Letra, en que
   aparte del carácter que representa cada letra, tenemos asociado el número de veces que aparece y su puntuación
   en el caso de jugar con puntuación.

   El invariante de representación de esta clase viene dado por todos aquellos valores correctos, es decir,
   en el caso del carácter letra, las letras de la a-z y entre A-Z pero nada de caracteres cómo: comas, puntos,
   asteriscos...  
*/
class ConjuntoLetras {
private:
	set <Letra> letras;	

public:
	/**
	 *	@brief Método para añadir una letra al conjunto, paasando los parámetros correspondientes
	 *	@param letra La letra (carácter) que estamos añadiendo
	 *	@param repeticiones La cantidad de veces que se repite la letra
	 *	@param puntuacion La puntuación de ésta letra
	 */
	void agregarLetra(char letra, int repeticiones, int puntuacion);

	/**
	 *	@brief Método para añadir una letra al conjunto pasando una letra de la clase Letra
	 *	@param letra La letra (objeto de la clase Letra) que vamos a añadir
	 */
	void agregarLetra(Letra letra);

	/**
	 *	@brief Sobrecarga del operador de salida << 
	 *	@param out Flujo empleado para la salida
	 *  @param cl Conjunto que vamos a mandar al flujo de salida
	 *  @return Flujo de salida correspondiente
	 */

	friend ostream& operator<<(ostream &out, ConjuntoLetras &cl);

	/**
	 *	@brief Sobrecarga del operador de entrada >> 
	 *	@param in Flujo empleado para la entrada
	 *  @param cl Conjunto que vamos a mandar al flujo de entrada
	 *  @return Flujo de entrada correspondiente
	 */

	friend istream& operator>>(istream &in, ConjuntoLetras &cl);

	/**
	 *	@brief TDA iterator que recorre las letras (de la clase Letra) de la colección
	 */
	class iterator {
	private:

		set<Letra>::iterator it;	

	public:

		/**
		 * @brief Constructor por parámetros de iterador
		 * @param it un iterador de la clase set<Letra>
		 */
		iterator(set<Letra>::iterator it);

		/**
		 * @brief Referencia a la letra a la que apunta it
		 * @return Letra a la que apunta el iterador 
		 */
		Letra operator *();

		/**
		 *	@brief Incrementa en 1 la posición de it
		 *	@return Iterador que apunta a la siguiente posición
		 */
		iterator operator ++();

		/**
		 *	@brief Comprueba si dos iteradores son iguales
		 *	@param other El iterador con el que comparamos
		 * 	@return true si son iguales
		 */
		bool operator ==(iterator other);

		/**
		 *	@brief Comprueba si dos iteradores son distintos
		 *	@param other El iterador con el que comparamos
		 * 	@return true si son distintos
		 */
		bool operator !=(iterator other);
	};

	/**
	 * @brief Método para apuntar al primer elemento del conjunto
	 * @return Iterador al primer elemento del conjuntos de letras
	 */
	iterator begin();

	/**
	 * @brief Método para apuntar al final del conjunto
	 * @return Iterador al final del conjunto de letras
	 */
	iterator end();

};

#endif