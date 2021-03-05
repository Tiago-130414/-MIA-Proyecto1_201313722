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
  int nParticiones;
  string path;
  vector<particionMontada> particiones;
}disco;
////////////////////////////////////
//////PARA SISTEMA DE ARCHIVOS

typedef struct{
  int s_filesystem_type;
  int s_inodes_count;
  int s_blocks_count;
  int s_free_blocks_count;
  int s_free_inodes_count;
  char s_mtime[16];
  char s_umtime[16];
  int s_mnt_count;
  int s_magic;
  int s_inode_size;
  int s_block_size;
  int s_first_ino;
  int s_first_blo;
  int s_bm_inode_start;
  int s_bm_block_start;
  int s_inode_start;
  int s_block_start;
}superBloque;

typedef struct{
  int i_uid;
  int i_gid;
  int i_size;
  char i_atime[16];
  char i_ctime[16];
  char i_mtime[16];
  int i_block [15];
  char i_type;
  int i_perm;
}inodo;

typedef struct{
  char Journal_Tipo_Operacion[10];
  char Journal_tipo;
  char Journal_nombre[200];
  char Journal_contenido[200];
  char Journal_fecha[16];
  int Journal_propietario;
  int Journal_permisos;
  int Journal_GID;//group id
}journal;

typedef struct{
  char b_name[12];
  int b_inodo;
}carpeta;

typedef struct{
  carpeta b_content[4];
}bloqueCarpetas;

typedef struct{
  char b_content[64];
}bloqueArchivos;

typedef struct{
  int b_pointers [16];
}bloqueApuntadores;
/////////////////////////////////////
/////PARA ESPACIOS EN PARTICIONES
typedef struct{
  int inicio;
  int tamano;
}bm_espacio;
/////////////////////////////////////
/////PARA USUARIOS
typedef struct{
  string usuario;
  string id;
}datosUSR;
class estructuras
{
public:
  estructuras();
};

#endif // ESTRUCTURAS_H
