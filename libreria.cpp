#include "libreria.h"

//FUNCIONES STRING PARA PASAR DE MAYUSCULA A MINUSCULA
string aMayuscula(string cadena) {
  for (int i = 0; i < cadena.length(); i++) cadena[i] = toupper(cadena[i]);
  return cadena;
}
string aMinuscula(string cadena) {
  for (int i = 0; i < cadena.length(); i++) cadena[i] = tolower(cadena[i]);
  return cadena;
}

//FUNCION QUE RETORNA LA RUTA COMO STRING SIN EXTENSION DE ARCHIVO
string rRuta(vector<string> path){
  string ruta="";
  for(int i =0;i<path.size()-1;i++){
      ruta +="/" + path[i];
    }
  return ruta;
}

//FUNCION QUE RETORNA LA RUTA COMO STRING CON EXTENSION DE ARCHIVO
string rRutaDeArchivo(string rutaCarpetas,string nombreArchivoCExtension){
  string ruta= rutaCarpetas+"/"+nombreArchivoCExtension;
  return ruta;
}

//FUNCION QUE RETORNA UN ARRAY CON TODAS LAS CARPETAS
vector<string> descomponerRuta(string ruta){
  vector<string> vCarpetas;
  int posInit = 0;
  int posFound = 0;
  string splitted;
  string pattern = "/";
  string rTemp = quitarComillas(ruta);
  //cout<<rTemp<<endl;
  while(posFound >= 0){
      posFound = rTemp.find(pattern, posInit);
      splitted = rTemp.substr(posInit, posFound - posInit);
      posInit = posFound + 1;
      vCarpetas.push_back(splitted);
    }
  vCarpetas.erase(vCarpetas.begin());

  return vCarpetas;
}

//FUNCION QUE QUITA COMILLAS EN DADO CASO VENGAN
string quitarComillas(string ruta){
  string cad="";
  int tam = ruta.length();
  char char_arr[tam+1];
  strcpy(char_arr,ruta.c_str());
  for(int j =0;j<tam;j++){
      if(char_arr[j]!='\"'){
          cad+=char_arr[j];
        }
    }
  return cad;
}

//FUNCION QUE EVALUA LA EXTENSION
bool extensionRutaValida(string nombreArchivo){
  vector<string> archivo;
  int posInit = 0;
  int posFound = 0;
  string splitted;
  string pattern = ".";
  bool valida = false;
  while(posFound >= 0){
      posFound = nombreArchivo.find(pattern, posInit);
      splitted = nombreArchivo.substr(posInit, posFound - posInit);
      //cout<<splitted<<endl;
      posInit = posFound + 1;
      archivo.push_back(splitted);
    }
  if(archivo[archivo.size()-1]=="dk" && archivo.size() != 1){
      //cout<<"extension valida"<<endl;
      valida = true;
    }
  return valida;
}

//FUNCION QUE IMPRIME VALORES DENTRO DE DISCO (MBR)
void imprimirDisco(string path){
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  if(archivo!=NULL){
      mbr MBR;
      fseek(archivo,0,SEEK_SET);
      fread(&MBR,sizeof(mbr),1,archivo);
      fclose(archivo);
      //cout<<"Datos del disco"<<endl;
      cout<<"-> tamano: "<<MBR.mbr_tamano<<endl;
      cout<<"-> fecha: "<<MBR.mbr_fecha_creacion<<endl;
      cout<<"-> fit: "<<MBR.disk_fit<<endl;
      cout<<"-> id: "<<MBR.mbr_disk_signature<<endl;
    }else{
      cout<<"Problema al leer el disco"<<endl;
    }
}

void imprimirInfo(string path){
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  if(archivo!=NULL){
      mbr MBR;
      fseek(archivo,0,SEEK_SET);
      fread(&MBR,sizeof(mbr),1,archivo);
      fclose(archivo);
      //cout<<"Datos del disco"<<endl;
      cout<<"-> tamano: "<<MBR.mbr_tamano<<endl;
      cout<<"-> fecha: "<<MBR.mbr_fecha_creacion<<endl;
      cout<<"-> fit: "<<MBR.disk_fit<<endl;
      cout<<"-> id: "<<MBR.mbr_disk_signature<<endl;

      for(int i=0;i<4;i++){
          if(MBR.mbr_particiones[i].part_status =='1'){
              cout<<"->Nombre de particion: "<<MBR.mbr_particiones[i].part_name<<endl;
              cout<<"->Size de particion: "<<MBR.mbr_particiones[i].part_size<<endl;
              cout<<"->Ajuste de particion: "<<MBR.mbr_particiones[i].part_fit<<endl;
              cout<<"->Start de particion: "<<MBR.mbr_particiones[i].part_start<<endl;
              cout<<"->Type de particion: "<<MBR.mbr_particiones[i].part_type<<endl;
            }
        }
    }else{
      cout<<"Problema al leer el disco"<<endl;
    }
}

