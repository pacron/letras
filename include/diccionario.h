#ifndef __Diccionario_h__
#define __Diccionario_h__

#include "ArbolGeneral.h"
#include <list>
#include <map>
#include <vector>
#include <set>
#include "Letra.h"

using namespace std;


/**
	@brief T.D.A Diccionario

	El TDA diccionario representa las palabras que podemos obtener de un idioma origen, y permite realizar
	comprobaciones tales cómo si una palabra existe o cuáles son las palabras de un tamaño determinado
	existentes en ese idioma. Se representa a través de un árbol general en el que en cada nodo viene dado
	por una estructura dada por una letra, y un bool que en caso de estar a true, nos indica que esa letra 
	es el final de alguna palabra.

	El invariante de representación podríamos rescatar el hecho de que las hojas siempre tienen que ser válidas
	(bool a true). En el caso de la struct info, destacar que el char letra sólo puede venir dado por letras correctas,
	es decir, entre a-z y entre A-Z pero no pueden poner asteriscos, puntos comas, etc

*/
class Diccionario {
private:
	/**
		@brief 	Esta estructura se usará para representar los caracteres dentro el arbol
				además de marcar si una palabra finaliza en tal posición
	*/
	struct info {
		char letra;
		bool valida;

		/**
		 * @brief Constructor por parámetros del struct info
		 * @param letra Letra que tendremos en la estructura
		 * @param valida Variable booleana que indica si la letra es o no válida  	
		*/

		info (char letra, bool valida){
			this->letra = letra;
			this->valida = valida;
		}

		/**
		 * @brief Constructor de la struct info a partir de una letra, poniendo válida a false
		 * @param letra Letra que tendremos en la estructura				
		*/

		info(char letra){
			this->letra = letra;
			this->valida = false;
		}

		/**
		 * @brief Constructor por defecto de la struct info				
		*/

		info(){}
	};

	ArbolGeneral<info> palabras;

	typedef ArbolGeneral<info>::Nodo Nodo;

	/**
	 * @brief Devuelve el nodo donde queremos insertar la letra
	 * @param letra Letra a la que nos acercamos
	 * @param nod Nodo de referencia
	 * @return Nodo donde queremos insertar la letra
	 */
	Nodo encontrarNodo(char letra, Nodo nod);

	/**
	 * @brief Método para saber (o crear) el nodo que se corresponde a un carácter
	 * @param letra Letra sobre la que realizamos la comprobación
	 * @param nod Nodo de referencia
	 * @return Nodo en que situamos la letra
	 */
	Nodo agregarLetra(char letra, Nodo nod);

	/**
	 *	@brief Método para crear un árbol en que sólo se tiene una ráiz con una letra
	 *	@param letra Letra que se va a insertar
	 *	@return El árbol que sólo tiene la raíz
	 */
	ArbolGeneral<info> crearSubarbol(char letra) {
		info nuevo(letra);
		return ArbolGeneral<info>(nuevo);
	}

	/**
	 *	@brief Método para obtener palabras que se encuentra a cierta profundidad
	 *	@param nivel La profundidad a la que buscamos
	 *	@param nod El nodo desde el que buscamos
	 *	@param palabra_actual El prefijo que se añadirá a los caracteres encontrados para formar palabras válidas
	 *	@return Una lista con las palabras de tal profundidad
	 */
	list<string> palabrasProfundidad(int nivel, Nodo nod, string palabra_actual);

	/**
	 *	@brief Devuelve una lista de palabras que solo contengan letras de un conjunto a partir de un nodo
	 *	@param letters Las letras que podrán utilizar las palabras devueltas
	 *	@param from El nodo desde el que se buscarán tales palabras
	 *	@param base_string El prefijo que se añadirá a los caracteres encontrados para formar palabras válidas
	 *	@return La lista especificada anteriormente
	 */
	list<string> obtenerPalabrasCoincidentes(multiset<char>& letras, Nodo actual, string palabra_actual);

public:
	/**
	 * @brief Constructor por defecto de la clase diccionario
	 */
	Diccionario();

	/**
	 * @brief Método para añadir una palabra al diccionario
	 * @param palabra La palabra que se añade
	 */
	void agregarPalabra(string palabra);

	/**
	 *	@brief Método que comprueba si una palabra existe en el diccionario
	 *	@param palabra La palabra que se comprueba
	 *	@return true si existe
	 */
	bool existe(string palabra);

	/**
	 * @brief Método que devuelven las palabras de una longitud dada
	 * @param longitud Longitud de la que buscamos las palabras
	 * @return Vector con las palabras de esa longitud
	 */
	vector<string> palabrasLongitud(int longitud);


	/**
	 * @brief Devuelve una lista con palabras que solo usen letras determinadas
	 * @param letters las letras que se podrán usar para formar las palabras
	 * @return un vector con las palabras pedidas
	 */
	vector<string> obtenerPalabras(const vector<Letra>& letters);

	/**
	 *	@brief Devuelve una lista con las mejores palabras que usen unas letras determinadas
	 *	@param letters Las letras que pueden usar las palabras
	 *	@param puntuador El elemento que dará una puntuación determinada a las palabras
	 *	@return un vector con las palabras pedidas
	 */
	vector<string> obtenerPalabrasMejorPuntuacion(const vector<Letra>& letters, map <char,int> puntuaciones);

	friend ostream& operator<<(ostream &out, const Diccionario &d);
	friend istream& operator>>(istream &in, Diccionario &d);
	/**
	 *	@brief TDA iterator Iterador sobre las palabras del diccionario en orden alfabético
	 */
	class iterator {
	private:
		string palabra;	///< La palabra que referencia el iterator
		ArbolGeneral<info>::const_iter_preorden it;	///< Iterador asociado del árbol

		/**
		 * @brief Apunta al iterador del árbol al siguiente nodo con una palabra válida
		 */
		void encontrarPalabraSiguiente();

	public:
		/**
		 * @brief Constructor por defecto del iterador
		 */
		iterator();

		/**
		 * @brief Constructor a partir del iterador de un árbol
		 * @param iter el iterador del árbol
		 */
		iterator(ArbolGeneral<info>::const_iter_preorden it);

		/**
		 * @brief Devuelve la palabra que referencia el iterador
		 * @return La palabra referenciada por el iterador
		 */
		string operator*();

		/**
		 * @brief Hace que el iterador apunte a la siguiente palabra
		 * @return El iterador apuntando a la siguiente palabra
		 */
		iterator &operator++();

		/**
		 * @brief Comprueba la igualdad entre dos iteradores
		 * @param i el iterador con el que comparar
		 * @return true si son iguales, false si no
		 */
		bool operator==(const iterator &other);

		/**
		 * @brief Comprueba la desigualdad de dos iteradores
		 * @param i el iterador con el que comparar
		 * @return true si son distintos, false si iguales
		 */
		bool operator!=(const iterator &i);

		friend class Diccionario;
	};

	/**
	 * @brief Devuelve un iterador a la primera palabra del diccionario
	 * @return un iterador a la primera palabra del diccionario
	 */
	iterator begin() const;

	/**
	 * @brief Devuelve un iterador que apunta al final del diccionario
	 * @return un iterador al final del diccionario
	 */
	iterator end() const;
};

#endif