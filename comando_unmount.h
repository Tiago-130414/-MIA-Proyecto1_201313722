#ifndef COMANDO_UNMOUNT_H
#define COMANDO_UNMOUNT_H
#include <string>
#include "libreria.h"
#include <iostream>
#include <vector>
class comando_unmount
{
public:
  comando_unmount();
  void ejecutarUnmount(vector<string>);
};

#endif // COMANDO_UNMOUNT_H
