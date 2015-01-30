#ifndef __BolsaLetras_h__
#define __BolsaLetras_h__

#include <vector>
#include "Letra.h"
#include "ConjuntoLetras.h"

using namespace std;

/**
   @brief T.D.A. BolsaLetras
   
   El tipo de dato abstracto BolsaLetras permite obtener vectores de letras aleatorias
   a partir de un ConjuntoLetras en el que se especifican las probabiliades de sacar
   cada una de tales letras.
  
*/

class BolsaLetras {
private:
	vector <Letra> bolsa;

public:
	/**
	 *	@brief 	Constructor de la clase BolsaLetras
	 *	@param	letras es el conjunto de letras del que se obtendrán las letras y sus respectivas probabilidades
	 */
	BolsaLetras(ConjuntoLetras letras);

	/**
	 *	@brief	Obtiene un vector con letras aleatorias de longitud n
	 *	@param 	n el número de letras aleatorias que se quiere obtener
	 *	@return Un vector con n letras aleatorias
	 */
	vector <Letra> obtenerLetras(int n);
};

#endif