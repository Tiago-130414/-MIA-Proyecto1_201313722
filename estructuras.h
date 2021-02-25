#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <string>
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


typedef struct{
  int inicioParticion;
  int tamanoParticion;
}espacio;

typedef struct{
  int inicio;
  int espacioLibre;
}vacios;

class estructuras
{
public:
  estructuras();
};

#endif // ESTRUCTURAS_H
