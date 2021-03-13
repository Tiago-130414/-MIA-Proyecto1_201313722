#ifndef COMANDO_MKDIR_H
#define COMANDO_MKDIR_H
#include <string>
#include <vector>
#include <iostream>
#include "libreria.h"
#include <estructuras.h>
using namespace std;
class comando_mkdir
{
public:
  comando_mkdir();
  void ejecutarMkdir(vector <string>);
};

#endif // COMANDO_MKDIR_H
