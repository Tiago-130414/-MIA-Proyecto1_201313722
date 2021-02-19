#ifndef COMANDO_RMDISK_H
#define COMANDO_RMDISK_H
#include <string>
#include <vector>
#include <iostream>
#include "libreria.h"
#include <cstdlib>
#include <stdlib.h>
using namespace std;
class comando_rmdisk
{
public:
  comando_rmdisk();
  void eliminarDisco(vector <string> ruta);
  bool confirmarEliminarArchivo();
};

#endif // COMANDO_RMDISK_H
