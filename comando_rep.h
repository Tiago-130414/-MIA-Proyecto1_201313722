#ifndef COMANDO_REP_H
#define COMANDO_REP_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <estructuras.h>
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
  void escribirBitmapTXT(string ruta,string nombre,string bitmap);
};

#endif // COMANDO_REP_H
