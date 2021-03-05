#ifndef COMANDO_LOGIN_H
#define COMANDO_LOGIN_H

#include <string>
#include <iostream>
#include <vector>
#include "libreria.h"
using namespace std;
class comando_login
{
public:
  comando_login();
  void ejecutarLogin(vector<string>);
  void validarDatos(string, string,string);
  vector<string>obtenerDatos(string);
  vector<string>splitPorComasUSR(string);
  void analizarUsuarios(vector<string>);
};

#endif // COMANDO_LOGIN_H
