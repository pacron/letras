#ifndef __Letra_h__
#define __Letra_h__

#include <iostream>
#include <cctype>

using namespace std;


/**
* @brief TDA Letra
*
* El TDA Letra representa una letra, junto con las repeticiones que se dan de dicha letra y su puntuación
* asociada.
*/
/**
  * @page repConjunto Rep del TDA Arbol General
  *
  * @section invConjunto Invariante de la representación
  *
  * Una letra debe representar un caracter alfabético del alfabeto
  * en el que se esté jugando, y no puede contener otro tipo de 
  * caracter.
  *
  * @section faConjunto Función de abstracción
  *
  * Cada instancia de este TDA contiene un caracter alfabético,
  * con un número de repeticiones asociado y la puntuación que 
  * dicha letra recibe en un juego similar al scrabble.
  */
class Letra {
private:
	char letra;	
	int repeticiones;	 
	int puntuacion;	

public:
	/**
	* @brief Constructor por defecto de Letra.
	*
	* Crea una letra con los campos vacíos.
	*/
	Letra();

	/**
	* @brief Constructor por parámetros de la clase Letra.
	* @param letra letra que se representa.
	* @param repeticiones Números de veces que aparece la letra.
	* @param puntuacion La puntuación asociada a la letra.
	*/
	Letra(char letra, int repeticiones, int puntuacion);

	/**
	* @brief Método para extraer la letra (sólo el carácter).
	* @return La letra (sólo el carácter).
	*/
	char getLetra() const;

	/**
	* @brief Método para extraer el número de veces que se repite la letra.
	* @return Número de apariciones de la letra.
	*/
	int getRepeticiones() const;

	/**
	* @brief Método para extraer la puntuación asociada a la letra.
	* @return La puntuación de la letra.
	*/
	int getPuntuacion() const;

	/**
	* @brief Método para asociar carácter a la letra.
	* @param letra El nuevo caracter que se dará a la letra.
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
	 * @return Flujo de salida con la información necesaria.
	 */

	friend ostream& operator<<(ostream &out, const Letra l);

	/**
	 * @brief Sobrecarga del operador de entrada >>
	 * @param in Flujo de entrada
	 * @param l Letra a la que se le da entrada
	 * @return El flujo de entrada restante
	 */

	friend istream& operator>>(istream &in, Letra &l);
};



#endif