#ifndef __Letra_h__
#define __Letra_h__

#include <iostream>
#include <cctype>

using namespace std;


/**
	@brief TDA Letra

	Representa una letra dentro del juego letra, y por tanto tiene un caracter asociado a su cantidad
	de apariciones y la cantidad de puntos que daría en caso de ser usada en el juego

*/
class Letra {
private:
	char letra;	///< El caracter de la letra
	int repeticiones;	///< La cantidad de apariciones 
	int puntuacion;	///< La puntuación que da

public:
	/**
	 *	@brief Constructor por defecto de la clase Letra
	 *
	 */
	Letra();

	/**
	 * @brief Constructor de la clase Letra a partir de sus datos miembro
	 * @param letra El caracter asociado a la letra
	 * @param repeticiones La cantidad de apariciones de la letra
	 * @param puntuacion La puntuación que daría la letra
	 */
	Letra(char letra, int repeticiones, int puntuacion);

	/**
	 * @brief getter del caracter de la letra
	 * @return el caracter asociado a la letra
	 */
	char getLetra() const;

	/**
	 * @brief Getter de las apariciones de la letra
	 * @return el número de apariciones de la letra
	 */
	int getRepeticiones() const;

	/**
	 * @brief Getter de la puntuación de la letra
	 * @return el número de puntos de la letra
	 */
	int getPuntuacion() const;

	/**
	 * @brief Setter del caracter de la letra
	 * @param letter El nuevo caracter que se asociará a la letra
	 */
	void setLetra(char letra);

	/**
	 * @brief Setter de las apariciones de la letra
	 * @param letter El nuevo número de apariciones de la letra
	 */
	void setRepeticiones(int repeticiones);

	/**
	 * @brief Setter del caracter de la letra
	 * @param letter El nuevo caracter que se asociará a la letra
	 */
	void setPuntuacion(int puntuacion);

	/**
	 * @brief Método para comparar una letra con otra 
	 * @param otra la letra con la que se comparará this
	 * @return true en caso this < otra, false en otro
	 */
	bool operator<(const Letra &otra) const;

	/**
	* @brief Sobrecarga del operador >
	*/
	bool operator>(const Letra &otra) const;

	bool operator<=(const Letra & otra) const;

	bool operator>=(const Letra &otra) const;

	bool operator==(const Letra &otra) const;

	bool operator!=(const Letra &otra) const;

	friend ostream& operator<<(ostream &out, const Letra l);

	friend istream& operator>>(istream &in, Letra &l);
};



#endif