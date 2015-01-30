#ifndef __ConjuntoLetras_h__
#define __ConjuntoLetras_h__

#include <set>
#include <iostream>
#include "Letra.h"

using namespace std;

/**
   @brief T.D.A. CojuntoLetras
   
   El tipo de dato abstracto ConjuntoLetras representa una colección de letras con información añadida relativa
   a la cantidad de apariciones de una tal letra y los puntos asignados si se jugara en modo Puntuación al juego
   letras.
*/
class ConjuntoLetras {
private:
	set <Letra> letras;	///< set en el que se guardarán las letras del conjunto

public:
	/**
	 *	@brief Añade una letra al conjunto dando sus propiedades
	 *	@param letter El caracter que se añadirá al conjunto
	 *	@param appearances La cantidad de apariciones de la letra
	 *	@param score La puntuación que daría utilizar esta letra
	 */
	void agregarLetra(char letra, int repeticiones, int puntuacion);

	/**
	 *	@brief Añade una letra al conjunto
	 *	@param letra La letra que se añadirá
	 */
	void agregarLetra(Letra letra);

	friend istream& operator>>(istream &in, ConjuntoLetras &cl);

	friend ostream& operator<<(ostream &out, ConjuntoLetras &cl);

	/**
	 *	@brief TDA iterator recorre las letras del conjunto
	 */
	class iterator {
	private:

		set<Letra>::iterator it;	///< Iterador del set asociado a ConjuntoLetras

	public:

		/**
		 * @brief Constructor de iterator
		 * @param iter un iterador de la clase set asociada
		 */
		iterator(set<Letra>::iterator it);

		/**
		 * @brief Referencia la Letra apuntada por el iterador
		 * @return la letra apuntada por el iterador
		 */
		Letra operator *();

		/**
		 *	@brief Incrementa la posición del iterador en 1
		 *	@return Un iterador que apunta a la siguiente posición
		 */
		iterator operator ++();

		/**
		 *	@brief Comprueba si dos iteradores son iguales
		 *	@param another El iterador con el que comparar
		 * 	@return true en caso de que sean iguales, false en cualquier otro caso
		 */
		bool operator ==(iterator other);

		/**
		 *	@brief Comprueba si dos iteradores son distintos
		 *	@param another El iterador con el que comparar
		 * 	@return true en caso de que sean distintos, false en cualquier otro caso
		 */
		bool operator !=(iterator other);
	};

	/**
	 * @brief Devuelve un iterador al primer elemento del conjunto
	 * @return Un iterador al primer elemento del conjunto
	 */
	iterator begin();

	/**
	 * @brief Devuelve un iterador al final del conjunto
	 * @return Un iterador al final del conjunto
	 */
	iterator end();

};

#endif