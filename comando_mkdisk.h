#ifndef COMANDO_MKDISK_H
#define COMANDO_MKDISK_H
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <stdlib.h>
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
  string aMayuscula(string cadena);
  string aMinuscula(string cadena);
};

#endif // COMANDO_MKDISK_H
