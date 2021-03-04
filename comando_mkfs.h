#ifndef COMANDO_MKFS_H
#define COMANDO_MKFS_H
#include <string>
#include <vector>
#include <iostream>
#include <estructuras.h>
#include <math.h>
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
  void imprimirsize();
  void crearFileSystem(string,string,string);
  int calcularNumeroInodosEXT2_3(int,int);
  int calcularNumeroBloquesEXT2_3(int);
  superBloque llenarSuperBloque(int, int,int,int,int);
  void inicializarFileSystem(string,int,string);
  string retornarNombreApuntador(int);
};

#endif // COMANDO_MKFS_H
