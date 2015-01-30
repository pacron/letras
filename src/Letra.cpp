#ifndef __Letra_cpp__
#define __Letra_cpp__

#include <iostream>
#include "Letra.h"
#include <cstdlib>

Letra::Letra(){}

Letra::Letra(char letra, int repeticiones, int puntuacion){
	this->letra = letra;
	this->repeticiones = repeticiones;
	this->puntuacion = puntuacion;
}

char Letra::getLetra() const{
	return this->letra;
}

int Letra::getRepeticiones() const{
	return this->repeticiones;
}

int Letra::getPuntuacion() const{
	return this->puntuacion;
}

void Letra::setLetra(char letra){
	this->letra = letra;
}

void Letra::setRepeticiones(int repeticiones){
	this->repeticiones = repeticiones;
}

void Letra::setPuntuacion(int puntuacion){
	this->puntuacion = puntuacion;
}

bool Letra::operator<(const Letra &otra) const{
	return this->letra < otra.letra;	
}

bool Letra::operator>(const Letra &otra) const{
	return this->letra > otra.letra;
}

bool Letra::operator>=(const Letra &otra) const{
	return this->letra >= otra.letra;
}

bool Letra::operator<=(const Letra &otra) const{
	return this->letra <= otra.letra;
}

bool Letra::operator==(const Letra &otra) const{
	return this->letra == otra.letra;
}

bool Letra::operator!=(const Letra &otra) const{
	return this->letra != otra.letra;
}

ostream& operator<<(ostream &out, const Letra l){
	out << l.letra << " " << l.repeticiones << " " << l.puntuacion;

	return out;
}


istream& operator>>(istream &in, Letra &l){
	char letra;
	int repeticiones, puntuacion;

	in >> letra;
	in >> repeticiones;
	in >> puntuacion;

	l.letra = letra;
	l.repeticiones = repeticiones;
	l.puntuacion = puntuacion;

	return in;
}

#endif