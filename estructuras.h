#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <string>
#include <vector>
using namespace std;

typedef struct{
  char part_status;
  char part_fit;
  int part_start;
  int part_size;
  int part_next;
  char part_name[16];
}ebr;

typedef struct{
  char part_status;
  char part_type;
  char part_fit;
  int  part_start;
  int  part_size;
  char part_name[16];
}particion;

typedef struct{
  int mbr_tamano;
  char mbr_fecha_creacion[16];
  int  mbr_disk_signature;//numero random que identifica al disco
  char disk_fit [1];
  particion mbr_particiones[4];
}mbr;

/////////////////////////////////////
/////PARA PARTICIONES
typedef struct{
  int inicioParticion;
  int tamanoParticion;
}espacio;

typedef struct{
  int inicio;
  int espacioLibre;
}vacios;

////////////////////////////////////
//////PARA MOUNT
typedef struct{
  string id;
  string nombre;
}particionMontada;

typedef struct{
  int id;
  string path;
  vector<particionMontada> particiones;
}disco;

class estructuras
{
public:
  estructuras();
};

#endif // ESTRUCTURAS_H
