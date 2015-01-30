#ifndef __ArbolGeneral_cpp__
#define __ArbolGeneral_cpp__

#include <cassert>
#include "ArbolGeneral.h"

//////////////////////////////////////////////////////////////////
/////////////////////// Funciones privadas ///////////////////////
//////////////////////////////////////////////////////////////////

template<class Tbase>
void ArbolGeneral<Tbase>::destruir(nodo *n){
	if (n == NULL)
		return;

	if (n->padre != NULL){
		nodo *anterior = n->padre->hijo;

		if (anterior == n){
			n->padre->hijo = n->drcha;
		} else {

			while (anterior->drcha != n){
				anterior = anterior->drcha;
			}

			anterior->drcha = n->drcha;

		}
	}

	nodo *hijo = n->hijo;

	while(hijo != NULL){
		nodo *siguiente = hijo->drcha;
		
		destruir(hijo);

		hijo = siguiente;
	}

	delete n;

}

template<class Tbase>
void ArbolGeneral<Tbase>::copiar(nodo *& dest, nodo *orig){
	dest->etiqueta = orig->etiqueta;

	if(orig->drcha != NULL){
		dest->drcha = new nodo;
		dest->drcha->padre = dest->padre;

		this->copiar(dest->drcha, orig->drcha);
	}
	
	if (orig->hijo != NULL){
		dest->hijo = new nodo;
		dest->hijo->padre = dest;

		this->copiar(dest->hijo, orig->hijo);
	}
}

template <class Tbase>
int ArbolGeneral<Tbase>::contar(const nodo *n) const {
	if (n == NULL)
		return 0;

	else {
		int resultado = 1;

		nodo *hijo_actual = n->hijo;

		while(hijo_actual != NULL){
			resultado += contar(hijo_actual);
			hijo_actual = hijo_actual->drcha;
		}


		return resultado;
	}
}

template<class Tbase>
bool ArbolGeneral<Tbase>::sonIguales(const nodo *n1, const nodo *n2) const {
	if (n1 == NULL && n2 == NULL){
		return true;
	}
	else if (n1 == NULL && n2 != NULL || n2 == NULL && n1 != NULL){
		return false;
	}

	else if (n1->etiqueta == n2->etiqueta) {
		Nodo hijo_1 = n1->hijo;
		Nodo hijo_2 = n2->hijo;

		while(hijo_1 != NULL || hijo_2 != NULL){

			if (sonIguales(hijo_1, hijo_2) == false){
				return false;
			}

			hijo_1 = hijo_1->drcha;
			hijo_2 = hijo_2->drcha;

		}

		return true;

	} 

	else  {
		return false;
	}
}

template <class Tbase>
void ArbolGeneral<Tbase>::escribeArbol(std::ostream &out, Nodo n) const{
    out << "n " << n->etiqueta << " ";
    Nodo *actual = n->hijo;
    while(actual != NULL){
        this->escribeArbol(out,actual);
        actual = actual->drcha;
    }
    out << "x ";
}

template <class Tbase>
void ArbolGeneral<Tbase>::leeArbol(std::istream &in, Nodo &nod){
    Nodo *actual = nod;
    char actual_token;

    while (in >> actual_token){
        if (actual_token == 'n'){
            Tbase etiqueta;
            in >> etiqueta;
            actual = actual->insertarHijoDerecha(etiqueta);
        }
        else if (actual_token == 'x'){
            actual = actual->padre;    
        } 
    }

    nod = nod->hijo;
    
}

//////////////////////////////////////////////////////////////////
/////////////////////// Funciones públicas ///////////////////////
//////////////////////////////////////////////////////////////////

template <class Tbase>
ArbolGeneral<Tbase>::ArbolGeneral() {
	this->laraiz = NULL;
}

template<class Tbase>
ArbolGeneral<Tbase>::ArbolGeneral(const Tbase &e) {
	this->laraiz = new nodo;
	this->laraiz->etiqueta = e;
	this->laraiz->padre = NULL;
	this->laraiz->hijo = NULL;
	this->laraiz->drcha = NULL;
}


template<class Tbase>
ArbolGeneral<Tbase>::ArbolGeneral(const ArbolGeneral<Tbase> &v){
	
	destruir(this->laraiz);
	this->laraiz = new nodo;
	this->copiar(this->laraiz, v.laraiz);
}

template<class Tbase>
ArbolGeneral<Tbase>::~ArbolGeneral(){
	destruir(this->laraiz);
}

