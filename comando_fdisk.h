#ifndef COMANDO_FDISK_H
#define COMANDO_FDISK_H
#include <string>
#include <iostream>
#include <vector>
#include "libreria.h"
using namespace std;
class comando_fdisk
{
public:
  comando_fdisk();
  void ejecutarFdisk(vector<string>);
};

#endif // COMANDO_FDISK_H
