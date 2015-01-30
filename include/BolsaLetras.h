#ifndef __BolsaLetras_h__
#define __BolsaLetras_h__

#include <vector>
#include "Letra.h"
#include "ConjuntoLetras.h"

using namespace std;

/**
 *  @brief T.D.A. BolsaLetras
 *  
 *  El tipo de dato abstracto BolsaLetras obtiene un vector en que se introduciden
 *  objetos de la clase Letra de un conunto de letras en función de la probabilidad
 *  que tenga cada letra de salir
 *
 *  El invariante de representación de esta clase viene dado por todos aquellos valores correctos, es decir,
 *  en el caso del carácter letra, las letras de la a-z y entre A-Z pero nada de caracteres cómo: comas, puntos,
 *  asteriscos... 
 *  
*/

class BolsaLetras {
private:
	vector <Letra> bolsa;

public:
	/**
	 *	@brief 	Constructor por parámetros de BolsaLetras
	 *	@param	letras Conjunto de letras del que se sacan las letras en función a su probabilidad
	 */
	BolsaLetras(ConjuntoLetras letras);

	/**
	 *	@brief	Método para obtener el vector con letras aleatorias
	 *	@param 	n Número de letras que tendrá el vector
	 *	@return Obtenemos un vector con n letras aleatorias
	 */
	vector <Letra> obtenerLetras(int n);
};

#endif