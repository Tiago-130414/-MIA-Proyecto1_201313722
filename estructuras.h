#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <string>
using namespace std;

typedef struct{
  char part_status[1];
  char part_type[1];
  char part_fit[1];
  int  part_start;
  int  part_size;
  char part_name[16];
}particion;

typedef struct{
  int mbr_tamano;
  char mbr_fecha_creacion[16];
  int  mbr_disk_signature;//numero random que identifica al disco
  char disk_fit [1];
  particion mbr_partitions[4];
}mbr;

class estructuras
{
public:
  estructuras();
};

#endif // ESTRUCTURAS_H
