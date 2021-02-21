#ifndef COMANDO_EXEC_H
#define COMANDO_EXEC_H
#include <iostream>
#include <vector>
#include <string>
#include "libreria.h"
#include <fstream>
#include <parser.h>  // Nuestro parser
#include <scanner.h>  // Nuestro scanner
using namespace std;
class comando_exec
{
public:
  comando_exec();
  void leerScript(vector<string>);
};

#endif // COMANDO_EXEC_H
