#ifndef COMANDO_MOUNT_H
#define COMANDO_MOUNT_H
#include <string>
#include "libreria.h"
#include <iostream>
#include <vector>
using namespace std;
class comando_mount
{
public:
  comando_mount();
  void ejecutarMount(vector<string>);
  string generarID(int,int);
  int existeParticion(string,string);
  int existeDisco(string);
  void mostrarRegistro();
};

#endif // COMANDO_MOUNT_H
