#ifndef __Letra_h__
#define __Letra_h__

#include <iostream>
#include <cctype>

using namespace std;


/**
	@brief TDA Letra

	El TDA Letra representa una letra, junto con las repeticiones que se dan de esa letra y la puntuación
	que lleva asociada cada una de estas letras.

	El invariante de representación de esta clase viene dado por todos aquellos valores correctos, es decir,
	en el caso del carácter letra, las letras de la a-z y entre A-Z pero nada de caracteres cómo: comas, puntos,
	asteriscos...

*/
class Letra {
private:
	char letra;	
	int repeticiones;	 
	int puntuacion;	

public:
	/**
	 *	@brief Constructor por defecto de Letra
	 *
	 */
	Letra();

	/**
	 * @brief Constructor por parámetros de la clase Letra
	 * @param letra letra que se representa
	 * @param repeticiones Números de veces que aparece la letra
	 * @param puntuacion La puntuación asociada a la letra.
	 */
	Letra(char letra, int repeticiones, int puntuacion);

	/**
	 * @brief Método para extraer la letra (sólo el carácter)
	 * @return la letra (sólo el carácter)
	 */
	char getLetra() const;

	/**
	 * @brief Método para extraer el número de veces que se repite la letra 
	 * @return Número de apariciones de la letra
	 */
	int getRepeticiones() const;

	/**
	 * @brief Método para extraer la puntuación asociada a la letra
	 * @return La puntuación de la letra
	 */
	int getPuntuacion() const;

	/**
	 * @brief Método para asociar carácter a la letra
	 * @param letra El nuevo caracter que se dará a la letra
	 */
	void setLetra(char letra);

	/**
	 * @brief Método para incluir el número de apariciones de la letra
	 * @param repeticiones El nuevo número de apariciones de la letra
	 */
	void setRepeticiones(int repeticiones);

	/**
	 * @brief Método para incluir la puntuación de la letra
	 * @param puntuacion La nueva puntuación de la letra
	 */
	void setPuntuacion(int puntuacion);

	/**
	 * @brief Sobrecarga del operador <
	 * @param otra la letra con la que se compara
	 * @return true en caso de que nuestra letra sea menor que la otra (orden alfabético)
	 */
	bool operator<(const Letra &otra) const;

	/**
	 * @brief Sobrecarga del operador >
	 * @param otra la letra con la que se compara
	 * @return true en caso de que nuestra letra sea mayor que la otra (orden alfabético)
	 */

	bool operator>(const Letra &otra) const;

	/**
	 * @brief Sobrecarga del operador <=
	 * @param otra la letra con la que se compara
	 * @return true en caso de que nuestra letra sea menor igual que la otra (orden alfabético)
	 */

	bool operator<=(const Letra & otra) const;

	/**
	 * @brief Sobrecarga del operador >=
	 * @param otra la letra con la que se compara
	 * @return true en caso de que nuestra letra sea mayor igual que la otra (orden alfabético)
	 */

	bool operator>=(const Letra &otra) const;

	/**
	 * @brief Sobrecarga del operador ==
	 * @param otra la letra con la que se compara
	 * @return true en caso de que nuestra letra sea igual que la otra
	 */

	bool operator==(const Letra &otra) const;

	/**
	 * @brief Sobrecarga del operador !=
	 * @param otra la letra con la que se compara
	 * @return true en caso de que nuestra letra sea distinta que la otra
	 */

	bool operator!=(const Letra &otra) const;

	/**
	 * @brief Sobrecarga del operador de salida <<
	 * @param out Flujo de salida
	 * @param l Letra a la que se le da salida
	 * @return El flujo de salida que corresponda
	 */

	friend ostream& operator<<(ostream &out, const Letra l);

	/**
	 * @brief Sobrecarga del operador de entrada >>
	 * @param in Flujo de entrada
	 * @param l Letra a la que se le da entrada
	 * @return El flujo de entrada que corresponda
	 */

	friend istream& operator>>(istream &in, Letra &l);
};



#endif