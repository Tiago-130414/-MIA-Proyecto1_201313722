#ifndef COMANDO_FDISK_H
#define COMANDO_FDISK_H
#include <string>
#include <iostream>
#include <vector>
#include "libreria.h"
#include <cstring>
using namespace std;
class comando_fdisk
{
public:
  comando_fdisk();
  void ejecutarFdisk(vector<string>);
  void crearParticion(int size,string unit,string path,string type,string name,string fit);
  int validarNombre(char nomb[16],string nomb2);
  int validarParametrosOpcionales(string unit,string type,string fit);
};

#endif // COMANDO_FDISK_H
