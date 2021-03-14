#ifndef COMANDO_LOGIN_H
#define COMANDO_LOGIN_H

#include <string>
#include <iostream>
#include <vector>
#include <estructuras.h>
#include "libreria.h"
using namespace std;
class comando_login
{
public:
  comando_login();
  void ejecutarLogin(vector<string>);
  void validarDatos(string, string,string);
  vector<datosUSR>obtenerDatos(string);
  vector<datosUSR>splitPorComasUSR(string);
  datosUSR analizarUsuarios(vector<string>);
  void realizarLogin(vector<datosUSR>,string,string,string,string,string);
};

#endif // COMANDO_LOGIN_H
