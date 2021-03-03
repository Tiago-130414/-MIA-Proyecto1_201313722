#include "comando_mkfs.h"

comando_mkfs::comando_mkfs()
{

}

void comando_mkfs::ejecutarMkfs(vector<string> parametrosMKFS){
  int tamanioParametrosMKFS = parametrosMKFS.size();
  //variables que guardan el valor
  string id = "";
  string type="-1";
  string fs = "-1";
  //variable booleana que me permite saber si vino el obligatorio id
  int existeID = 0;
  for(int i=0;i<tamanioParametrosMKFS;i++){
      //cout<<parametrosMKFS[i]<<endl;
      if(aMinuscula(parametrosMKFS[i]) == "id"){
          id = parametrosMKFS[i+1];
          existeID = 1;
        }else if(aMinuscula(parametrosMKFS[i]) == "type"){
          type = aMinuscula(parametrosMKFS[i+1]);
        }else if(aMinuscula(parametrosMKFS[i])== "fs"){
          fs = aMinuscula(parametrosMKFS[i+1]);
        }
    }
  //se verifica si existe el id
  string tType = "";
  string tFS = "";
  if(existeID == 1){
      if(validarType(type)==1){
          tType = reasignarType(type);
          if(validarFS(fs)==1){
              tFS = reasignarFS(fs);
              crearFileSystem(id,tFS,tType);
            }else{
              cout<<"*** El valor del -fs no es valido ***"<<endl;
            }
        }else{
          cout<<"*** El valor de -type no es valido ***"<<endl;
        }
    }else{
      cout<<"*** Falta parametro obligatorio -id ***"<<endl;
    }
}

//funcion que valida los valores enviados para type sean los posibles correctos
int comando_mkfs::validarType(string type){
  int rType = 0;
  if(type=="-1"||type=="fast"||type=="full"){
      rType=1;
    }
  return rType;
}

//funcion que valida los valores enviados para fs sean los posibles correctos
int comando_mkfs::validarFS(string fs){
  int rFS = 0;
  if(fs=="-1"||fs=="2fs" || fs=="3fs"){
      rFS=1;
    }
  return rFS;
}

//funcion que asigna el valor a type cuando no trae
string comando_mkfs::reasignarType(string type){
  string temp;
  if(type=="-1"){
      temp = "full";
    }else{
      temp = type;
    }
  return temp;
}

//funcion que asigna el valor a fs cuando no trae
string comando_mkfs::reasignarFS(string fs){
  string temp;
  if(fs=="-1"){
      temp = "2fs";
    }else{
      temp = fs;
    }
  return temp;
}

//metodo que crea el sistema de archivos
void comando_mkfs::crearFileSystem(string id,string fs,string type){
  int idDisco = stoi(retornarIndiceDisco(id));
  string pathDisco = retornarPathDisco(idDisco);
  string nombreParticion = retornarNombreParticion(idDisco,id);
  if(pathDisco !="-1"){
      if(nombreParticion != "-1"){
          //se puede buscar particion
          particion particionTemp = retornarParticion(pathDisco,nombreParticion);
          int tamanioParticion = particionTemp.part_size;
          int initPart = particionTemp.part_start;
          //se crea un archivo en caso que haya que formatear y para escribir el superbloque
          FILE *archivo;
          archivo = fopen(pathDisco.c_str(),"rb+");
          /*Se formatea la particion si es full*/
          if(type == "full"){
              char ceros = '1';
              fseek(archivo, initPart, SEEK_SET);
              for(int j = 0;j<tamanioParticion;j++){
                  fwrite(&ceros,sizeof(ceros),1,archivo);
                }
            }
          /* se crea el super bloque*/
          superBloque nSB;
          int numeroInodos;
          int numeroBloques;
          int nFileSystem;
          int tamanioJournal = 0;
          if(fs == "2fs"){
              numeroInodos = calcularNumeroInodosEXT2_3(tamanioParticion,tamanioJournal);
              numeroBloques = calcularNumeroBloquesEXT2_3(numeroInodos);
              nFileSystem = 2;
            }else if(fs == "3fs"){
              tamanioJournal = sizeof(journal);
              cout<<tamanioJournal<<endl;
              numeroInodos = calcularNumeroInodosEXT2_3(tamanioParticion,tamanioJournal);
              numeroBloques = calcularNumeroBloquesEXT2_3(numeroInodos);
              nFileSystem = 3;
            }
          cout<< numeroInodos<<endl;
          cout<< numeroBloques<<endl;
          nSB = llenarSuperBloque(numeroInodos,numeroBloques,nFileSystem,tamanioJournal,initPart);
          cout<<nSB.s_bm_inode_start<<endl;
          cout<<nSB.s_bm_block_start<<endl;
          cout<<nSB.s_inode_start<<endl;
          cout<<nSB.s_block_start<<endl;
          /*escribir el super bloque en la particion*/
          fseek(archivo,initPart,SEEK_SET);
          fwrite(&nSB,sizeof(superBloque),1,archivo);
          //cerrar el archivo

          fclose(archivo);

        }else{
          cout<<"*** La particiones no esta montada ***"<<endl;
        }
    }else{
      cout<<"*** El disco buscado no esta montado ***"<<endl;
    }
}

