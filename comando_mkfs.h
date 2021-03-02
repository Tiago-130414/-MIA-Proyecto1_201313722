#ifndef COMANDO_MKFS_H
#define COMANDO_MKFS_H
#include <string>
#include <vector>
#include <iostream>
#include <estructuras.h>
#include "libreria.h"
using namespace std;

class comando_mkfs
{
public:
  comando_mkfs();
  void ejecutarMkfs(vector<string>);
  int validarType(string);
  int validarFS(string);
  string reasignarType(string);
  string reasignarFS(string);

};

#endif // COMANDO_MKFS_H
