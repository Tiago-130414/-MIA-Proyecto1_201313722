#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <string>
using namespace std;

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
  particion mbr_partition_1;
  particion mbr_partition_2;
  particion mbr_partition_3;
  particion mbr_partition_4;
}mbr;

class estructuras
{
public:
  estructuras();
};

#endif // ESTRUCTURAS_H