template<class Tbase>
ArbolGeneral<Tbase> &ArbolGeneral<Tbase>::operator=(const ArbolGeneral<Tbase> &v){
	
	destruir(this->laraiz);
	copiar(this->laraiz, v.laraiz);
}

template<class Tbase>
void ArbolGeneral<Tbase>::asignaRaiz(const Tbase &e){

	destruir(this->laraiz);

	this->laraiz = new nodo;
	this->laraiz->padre = NULL;
	this->laraiz->hijo = NULL;
	this->laraiz->drcha = NULL;

	this->laraiz->etiqueta = e;
}

template<class Tbase>
typename ArbolGeneral<Tbase>::Nodo ArbolGeneral<Tbase>::raiz() const {
	return this->laraiz;
}

template<class Tbase>
typename ArbolGeneral<Tbase>::Nodo ArbolGeneral<Tbase>::hijoIzquierda(const Nodo n) const {
	return n->hijo;
}

template<class Tbase>
typename ArbolGeneral<Tbase>::Nodo ArbolGeneral<Tbase>::hermanoDerecha(const Nodo n) const {
	return n->drcha;
}

template<class Tbase> 
typename ArbolGeneral<Tbase>::Nodo ArbolGeneral<Tbase>::padre(const Nodo n) const {
	return n->padre;
}

template <class Tbase>
Tbase& ArbolGeneral<Tbase>::etiqueta(const Nodo n){
	return n->etiqueta;
}

template <class Tbase>
const Tbase& ArbolGeneral<Tbase>::etiqueta(const Nodo n) const {
	return n->etiqueta;
}

template <class Tbase>
void ArbolGeneral<Tbase>::asignarSubarbol(const ArbolGeneral<Tbase> &origen, Nodo nod){
	copiar(origen.laraiz, nod);
}

template<class Tbase>
void ArbolGeneral<Tbase>::podarHijoIzquierda(Nodo n, ArbolGeneral<Tbase> &dest){
	if(n->hijo != NULL){
		dest.laraiz = n->hijo;
		n->hijo = n->hijo->drcha;
		dest.laraiz->padre = NULL;
		dest.laraiz->drcha = NULL;
	}
}

template<class Tbase>
void ArbolGeneral<Tbase>::podarHermanoDerecha(Nodo n, ArbolGeneral<Tbase> &dest){
	if(n->hijo != NULL){
		dest.laraiz = n->drcha;
		n->drcha = n->drcha->drcha;
		dest.laraiz->drcha = NULL;
		dest.laraiz->padre = NULL;
	}
}


template<class Tbase>
void ArbolGeneral<Tbase>::insertarHijoIzquierda(Nodo n, ArbolGeneral<Tbase>& rama){

	Nodo hijo_anterior = n->hijo;

	Nodo nuevo = new nodo;
	copiar(nuevo, rama.laraiz);

	n->hijo = nuevo;
	nuevo->padre = n;
	nuevo->drcha = hijo_anterior;
	nuevo->hijo = NULL;
}

template<class Tbase>
void ArbolGeneral<Tbase>::insertarHermanoDerecha(Nodo n, ArbolGeneral<Tbase>& rama){
	
	Nodo hermano_anterior = n->drcha;

	Nodo nuevo = new nodo;
	copiar(nuevo, rama.laraiz);
	
	nuevo->padre = n->padre;
	n->drcha = nuevo;
	nuevo->drcha = hermano_anterior;
}

template<class Tbase>
void ArbolGeneral<Tbase>::clear(){
	destruir(this->laraiz);
}



template<class Tbase>
int ArbolGeneral<Tbase>::size() const {
	return contar(this->laraiz);
}

template<class Tbase>
bool ArbolGeneral<Tbase>::empty() const {
	return this->size() == 0;
}


template<class Tbase>
bool ArbolGeneral<Tbase>::operator==(const ArbolGeneral<Tbase>& v) const {
	return sonIguales(this->laraiz, v.laraiz);

}

template<class Tbase>
bool ArbolGeneral<Tbase>::operator!=(const ArbolGeneral<Tbase>& v) const {
	return !sonIguales(this->laraiz, v.laraiz);
}

template<class T>
std::istream& operator>>(std::istream& in, ArbolGeneral<T> &v){
	leeArbol(in, v.laraiz);
	return in;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const ArbolGeneral<T> &v){
	escribeArbol(out, v.laraiz);
	return out;
}

