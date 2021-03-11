#ifndef LIBRERIA_H
#define LIBRERIA_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <estructuras.h>
using namespace std;
string aMayuscula(string cadena);
string aMinuscula(string cadena);
bool extensionRutaValida(string nombreArchivo);
string rRuta(vector<string> path);
string rRutaDeArchivo(string rutaCarpetas,string nombreArchivoCExtension);
string quitarComillas(string ruta);
vector<string> descomponerRuta(string ruta);
bool extensionScriptValida(string nombreArchivo);
void imprimirInfo(string path);
void imprimirDisco(string path);
void mostrarRegistro();//metodo que muestra las particiones montadas en memoria
string retornarIndiceDisco(string);
mbr retornarMBRdisco(string);
string retornarPathDisco(int);
string retornarNombreParticion(int,string);
particion retornarParticion(string path,string nombParticion);
string retornarFecha();
superBloque retornarSuperBloque(string,int);
string leerBitmapI(string,int);
string leerBitmapB(string,int);
vector<bm_espacio> retornarEspaciosVacios(string);
void escribirSuperBloque(string, int, superBloque);
int retornarPosicionInodo(int, int);
int retornarPosicionBloque(int, int);
journal retornarJournal(string, int);
int retornarPosicionJournal(int,int);
void recorrerJournal(string, int);
void escribirJournal(string, int,journal);
inodo retornarInodo(string,int,int);
int recorrerSistemaArchivos(vector<string>,inodo,string,int);
bloqueArchivos retornarBloqueArchivos(string,int,int);
bloqueCarpetas retornarBloqueCarpetas(string,int,int);
int recorrerBloqueCarpetas(int,string,string,int);
string recorrerBloqueArchivos(int,string,int);
void escribirReporte(string,string,string);
string quitarExtension(string);
#endif // LIBRERIA_H
