#ifndef __BolsaLetras_cpp__
#define __BolsaLetras_cpp__

#include "BolsaLetras.h"
#include "ConjuntoLetras.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

BolsaLetras::BolsaLetras (ConjuntoLetras letras) {
	
    ConjuntoLetras::iterator it = letras.begin(), end = letras.end();
	
    for(;it != end; ++it){

        int repeticiones = (*it).getRepeticiones();

        for (int i = 0; i < repeticiones; ++i){
        	bolsa.push_back(*it);
        }
	}
}

vector <Letra> BolsaLetras::obtenerLetras(int n){

	vector <Letra> elegidas;
	srand(time(NULL));
	int size = this->bolsa.size();

	for(int i = 0; i < n; i++){

		int indice = rand() % size;
		elegidas.push_back(this->bolsa[indice]);
	}

	return elegidas;
}

#endif