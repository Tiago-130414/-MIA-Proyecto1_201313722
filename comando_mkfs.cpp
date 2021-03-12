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
              char ceros = '\0';
              fseek(archivo, initPart, SEEK_SET);
              for(int j = 0;j<tamanioParticion;j++){
                  fwrite(&ceros,sizeof(ceros),1,archivo);
                }
            }
          /* se crea el super bloque*/

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
              numeroInodos = calcularNumeroInodosEXT2_3(tamanioParticion,tamanioJournal);
              numeroBloques = calcularNumeroBloquesEXT2_3(numeroInodos);
              nFileSystem = 3;
            }
          superBloque nSB(llenarSuperBloque(numeroInodos,numeroBloques,nFileSystem,tamanioJournal,initPart));
          fseek(archivo,initPart,SEEK_SET);
          fwrite(&nSB,sizeof(superBloque),1,archivo);
          fclose(archivo);
          inicializarFileSystem(pathDisco,initPart,type);
          cout<<"-> n: "<<numeroInodos<<endl;
          cout<<"-> 3n: "<<numeroBloques<<endl;
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
  strcpy(nuevoSuperBloque.s_umtime,retornarFecha().c_str());
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

///////////CREAR RAIZ Y USUARIOS POR DEFECTO

void comando_mkfs::inicializarFileSystem(string path, int initPart,string type){

  ////inodo de raiz
  inodo inodoNuevo;
  inodoNuevo.i_uid = 1;
  inodoNuevo.i_gid = 1;
  inodoNuevo.i_size = 0;
  strcpy(inodoNuevo.i_atime,retornarFecha().c_str()); //ultima fecha de lectura
  strcpy(inodoNuevo.i_ctime,retornarFecha().c_str()); //fecha de creacion
  strcpy(inodoNuevo.i_mtime,retornarFecha().c_str()); //ultima fecha en que se modifico el inodo
  for(int i=0;i<15;i++){
      inodoNuevo.i_block[i] = -1; //inicializando el vector de apuntadores
    }
  inodoNuevo.i_block[0] = 0;
  inodoNuevo.i_type = '0'; //es cero si es una carpeta
  inodoNuevo.i_perm  = 664;

  ////bloque de carpeta para raiz
  bloqueCarpetas nuevoBloqueCarpetas;
  string usr = "users.txt";
  string pad = "..";
  string self = ".";
  string nBloqueVacio ="-";
  nuevoBloqueCarpetas.b_content[0].b_inodo = 0;
  strcpy(nuevoBloqueCarpetas.b_content[2].b_name,self.c_str());
  nuevoBloqueCarpetas.b_content[1].b_inodo = 0;
  strcpy(nuevoBloqueCarpetas.b_content[1].b_name,pad.c_str());
  nuevoBloqueCarpetas.b_content[2].b_inodo = 1;
  strcpy(nuevoBloqueCarpetas.b_content[2].b_name,usr.c_str());
  nuevoBloqueCarpetas.b_content[3].b_inodo = -1;
  strcpy(nuevoBloqueCarpetas.b_content[3].b_name,nBloqueVacio.c_str());


  string contenidoArchivoUsr = "1,G,root\n";
  contenidoArchivoUsr += "1,U,root,root,123\n";
  ////inodo de archivo usuarios
  inodo inodoArchivo;
  inodoArchivo.i_uid = 1;
  inodoArchivo.i_gid = 1;
  inodoArchivo.i_size = contenidoArchivoUsr.length();
  strcpy(inodoArchivo.i_atime,retornarFecha().c_str()); //ultima fecha de lectura
  strcpy(inodoArchivo.i_ctime,retornarFecha().c_str()); //fecha de creacion
  strcpy(inodoArchivo.i_mtime,retornarFecha().c_str()); //ultima fecha en que se modifico el inodo
  for(int i=0;i<15;i++){
      inodoArchivo.i_block[i] = -1; //inicializando el vector de apuntadores
    }
  inodoArchivo.i_block[0] = 1;
  inodoArchivo.i_type = '1'; //es cero si es una carpeta
  inodoArchivo.i_perm  = 664;

  ////bloque de archivos de usuario
  bloqueArchivos nuevoArchivo;
  strcpy(nuevoArchivo.b_content,contenidoArchivoUsr.c_str());

  //reasignando valores del superbloque
  superBloque sb (retornarSuperBloque(path,initPart));
  sb.s_free_blocks_count = sb.s_free_blocks_count - 2;
  sb.s_free_inodes_count = sb.s_free_inodes_count - 2;
  sb.s_first_blo = 2;
  sb.s_first_ino = 2;

  //escribo el superbloque
  escribirSuperBloque(path,initPart,sb);
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");

  //antes de escribir el bitmap de inodos y de bloques lleno de ceros
  if(type == "fast" || type=="full"){
      char ceros = '0';

      //formateando bitmap de inodos por si el tipo de formateo es fast
      int bm = sb.s_inodes_count;
      fseek(archivo, sb.s_bm_inode_start, SEEK_SET);
      for(int j = 0;j<bm;j++){
          fwrite(&ceros,sizeof(ceros),1,archivo);
        }

      //formateando bitmap de bloques por si el tipo de formateo es fast
      bm = sb.s_blocks_count;
      fseek(archivo, sb.s_bm_block_start, SEEK_SET);
      for(int j = 0;j<bm;j++){
          fwrite(&ceros,sizeof(ceros),1,archivo);
        }
    }

  //si el sistema de archivos es de tipo EXT3
  if(sb.s_filesystem_type == 3){
      //Escribiendo journal pivote
      journal pivote;
      string t = "pivote";
      strcpy(pivote.Journal_nombre,t.c_str());
      pivote.Journal_permisos = 3;
      //escribiendo el pivote
      fseek(archivo,retornarPosicionJournal(initPart,0),SEEK_SET);
      fwrite(&pivote,sizeof(journal),1,archivo);

      //escribiendo journal de carpeta raiz
      journal raiz;
      string tpOperacion = "mkfs";
      char tipo ='0';
      string nombre = "/";
      string fecha = retornarFecha();

      strcpy(raiz.Journal_Tipo_Operacion,tpOperacion.c_str());
      raiz.Journal_tipo = tipo;
      strcpy(raiz.Journal_nombre,nombre.c_str());
      strcpy(raiz.Journal_fecha,fecha.c_str());
      raiz.Journal_propietario = 1;
      raiz.Journal_GID =1;
      raiz.Journal_permisos = 664;

      fseek(archivo,retornarPosicionJournal(initPart,1),SEEK_SET);
      fwrite(&raiz,sizeof(journal),1,archivo);

      //escribiendo journal de archivo usuarios.txt
      journal archTXT;
      tipo = '1';
      nombre = "/users.txt";
      fecha = retornarFecha();
      strcpy(archTXT.Journal_Tipo_Operacion,tpOperacion.c_str());
      archTXT.Journal_tipo = tipo;
      strcpy(archTXT.Journal_nombre,nombre.c_str());
      strcpy(archTXT.Journal_contenido,contenidoArchivoUsr.c_str());
      strcpy(archTXT.Journal_fecha,fecha.c_str());
      archTXT.Journal_propietario = 1;
      archTXT.Journal_GID = 1;
      archTXT.Journal_permisos = 664;

      fseek(archivo,retornarPosicionJournal(initPart,2),SEEK_SET);
      fwrite(&archTXT,sizeof(journal),1,archivo);


      //escribirJournal

    }

  //marco los inodos y bloques usados en el bitmap
  char bm_usado = '1';

  //marcando el bitmap de inodos
  fseek(archivo,sb.s_bm_inode_start, SEEK_SET);
  fwrite(&bm_usado,sizeof(bm_usado),1,archivo);
  fwrite(&bm_usado,sizeof(bm_usado),1,archivo);

  //marcando el bitmap de bloques
  fseek(archivo,sb.s_bm_block_start, SEEK_SET);
  fwrite(&bm_usado,sizeof(bm_usado),1,archivo);
  fwrite(&bm_usado,sizeof(bm_usado),1,archivo);

  //escribir los inodos en tabla de inodos de la raiz
  int pos1 = retornarPosicionInodo(sb.s_inode_start,0);
  fseek(archivo, pos1, SEEK_SET);
  fwrite(&inodoNuevo,sizeof(inodo),1,archivo);

  //escribir los inodos en tabla de inodos de archivos
  int pos2 = retornarPosicionInodo(sb.s_inode_start,1);
  fseek(archivo, pos2, SEEK_SET);
  fwrite(&inodoArchivo,sizeof(inodo),1,archivo);

  //escribir los bloques en la tabla de bloques de carpetas
  fseek(archivo, retornarPosicionBloque(sb.s_block_start,0), SEEK_SET);
  fwrite(&nuevoBloqueCarpetas,sizeof(bloqueCarpetas),1,archivo);

  //escribir los bloques en la tabla de bloques de archivos
  fseek(archivo, retornarPosicionBloque(sb.s_block_start,1), SEEK_SET);
  fwrite(&nuevoArchivo,sizeof(bloqueArchivos),1,archivo);

  fclose(archivo);

}

string comando_mkfs::retornarNombreApuntador(int id){
  return "AP"+id;
}
