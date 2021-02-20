#ifndef COMANDO_FDISK_H
#define COMANDO_FDISK_H
#include <string>
#include <iostream>
#include <vector>
#include "libreria.h"
using namespace std;
class comando_fdisk
{
public:
  comando_fdisk();
  void ejecutarFdisk(vector<string>);
  void crearParticion(int size,string unit,string path,string type,string name,string fit);
};

#endif // COMANDO_FDISK_H
