#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include "diccionario.h"
#include "BolsaLetras.h"
#include "ConjuntoLetras.h"

using namespace std;

void imprimirErrores(){
  cout << "Los parametros son:"<<endl;
  cout << " 1.- El fichero con las palabras" << endl;
  cout << " 2.- El fichero con las letras" << endl;
  cout << " 3.- El fichero de salida" << endl;
}

map<char, int> obtenerPorcentajes(map<char, int> repeticiones, int total_repeticiones){

	map<char, int> resultado;
  map<char, int>::iterator it = repeticiones.begin(), end = repeticiones.end();
	for(; it != end; ++it){
		resultado[(*it).first] = 100.0 * (*it).second / total_repeticiones;
	}

	return resultado;
}

map<char,int> obtenerPuntuaciones(map<char,int> repeticiones, int total_repeticiones){	
	
  map<char, int> puntuaciones;
  map<char, int>::iterator it = repeticiones.begin(), end = repeticiones.end();
  
  int rep_max = (*it).second;
  for(; it != end; ++it){
      if (rep_max < (*it).second){
        rep_max = (*it).second;
      }
  }

  it = repeticiones.begin();

  for(; it != end; ++it){
    puntuaciones[(*it).first] = 0.3*rep_max/(*it).second + 1;
    if(puntuaciones[(*it).first] > 10){
      puntuaciones[(*it).first] = 10;
    }
  }
  
  return puntuaciones;
}

  
int main(int argc, char * argv[]){
  if (argc != 4){
	 imprimirErrores();
	 return 1;
  }
  
  ifstream palabras(argv[1]);
  ifstream f_letras(argv[2]);
  ofstream f_nuevo(argv[3]);

  // Cargamos el conjunto de letras
  cout << "Cargando letras..." << endl;
  ConjuntoLetras conjunto_letras;
  f_letras >> conjunto_letras;

  int total_letras = 0;
  map<char, int> repeticiones, porcentajes, puntuaciones;
  ConjuntoLetras::iterator it_conj = conjunto_letras.begin(), end_conj = conjunto_letras.end();
  for(; it_conj != end_conj; ++it_conj) {
  	repeticiones[(*it_conj).getLetra()] = 0;
  }

  char caracter;

  cout << "Calculando apariciones de las letras..." << endl;
  while (palabras.get(caracter)){
    caracter = toupper(caracter);
  	if (repeticiones.find(caracter) != repeticiones.end()){
  		repeticiones[caracter]++;
  		total_letras++;
  	}
  }

  cout << "[+] Normalizando apariciones" << endl;
  porcentajes = obtenerPorcentajes(repeticiones, total_letras);

  cout << "[+] Asignando puntos a las letras" << endl;
  puntuaciones = obtenerPuntuaciones(repeticiones, total_letras);

  ConjuntoLetras nuevo;

  map<char,int>::iterator it_rep = porcentajes.begin(), end_rep = porcentajes.end(),
                          it_punt = puntuaciones.begin();
  for(; it_rep != end_rep; ++it_rep, ++it_punt){
  	nuevo.agregarLetra((*it_rep).first, (*it_rep).second + 1, (*it_punt).second);
  }

  cout << "[+] Escribiendo en el archivo de salida" << endl;
  f_nuevo << "#Letra Cantidad Puntos" << endl;
  f_nuevo << nuevo;


  cout << "Hecho" << endl;
}