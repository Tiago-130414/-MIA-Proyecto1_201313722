#ifndef COMANDO_MKDISK_H
#define COMANDO_MKDISK_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class comando_mkdisk
{
public:
  comando_mkdisk();
  int size;
  string path;
  string unit;
  string fit;
  void prueba(string size,string path, string unit,string fit);
  void prueba2(vector<string> valores_mkdisk);
};

#endif // COMANDO_MKDISK_H
