#ifndef COMANDO_RMDISK_H
#define COMANDO_RMDISK_H
#include <string>
#include <vector>
#include <iostream>
#include "libreria.h"
using namespace std;
class comando_rmdisk
{
public:
  comando_rmdisk();
  void eliminarDisco(vector <string> ruta);
};

#endif // COMANDO_RMDISK_H
