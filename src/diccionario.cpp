#ifndef __Diccionario_cpp__
#define __Diccionario_cpp__

#include "diccionario.h"

//////////////////////////////////////////////////////////////////
/////////////////////// Funciones privadas ///////////////////////
//////////////////////////////////////////////////////////////////

Diccionario::Nodo Diccionario::encontrarNodo(char letra, Nodo nod){
	Nodo hijo_anterior = NULL, hijo_actual = nod->hijo;

	for(; hijo_actual != NULL && hijo_actual->etiqueta.letra <= letra; hijo_actual = hijo_actual->drcha){

		if (hijo_actual->etiqueta.letra == letra){
			return hijo_actual;
		} 

		hijo_anterior = hijo_actual;
	}

	if (hijo_anterior == NULL){
		return nod;
	}

	return hijo_anterior;
}

Diccionario::Nodo Diccionario::agregarLetra(char letra, Nodo nod){
	Nodo posible = encontrarNodo(letra, nod);

	if (posible == nod){

		ArbolGeneral<info> subarbol = crearSubarbol(letra);
		palabras.insertarHijoIzquierda(nod, subarbol);

		return nod->hijo;

	} else if (posible->etiqueta.letra == letra) {
		return posible;
	} 

	ArbolGeneral<info> subarbol = crearSubarbol(letra);
	palabras.insertarHermanoDerecha(posible, subarbol);

	return posible->drcha;
}

list<string> Diccionario::palabrasProfundidad(int level, Nodo nod, string palabra_actual){
	
	list<string> resultado;
	if (nod == NULL){

	} else if (level == 1 && nod->etiqueta.valida == true){
		resultado.push_back(palabra_actual);
	} else if (level > 1) {

		Nodo hijo_actual = nod->hijo;

		while(hijo_actual != NULL){

			char letra_actual = hijo_actual->etiqueta.letra;
			list<string> palabras_inferiores = palabrasProfundidad(level - 1, hijo_actual, palabra_actual + letra_actual);
			resultado.splice(resultado.end(), palabras_inferiores);
			hijo_actual = hijo_actual->drcha;
		}
	}
	return resultado;
}

//////////////////////////////////////////////////////////////////
/////////////////////// Funciones publicas ///////////////////////
//////////////////////////////////////////////////////////////////

Diccionario::Diccionario(){
	palabras.asignaRaiz(info());
}

void Diccionario::agregarPalabra(string palabra){
	Nodo actual = palabras.raiz();

	int size = palabra.size();
	for(int i = 0; i < size; i++){
		actual = agregarLetra(palabra[i], actual);
	}

	actual->etiqueta.valida = true;
}

bool Diccionario::existe(string palabra){
	Nodo actual = palabras.raiz();

	int size = palabra.size();
	for(int i = 0; i < size; i++){

		actual = encontrarNodo(palabra[i], actual);

		if (actual->etiqueta.letra != palabra[i]){
			return false;
		}

	}

	return actual->etiqueta.valida == true;
}

vector<string> Diccionario::palabrasLongitud(int longitud){
	Nodo raiz = palabras.raiz();
	
	list<string> palabras = this->palabrasProfundidad(longitud + 1, raiz, "");

	return vector<string>(palabras.begin(), palabras.end());
}


ostream& operator<<(ostream &out, const Diccionario &diccionario){

	Diccionario::iterator it = diccionario.begin(), end = diccionario.end();
	for(; it != end; ++it){

		out << *it << endl;

	}

	return out;
}

istream& operator>>(istream &in, Diccionario &diccionario){
	string palabra;
	while (getline(in, palabra)){
		diccionario.agregarPalabra(palabra);
	}

	return in;
}

vector<string> Diccionario::obtenerPalabrasMejorPuntuacion(const vector<Letra>& letras, map <char,int> puntuaciones){

	vector<string> palabras = obtenerPalabras(letras);
	vector<string> resultado;

	int puntuacion_maxima = 0;
	int size = palabras.size();

	for(int i = 0; i < size; ++i){

		int puntuacion_actual = 0;
		
		for (int j = 0; j < palabras[i].size(); ++j){
			char letra_actual = palabras[i][j];
			if(puntuaciones.find(letra_actual) != puntuaciones.end()){
				puntuacion_actual += puntuaciones[letra_actual];
			}
		}

		if (puntuacion_actual > puntuacion_maxima){
			resultado.clear();
			resultado.push_back(palabras[i]);

			puntuacion_maxima = puntuacion_actual;

		} else if (puntuacion_actual == puntuacion_maxima) {
			resultado.push_back(palabras[i]);
		}
	}
	return resultado;
}

vector<string> Diccionario::obtenerPalabras(const vector<Letra>& letras) {

	multiset<char> conjunto_letras;

	int size = letras.size();
	for(int i = 0; i < size; ++i)
		conjunto_letras.insert(letras[i].getLetra());

	list<string> palabras_validas = obtenerPalabrasCoincidentes(conjunto_letras, palabras.raiz(), "");

	return vector<string>(palabras_validas.begin(), palabras_validas.end());

}

list<string> Diccionario::obtenerPalabrasCoincidentes(multiset<char>& letras, Nodo actual, string palabra_actual) {

	list<string> resultado;

	if (actual == NULL)
		return resultado;

	if (actual->etiqueta.valida){
		resultado.push_back(palabra_actual);
	}

	Nodo hijo_actual = actual->hijo;

	while(hijo_actual != NULL){
		set<char>::iterator letra = letras.find(actual->etiqueta.letra);


		if (letra != letras.end()){	
			letras.erase(letra);	

			list<string> resultado_actual = obtenerPalabrasCoincidentes(letras, hijo_actual, palabra_actual + *letra);

			resultado.splice(resultado.end(), resultado_actual);

			letras.insert(hijo_actual->etiqueta.letra);
		}

		hijo_actual = hijo_actual->drcha;
	}

	return resultado;
}


//////////////////////////////////////////////////////////////////
//////////////////////////// Iterador ////////////////////////////
//////////////////////////////////////////////////////////////////

void Diccionario::iterator::encontrarPalabraSiguiente(){	
		do {
			++it;

			palabra = palabra.substr(0, it.getLevel() - 1);
			
			if (it.getLevel() != -1){
				palabra += (*it).letra;
			}
			
		} while (it.getLevel() != -1 && (*it).valida != true);		
}

Diccionario::iterator::iterator(){}

Diccionario::iterator::iterator(ArbolGeneral<info>::const_iter_preorden it){
	this->it = it;
}

string Diccionario::iterator::operator*(){
	return this->palabra;
}

Diccionario::iterator &Diccionario::iterator::operator++(){
	this->encontrarPalabraSiguiente();
	return *this;
}

bool Diccionario::iterator::operator==(const iterator &other){
	return this->it == other.it;
}

bool Diccionario::iterator::operator!=(const iterator &other){
	return this->it != other.it;
}

//////////////////////////////////////////////////////////////////
/////////////////////// Funciones begin end //////////////////////
//////////////////////////////////////////////////////////////////

Diccionario::iterator Diccionario::begin() const {
	iterator it(palabras.begin());
	it.palabra = "";
	++it;

	return it;
}

Diccionario::iterator Diccionario::end() const {
	
	iterator it(palabras.end());
	
	it.palabra = "";

	return it;
}

#endif