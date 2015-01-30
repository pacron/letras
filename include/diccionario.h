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

	El TDA diccionario representa el conjunto de palabras válidas de un idioma y permite realizar
	comprobaciones recurrentes como si una palabra dada existe o no, cuántas palabras existen
	con un determinado número de letras...
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

		info (char letra, bool valida){
			this->letra = letra;
			this->valida = valida;
		}

		info(char letra){
			this->letra = letra;
			this->valida = false;
		}

		info(){
			this->letra = 0;
			this->valida = false;
		}
	};

	ArbolGeneral<info> palabras;

	typedef ArbolGeneral<info>::Nodo Nodo;

	/**
	 * @brief De entre los hijos de un nodo, devuelve el nodo más cercano por la izquierda a la letra
	 * @param letter La letra a la que acercarse por la izquierda
	 * @param node el nodo de cuyos hijos se busca encontrar el más cercano
	 * @return El nodo más cercano por la izquierda al nodo que debería contener la letra
	 */
	Nodo encontrarNodo(char letra, Nodo nod);

	/**
	 * @brief Crea o encuentra el nodo que corresponde a un caracter a partir del nodo especificado
	 * @param letter la letra a la que se le busca hogar como hija de node
	 * @param node El nodo en cuyos hijos se quiere situar la letra letter
	 * @return el nodo (creado o encontrado) en el que se situará la letra
	 */
	Nodo agregarLetra(char letra, Nodo nod);

	/**
	 *	@brief Crea un árbol que tenga como raiz un caracter letter y no tenga hijos
	 *	@param letter El caracter de la raiz del nuevo árbol
	 *	@return Un árbol que tenga como raiz el caracter letter y nada más
	 */
	ArbolGeneral<info> crearSubarbol(char letra) {
		info nuevo(letra);
		return ArbolGeneral<info>(nuevo);
	}

	/**
	 *	@brief Devuelve una lista con las palabras de cierto nivel de profundidad a partir de node
	 *	@param level La profundidad a la que buscar desde node
	 *	@param node El nodo desde el que buscar
	 *	@param base_string El prefijo que se añadirá a los caracteres encontrados para formar palabras válidas
	 *	@return Una lista con las palabras de tal profundidad
	 */
	list<string> palabrasProfundidad(int level, Nodo nod, string palabra_actual);

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
	 * @brief Añade una palabra al diccionario
	 * @param word La palabra que será añadida al diccionario
	 */
	void agregarPalabra(string word);

	/**
	 *	@brief Comprueba si una palabra esta en el diccionario
	 *	@param word La palabra cuya pertenencia al diccionario será comprobada
	 *	@return true si está, false si no está
	 */
	bool existe(string word);

	/**
	 * @brief Devuelve un vector con palabras de una longitud determinada
	 * @param longitud la longitud de las palabras que serán devueltas
	 * @return un vector con palabras de la longitud especificada
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
	vector<string> obtenerPalabrasMejorPuntuacion(const vector<Letra>& letters, map <char,int> puntuaciones, int &mejor_puntuacion);

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