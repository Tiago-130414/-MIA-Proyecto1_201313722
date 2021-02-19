#ifndef LIBRERIA_H
#define LIBRERIA_H
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;
string aMayuscula(string cadena);
string aMinuscula(string cadena);
bool extensionRutaValida(string nombreArchivo);
string rRuta(vector<string> path);
string quitarComillas(string ruta);
vector<string> descomponerRuta(string ruta);
#endif // LIBRERIA_H
