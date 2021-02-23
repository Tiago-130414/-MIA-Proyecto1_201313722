#ifndef LIBRERIA_H
#define LIBRERIA_H
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <estructuras.h>
using namespace std;
string aMayuscula(string cadena);
string aMinuscula(string cadena);
bool extensionRutaValida(string nombreArchivo);
string rRuta(vector<string> path);
string quitarComillas(string ruta);
vector<string> descomponerRuta(string ruta);
bool extensionScriptValida(string nombreArchivo);
void imprimirInfo(string path);
void imprimirDisco(string path);
#endif // LIBRERIA_H
