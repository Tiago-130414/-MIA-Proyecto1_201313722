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
