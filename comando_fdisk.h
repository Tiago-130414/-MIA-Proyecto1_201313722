#ifndef COMANDO_FDISK_H
#define COMANDO_FDISK_H
#include <string>
#include <iostream>
#include <vector>
#include "libreria.h"
#include <cstring>
#include <estructuras.h>
#include <bits/stdc++.h>
using namespace std;
class comando_fdisk
{
public:
  comando_fdisk();
  void ejecutarFdisk(vector<string>);
  void crearParticion(int size,string unit,string path,string type,string name,string fit);
  int validarNombre(char nomb[16],string nomb2);
  int validarParametrosOpcionales(string unit,string type,string fit);
  //funcion que valida el unit y retorna el tamano de la particion
  int tamanoParticionNueva(string unit,int size);
  //funcion que valida el tipo de ajuste y retorna la letra que representa el ajuste de la particion
  char validarAjuste(string fit);
  //funcion que valida el tipo de partcion y retorna la letra que representa el tipo de particon que es
  char validarTipoParticion(string type);
  // funcion que retorna cuantas particiones vacias hay
  int particionesVacias(string path);
  int numeroPartPrimarias(string path);
  int numeroPartExtendidas(string path);

  ///////////////////////////////
  vector<espacio>particionesOcupadas(string path);
  void buscarEspacios(vector<espacio> particionesActivas,string fit);
};

#endif // COMANDO_FDISK_H