//metodo que llena el superbloque
superBloque comando_mkfs::llenarSuperBloque(int numeroInodos, int numeroBloques ,int fsType, int journalSize, int initPart){
  superBloque nuevoSuperBloque;
  nuevoSuperBloque.s_filesystem_type = fsType;
  nuevoSuperBloque.s_inodes_count = numeroInodos;
  nuevoSuperBloque.s_blocks_count = numeroBloques;
  nuevoSuperBloque.s_free_blocks_count = numeroBloques;
  nuevoSuperBloque.s_free_inodes_count = numeroInodos;
  strcpy(nuevoSuperBloque.s_mtime,retornarFecha().c_str());
  nuevoSuperBloque.s_mnt_count = 1;
  nuevoSuperBloque.s_magic = 61267;
  nuevoSuperBloque.s_inode_size = sizeof(inodo);
  nuevoSuperBloque.s_block_size = sizeof(bloqueCarpetas);
  nuevoSuperBloque.s_first_ino = 0;
  nuevoSuperBloque.s_first_blo = 0;
  int tamJournal = numeroInodos * journalSize;
  nuevoSuperBloque.s_bm_inode_start = initPart + sizeof(superBloque)+ tamJournal;
  nuevoSuperBloque.s_bm_block_start = initPart + sizeof(superBloque) + tamJournal + numeroInodos;
  nuevoSuperBloque.s_inode_start = initPart + sizeof(superBloque) + tamJournal + numeroInodos + numeroBloques;
  nuevoSuperBloque.s_block_start = initPart + sizeof(superBloque) + tamJournal + numeroInodos + numeroBloques + numeroInodos * sizeof(inodo);
  return nuevoSuperBloque;
}

int comando_mkfs::calcularNumeroInodosEXT2_3(int tamanioParticion,int tamanioJounal){
  int n;
  int aux;
  int aux2;
  int tamanioSuperBloque = sizeof(superBloque);
  int tamanioInodos = sizeof(inodo);
  int tamanioBlock = sizeof(bloqueCarpetas);
  n = tamanioParticion - tamanioSuperBloque;
  aux2 = 3 * tamanioBlock;
  aux = 4 + tamanioJounal + tamanioInodos + aux2;
  n = floor(n/aux);
  return n;
}

int comando_mkfs::calcularNumeroBloquesEXT2_3(int numeroInodos){
  return 3*numeroInodos;
}

void comando_mkfs::imprimirsize(){

  cout<<"Super bloque: "<< sizeof(superBloque)<<endl;
  cout<<"Inodos: "<< sizeof(inodo)<<endl;
  cout<<"Block: "<< sizeof(carpeta)<<endl;
  cout<<"Carpetas: "<< sizeof(bloqueCarpetas)<<endl;
  cout<<"Bloque apuntadores: "<<sizeof(bloqueApuntadores)<<endl;
  cout<<"Journal: "<<sizeof(journal)<<endl;
}
