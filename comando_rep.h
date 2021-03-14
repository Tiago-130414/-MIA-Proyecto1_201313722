#ifndef COMANDO_REP_H
#define COMANDO_REP_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <estructuras.h>
#include <bits/stdc++.h>
#include "libreria.h"
using namespace std;
class comando_rep
{
public:
  comando_rep();
  void ejecutarReporte(vector<string>);
  int validarNombreReportes(string);
  void generarReporte(string,string,string,string);
  void ReporteMBR(string,string);
  string infoParticiones(mbr);
  void reporteBitmapI(string,string);
  void reporteBitmapB(string,string);
  void escribirBitmapTXT(string,string,string);
  void reporteSuperBloque(string,string);
  void reporteDisco(string,string);
  float retornarPorcentaje(int,int);
  void escribirDot(string,string,string,string);
  void reporteInode(string,string);
  void reporteJournal(string,string);
  void reporteTree(string,string);
  string leerBloqueCarpeta(string,int,int);
  string leerBloqueArchivo(string,int,int);
  string leerInodo(string,int,int);
  string recorrerInodos(int,inodo);
  string recorrerBloqueCarpetas(int,bloqueCarpetas);
  string recorrerBloqueArchivos(int,bloqueArchivos);
  void reporteBloques(string,string);
  string leerInodoRB(string,int,int);
  string leerBloqueCarpetaRB(string,int,int);
  string leerBloqueArchivosRB(string,int,int);
  string realizarApuntadoresRB(string,int);
};

#endif // COMANDO_REP_H
