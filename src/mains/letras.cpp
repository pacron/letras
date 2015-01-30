#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "diccionario.h"
#include "BolsaLetras.h"
#include "ConjuntoLetras.h"


using namespace std;

void imprimirErrores(){
  cout << "Los parametros son:"<<endl;
  cout << "1.- El fichero con las palabras" << endl;
  cout << "2.- El fichero con las letras" << endl;
  cout << "3.- La longitud de la palabra" << endl;
  cout << "4.- El modo de juego [L|P]" << endl;
}


  
int main(int argc, char * argv[]){
  if (argc != 5){
	 imprimirErrores();
   exit(1);
  }
  
  ifstream palabras(argv[1]);
  ifstream f_letras(argv[2]);
  int n_letras = atoi(argv[3]);
  
  // Cargamos el diccionario
  cout<<"Cargando diccionario...."<< endl;
  Diccionario diccionario;
  palabras >> diccionario;

  map <char,int> puntuaciones;

  // Cargamos el conjunto de letras
  cout << "Cargando letras..." << endl;
  ConjuntoLetras conjunto_letras;
  f_letras >> conjunto_letras;

  // Creamos la bolsa de letras a partir del conjunto
  BolsaLetras bolsa(conjunto_letras);

  ConjuntoLetras::iterator it_conj = conjunto_letras.begin(), end_conj = conjunto_letras.end();
  if (argv[4][0] == 'P'){

    for(; it_conj != end_conj; ++it_conj){
      char letra = tolower((*it_conj).getLetra());
      puntuaciones[letra] = (*it_conj).getPuntuacion();
    }  

  }else{
  
    for(; it_conj != end_conj; ++it_conj){
      char letra = tolower((*it_conj).getLetra());
      puntuaciones[letra] = 1;
    }    
  }


  string user_solution;

  char si_o_no = 'S';

  while (si_o_no == 'S' || si_o_no == 's'){
    // Sacamos las letras correspondientes
    vector<Letra> letras = bolsa.obtenerLetras(n_letras);

    for(int i = 0; i < letras.size(); ++i) {  // Mostramos las letras
      cout << letras[i].getLetra() << "\t";
    }
    cout << endl;

    string palabra_usuario;
    cout << "¿Cual es tu solución? ";
    cin >> palabra_usuario;
    int puntuacion_usuario = 0;

    if (diccionario.existe(palabra_usuario)){
      for (int i = 0; i < palabra_usuario.size(); ++i){
        if(puntuaciones.find(palabra_usuario[i]) != puntuaciones.end()){
          puntuacion_usuario += puntuaciones[palabra_usuario[i]]; 
        }

      }
      cout << "Tu puntuación es: " << puntuacion_usuario << endl;
    }
    else
      cout << "Deja de inventarte palabras" << endl;

    cout << "Mis soluciones son: " << endl;
    vector<string> best_words = diccionario.obtenerPalabrasMejorPuntuacion(letras, puntuaciones);
    for (int i = 0; i < best_words.size(); ++i){
      cout << best_words[i] << endl;
    }
    cout << "¿Quieres seguir jugando? [S|N]: ";
    cin >> si_o_no;

  }

  
}
  
  
  
