#ifndef __ConjuntoLetras_cpp__
#define __ConjuntoLetras_cpp__

#include "ConjuntoLetras.h"

//////////////////////////////////////////////////////////////////
/////////////////////// Funciones publicas ///////////////////////
//////////////////////////////////////////////////////////////////

void ConjuntoLetras::agregarLetra(char letra, int repeticiones, int puntuacion){
	Letra nueva(letra, repeticiones, puntuacion);

	this->agregarLetra(nueva);
}

void ConjuntoLetras::agregarLetra(Letra letra){
	letras.insert(letra);
}


istream& operator>>(istream &in, ConjuntoLetras &letras){
	string basura;
	in >> basura;
	in >> basura;
	in >> basura;
	while(getline(in, basura)){
		
		Letra letra;
		in >> letra;
		letras.agregarLetra(letra);
	}

	return in;

}

ostream& operator<<(ostream &os, ConjuntoLetras &letras){
	
	ConjuntoLetras::iterator it = letras.begin(), end = letras.end();

	for(; it != end; ++it){
		os << *it << endl;
	}

	return os;
}

//////////////////////////////////////////////////////////////////
//////////////////////////// Iterador ////////////////////////////
//////////////////////////////////////////////////////////////////

ConjuntoLetras::iterator::iterator(set<Letra>::iterator it){
	this->it = it;
}

Letra ConjuntoLetras::iterator::operator*(){
	return *this->it;
}

ConjuntoLetras::iterator ConjuntoLetras::iterator::operator++(){
	return this->it++;
}

bool ConjuntoLetras::iterator::operator==(ConjuntoLetras::iterator other){
	return this->it == other.it;
}

bool ConjuntoLetras::iterator::operator!=(ConjuntoLetras::iterator other){
	return this->it != other.it;
}

//////////////////////////////////////////////////////////////////
/////////////////////// Funciones begin end //////////////////////
//////////////////////////////////////////////////////////////////

ConjuntoLetras::iterator ConjuntoLetras::begin(){
	set<Letra>::iterator it = this->letras.begin();
	return it;
}

ConjuntoLetras::iterator ConjuntoLetras::end(){
	set<Letra>::iterator it = this->letras.end();
	return it;
}
#endif