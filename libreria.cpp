#include "libreria.h"

//METODOS STRING PARA PASAR DE MAYUSCULA A MINUSCULA
string aMayuscula(string cadena) {
  for (int i = 0; i < cadena.length(); i++) cadena[i] = toupper(cadena[i]);
  return cadena;
}
string aMinuscula(string cadena) {
  for (int i = 0; i < cadena.length(); i++) cadena[i] = tolower(cadena[i]);
  return cadena;
}

//METODO QUE RETORNA LA RUTA COMO STRING
string rRuta(vector<string> path){
  string ruta="";
  for(int i =0;i<path.size()-1;i++){
      ruta +="/" + path[i];
    }
  return ruta;
}

//METODO QUE RETORNA UN ARRAY CON TODAS LAS CARPETAS
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

//METODO QUE QUITA COMILLAS EN DADO CASO VENGAN
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

//METODO QUE EVALUA LA EXTENSION
bool extensionRutaValida(string nombreArchivo){
  vector<string> archivo;
  int posInit = 0;
  int posFound = 0;
  string splitted;
  string pattern = ".";
  string extension;
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

//METODO QUE IMPRIME VALORES DENTRO DE DISCO (MBR)
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
