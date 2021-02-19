#ifndef COMANDO_MKDISK_H
#define COMANDO_MKDISK_H
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <estructuras.h>
#include <time.h>
#include "libreria.h"
using namespace std;

class comando_mkdisk
{
public:
  comando_mkdisk();
  int size;
  string path;
  string unit;
  string fit;
  void ejecutarMkdisk(vector<string> valores_mkdisk);
  void crearDisco(int size,string path,string unit,string fit);
  void generarDisco(int size,string path, string unit, string fit);
  bool extensionRutaValida(string nombreArchivo);

  char tiempo();
  string rRuta(vector<string> path);
  string quitarComillas(string ruta);

  vector<string> descomponerRuta(string ruta);
};

#endif // COMANDO_MKDISK_H