bool extensionScriptValida(string nombreArchivo){
  vector<string> archivo;
  int posInit = 0;
  int posFound = 0;
  string splitted;
  string pattern = ".";
  bool valida = false;
  while(posFound >= 0){
      posFound = nombreArchivo.find(pattern, posInit);
      splitted = nombreArchivo.substr(posInit, posFound - posInit);
      posInit = posFound + 1;
      archivo.push_back(splitted);
    }
  if(archivo[archivo.size()-1]=="script" && archivo.size() != 1){
      valida = true;
    }
  return valida;
}
///////metodo que muestra las particiones
void mostrarRegistro(){
  extern vector <disco> registro;
  int tamanioRegistro = registro.size();
  for(int i =0;i<tamanioRegistro;i++){
      int tamanioParticiones = registro[i].particiones.size();
      cout<<"\n*** DISCO ***"<<endl;
      cout<<"ID disco: "<<registro[i].id<<endl;
      cout<<"Ruta disco: "<<registro[i].path<<endl;
      cout<<"Numero de particiones que se insertaron: "<<registro[i].nParticiones<<endl;
      for(int j=0;j<tamanioParticiones;j++){
          cout<<endl;
          cout<<"*** PARTICION "<<j<<" ***"<<endl;
          cout<<"ID particion: "<<registro[i].particiones[j].id<<endl;
          cout<<"Nombre particion: "<<registro[i].particiones[j].nombre<<endl;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// DISCO ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

//////metodo que retorna el indice del disco
string retornarIndiceDisco(string id){
  string temp;
  temp = id.substr(2,id.length()-3);
  return temp;
}

/////metodo que retorna el MBR de un disco
mbr retornarMBRdisco(string path){
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  fseek(archivo, 0, SEEK_SET); //me posiciono en el inicio del archivo
  mbr MBR;//mbr temporal que agarra el mbr que ya esta en el disco
  fread(&MBR,sizeof(mbr),1,archivo);
  fclose(archivo);
  return MBR;
}

/////metodo que busca el path del disco
string retornarPathDisco(int id){
  extern vector <disco> registro;
  string path = "-1";
  int tamanioRegistro = registro.size();
  for(int i = 0;i<tamanioRegistro;i++){
      if(registro[i].id==id){
          path = registro[i].path;
          break;
        }
    }
  return path;
}

////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// PARTICION //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

string retornarNombreParticion(int idDisco,string id){
  extern vector <disco> registro;
  string nombParticion = "-1";
  int tamanioRegistro = registro.size();
  for(int i = 0;i<tamanioRegistro;i++){
      if(registro[i].id==idDisco){
          int tamanioParticiones = registro[i].particiones.size();
          for(int j=0;j<tamanioParticiones;j++){
              //cout<<registro[i].particiones[j].id<<endl;
              if(registro[i].particiones[j].id==aMayuscula(id)){
                  nombParticion = registro[i].particiones[j].nombre;
                  break;
                }
            }
          break;
        }
    }
  return nombParticion;
}

particion retornarParticion(string path,string nombParticion){
  FILE *archivo;
  particion part;
  archivo = fopen(path.c_str(),"rb+");
  if(archivo!= NULL){
      fseek(archivo, 0, SEEK_SET); //me posiciono en el inicio del archivo
      mbr MBR;//mbr temporal que agarra el mbr que ya esta en el disco
      fread(&MBR,sizeof(mbr),1,archivo);
      for(int i=0;i<4;i++){
          if(MBR.mbr_particiones[i].part_status=='1'){
              if(MBR.mbr_particiones[i].part_name == nombParticion){
                  part = MBR.mbr_particiones[i];
                  break;
                }
            }
        }
    }
  fclose(archivo);
  return part;
}

string retornarFecha(){
  char fecha[16];
  time_t fechaActual;
  time(&fechaActual);
  struct tm* informacion = localtime(&fechaActual);
  strftime(fecha,sizeof(fecha),"%d/%m/%y %H:%M",informacion);
  return fecha;
}

////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// SUPER BLOQUE /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
/////retornar superbloque
superBloque retornarSuperBloque(string path,int partInit){
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  fseek(archivo, partInit, SEEK_SET); //me posiciono en el inicio del archivo
  superBloque sbTemp;//superbloque temporal que agarra el superbloque que ya esta en el disco
  fread(&sbTemp,sizeof(superBloque),1,archivo);
  fclose(archivo);
  return sbTemp;
}

/////sobreescribir el superbloque
void escribirSuperBloque(string path, int partInit , superBloque sbTemp){
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  fseek(archivo, partInit, SEEK_SET); //me posiciono en el inicio del archivo
  fwrite(&sbTemp,sizeof(superBloque),1,archivo);
  fclose(archivo);
}

/////leer el bitmap de inodos
string leerBitmapI(string path,int partInit){
  string bitmap="";
  superBloque sb = retornarSuperBloque(path,partInit);
  int initBMI = sb.s_bm_inode_start;
  int tamanioBMI = sb.s_inodes_count;
  char temp[tamanioBMI];
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  fseek(archivo,initBMI,SEEK_SET);
  fread(&temp,tamanioBMI,1,archivo);
  for(int i=0;i<tamanioBMI;i++){
      bitmap += temp[i];
    }
  fclose(archivo);
  return bitmap;
}

/////leer el bitmap de bloques
string leerBitmapB(string path,int partInit){
  string bitmap="";
  superBloque sb = retornarSuperBloque(path,partInit);
  int initBMB = sb.s_bm_block_start;
  int tamanioBMB = sb.s_blocks_count;
  char temp[tamanioBMB];
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  fseek(archivo,initBMB,SEEK_SET);
  fread(&temp,tamanioBMB,1,archivo);
  for(int i=0;i<tamanioBMB;i++){
      bitmap += temp[i];
    }
  fclose(archivo);
  return bitmap;
}

vector<bm_espacio> retornarEspaciosVacios(string bm){
  vector<bm_espacio> espaciosVacios;
  //obteniendo tamano de cadena para crear un arreglo de char de este tamanio
  int bmSize = bm.length();
  //creando un arreglo para guardar el bitmap
  char bitmap[bmSize];
  //guardando cadena que trae bitmap en el vector de chars
  strcpy(bitmap,bm.c_str());
  //llenando el vector de bm_espacios
  for(int i=0;i<bmSize;i++){
      int bandera = 0;
      int inicio;
      int fin;
      if(bitmap[i] == '0'){
          inicio = i;
          for(int j = i;j<bmSize;j++){
              if(bitmap[j]!='0'){
                  fin = j-1;
                  i = j;
                  bandera = 1;
                  break;
                }else{
                  int temp = j + 1;
                  if(temp==bmSize){
                      fin = bmSize-1;
                      i = j;
                      bandera = 1;
                    }
                }
            }
        }
      if(bandera == 1){
          int tam = fin - inicio + 1;
          cout<<"inicio: "<<inicio<<" fin: "<<fin<<" tamanio: "<<tam<<endl;
          //aqui deberia de ingresar al vector de espacios el bm_espacios
        }
    }
  return espaciosVacios;
}

/////retornar posicion donde va colocado el inodo
int retornarPosicionInodo(int inodeStart , int indiceInodo){
  int calculo = inodeStart + indiceInodo * sizeof(inodo);
  return calculo;
}

/////retornar posicion donde va colocado el bloque
int retornarPosicionBloque(int blockStart , int indiceBloque){
  int calculo = blockStart + indiceBloque* sizeof(bloqueCarpetas);
  return calculo;
}

inodo retornarInodo(string path,int partInit,int indice){
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  superBloque sbTemp (retornarSuperBloque(path,partInit));
  int posIno = retornarPosicionInodo(sbTemp.s_inode_start,indice);
  inodo inoTemp;
  fseek(archivo, posIno, SEEK_SET);
  fread(&inoTemp,sizeof(inodo),1,archivo);
  fclose(archivo);
  return inoTemp;
}

bloqueArchivos retornarBloqueArchivos(string path,int partInit,int indice){
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  superBloque sbTemp (retornarSuperBloque(path,partInit));
  int posBlo = retornarPosicionBloque(sbTemp.s_block_start,indice);
  bloqueArchivos bloTemp;
  fseek(archivo, posBlo, SEEK_SET);
  fread(&bloTemp,sizeof(bloqueArchivos),1,archivo);
  fclose(archivo);
  return bloTemp;
}

bloqueCarpetas retornarBloqueCarpetas(string path,int partInit,int indice){
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  superBloque sbTemp (retornarSuperBloque(path,partInit));
  int posBlo = retornarPosicionBloque(sbTemp.s_block_start,indice);
  bloqueCarpetas bloTemp;
  fseek(archivo, posBlo, SEEK_SET);
  fread(&bloTemp,sizeof(bloqueCarpetas),1,archivo);
  fclose(archivo);
  return bloTemp;
}

void actualizarFechaInodo(string path,int initPart,int ind){
  inodo in = retornarInodo(path,initPart,ind);
  strcpy(in.i_atime,retornarFecha().c_str());
  superBloque sb = retornarSuperBloque(path,initPart);
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  fseek(archivo,retornarPosicionInodo(sb.s_inode_start,ind),SEEK_SET);
  fwrite(&in,sizeof(inodo),1,archivo);
  fclose(archivo);
}

////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// JOURNAL ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
//retorna el journal pivote
journal retornarJournal(string path, int partInit){
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  fseek(archivo,retornarPosicionJournal(partInit,0),SEEK_SET);
  journal journalPivote;
  fread(&journalPivote,sizeof(journal),1,archivo);
  fclose(archivo);
  return journalPivote;
}

//retorna la posicion del journal segun el indice
int retornarPosicionJournal(int partStart,int indice){
  int aux = indice * sizeof(journal);
  int calculo = partStart + sizeof(superBloque) + aux;
  return calculo;
}

//muestra los journal
void recorrerJournal(string path, int partInit){
  journal jorTemp (retornarJournal(path,partInit));
  int ind = jorTemp.Journal_permisos;
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  journal t;
  for(int i = 1;i<ind;i++){
      fseek(archivo,retornarPosicionJournal(partInit,i),SEEK_SET);
      fread(&t,sizeof(journal),1,archivo);
      printf(t.Journal_nombre);
      cout<<t.Journal_permisos<<endl;
      cout<<"\n"<<endl;
    }
  fclose(archivo);
}

//escribir journal
void escribirJournal(string path, int partInit,journal nuevoJournal){
  //obtengo el journal pivote
  journal pivote(retornarJournal(path,partInit));
  //capturo el indice que me servira para el nuevo journal
  int ind = pivote.Journal_permisos;
  //genero un aux que contiene la posicion siguiente que iria otro nuevo journal
  int aux = ind+1;
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  //asigno el aux al pivote
  pivote.Journal_permisos = aux;
  //escribo el posicion para otro nuevo journal en el journal pivote
  fseek(archivo,retornarPosicionJournal(partInit,0),SEEK_SET);
  fwrite(&pivote,sizeof(journal),1,archivo);
  //escribo el nuevo journal
  fseek(archivo,retornarPosicionJournal(partInit,ind),SEEK_SET);
  fwrite(&nuevoJournal,sizeof(journal),1,archivo);
  fclose(archivo);
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// LEER INODOS /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


int recorrerSistemaArchivos(vector<string> ruta, inodo pivote,string path,int initPart){
  int tamR = ruta.size();
  int ind = -1;
  int encontre = 0;
  //actualizando fecha de la raiz
  actualizarFechaInodo(path,initPart,0);
  //recorre el vector de ruta
  for(int i = 0;i<tamR;i++){
      //recorre los punteros del inodo pivote
      ind = -1;
      string direccion =ruta[i];
      for(int j =0;j<12;j++){
          if(pivote.i_block[j]!=-1){
              //buscando el bloque de carpeta
              bloqueCarpetas carpetas (retornarBloqueCarpetas(path,initPart,pivote.i_block[j]));
              for(int k = 0;k<4;k++){
                  //cout<<direccion<<"---"<<carpetas.b_content[k].b_name<<endl;
                  if(direccion == carpetas.b_content[k].b_name){
                      pivote = retornarInodo(path,initPart,carpetas.b_content[k].b_inodo);
                      actualizarFechaInodo(path,initPart,carpetas.b_content[k].b_inodo);
                      ind = carpetas.b_content[k].b_inodo;
                    }
                }

            }
        }
      if(ind == -1){
        break;
      }
    }
  return ind;
}

string recorrerBloqueArchivos(int ind,string path,int initPart){
  string texto;
  inodo nodoArchivo = retornarInodo(path,initPart,ind);
  int limiteCaracteres = nodoArchivo.i_size;
  for(int i = 0;i<12;i++){
    if(nodoArchivo.i_block[i]!=-1){
      bloqueArchivos archivo = retornarBloqueArchivos(path,initPart,nodoArchivo.i_block[i]);
      for (int j = 0; j < limiteCaracteres && j<64; j++)
      {
        texto += archivo.b_content[j];
      }
    }
  }
  return texto;
}