//////////////////////////////////////////////////////////////////
//////////////////////////// Iterador ////////////////////////////
//////////////////////////////////////////////////////////////////

template<class Tbase>
ArbolGeneral<Tbase>::iter_preorden::iter_preorden(){}

template<class Tbase>
Tbase& ArbolGeneral<Tbase>::iter_preorden::operator*(){
	return this->it->etiqueta;
}

template<class Tbase>
int ArbolGeneral<Tbase>::iter_preorden::getLevel() const {
	return this->level;
}


template<class Tbase>
typename ArbolGeneral<Tbase>::iter_preorden &ArbolGeneral<Tbase>::iter_preorden::operator++() {
	if (this->it->hijo != NULL){
		this->it = this->it->hijo;
		this->level++;
	}
	else if (this->it->drcha != NULL) {
		this->it = this->it->drcha;
	}
	else {
		Nodo actual = this->it->padre;
		this->level--;

		while(actual->drcha == NULL && actual != this->raiz){
			actual = actual->padre;
			this->level--;
		}

		if (actual == this->raiz){
			this->it = NULL;
			this->level = -1;
		} else {
			this->it = actual->drcha;
		}

	}

	return *this;
}

template <class Tbase>
bool ArbolGeneral<Tbase>::iter_preorden::operator==(const iter_preorden &i){
	return this->raiz == i.raiz && this->it == i.it;
}

template<class Tbase>
bool ArbolGeneral<Tbase>::iter_preorden::operator!=(const iter_preorden &i){
	return !(*this == i);
}



template<class Tbase>
ArbolGeneral<Tbase>::const_iter_preorden::const_iter_preorden(){}

template<class Tbase>
const Tbase& ArbolGeneral<Tbase>::const_iter_preorden::operator*(){
	return this->it->etiqueta;
}

template<class Tbase>
int ArbolGeneral<Tbase>::const_iter_preorden::getLevel() const {
	return this->level;
}


template<class Tbase>
typename ArbolGeneral<Tbase>::const_iter_preorden &ArbolGeneral<Tbase>::const_iter_preorden::operator++() {
	if (this->it->hijo != NULL){
		this->it = this->it->hijo;
		this->level++;
	}
	else if (this->it->drcha != NULL) {
		this->it = this->it->drcha;
	}
	else {
		Nodo actual = this->it->padre;
		this->level--;

		while(actual->drcha == NULL && actual != this->raiz){
			actual = actual->padre;
			this->level--;
		}

		if (actual == this->raiz){
			this->it = NULL;
			this->level = -1;
		} else {
			this->it = actual->drcha;
		}

	}

	return *this;
}

template <class Tbase>
bool ArbolGeneral<Tbase>::const_iter_preorden::operator==(const const_iter_preorden &i){
	return this->raiz == i.raiz && this->it == i.it;
}

template<class Tbase>
bool ArbolGeneral<Tbase>::const_iter_preorden::operator!=(const const_iter_preorden &i){
	return !(*this == i);
}

//////////////////////////////////////////////////////////////////
////////////////////// Funciones begin end ///////////////////////
//////////////////////////////////////////////////////////////////

template<class Tbase>
typename ArbolGeneral<Tbase>::iter_preorden ArbolGeneral<Tbase>::begin() {
	iter_preorden nuevo;

	nuevo.raiz = this->laraiz;
	nuevo.it = this->laraiz;
	nuevo.level = 0;

	return nuevo;
}


template<class Tbase> 
typename ArbolGeneral<Tbase>::const_iter_preorden ArbolGeneral<Tbase>::begin() const {
	const_iter_preorden nuevo;

	nuevo.raiz = this->laraiz;
	nuevo.it = this->laraiz;
	nuevo.level = 0;

	return nuevo;
}

template<class Tbase>
typename ArbolGeneral<Tbase>::iter_preorden ArbolGeneral<Tbase>::end(){
	iter_preorden nuevo;

	nuevo.raiz = this->laraiz;
	nuevo.it = NULL;
	nuevo.level = -1;

	return nuevo;
}


template<class Tbase>
typename ArbolGeneral<Tbase>::const_iter_preorden ArbolGeneral<Tbase>::end() const {
	const_iter_preorden nuevo;

	nuevo.raiz = this->laraiz;
	nuevo.it = NULL;
	nuevo.level = -1;

	return nuevo;
}

#endif