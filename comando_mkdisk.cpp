#include "comando_mkdisk.h"
comando_mkdisk::comando_mkdisk()
{

}
//METODO QUE RECIBE VALORES DE BISON Y EJECUTA EL CREAR DISCO
void comando_mkdisk::ejecutarMkdisk(vector<string> mkdiskP){
  //temporales
  int ePath = 0; //existe path
  int eSize = 0; //existe size
  //atributos del disco
  int size = 0;
  string path = "";
  string unit = "-1";
  string fit = "-1";
  //recorriendo vector con datos de comando mkdisk
  for(int i = 0;i<mkdiskP.size();i++){
      if(aMinuscula(mkdiskP[i])=="size"){
          eSize = 1;
          size = stoi(mkdiskP[i+1],nullptr,16);
        }else if(aMinuscula(mkdiskP[i])=="path"){
          ePath = 1;
          path = mkdiskP[i+1];
        }else if(aMinuscula(mkdiskP[i])=="f"){
          fit = mkdiskP[i+1];
        }else if(aMinuscula(mkdiskP[i])=="u"){
          unit = mkdiskP[i+1];
        }
    }
  //validando comandos necesarios para crear disco
  if(ePath!=0&&eSize!=0){
      crearDisco(size,path,unit,fit);
    }else{
      cout<<"Parametros obligatorio faltante"<<endl;
    }
}
//CREA EL DISCO CON PARAMETROS OBTENIDOS
void comando_mkdisk::crearDisco(int size,string path,string unit,string fit){

}

//METODOS STRING PARA PASAR DE MAYUSCULA A MINUSCULA
string comando_mkdisk::aMayuscula(string cadena) {
  for (int i = 0; i < cadena.length(); i++) cadena[i] = toupper(cadena[i]);
  return cadena;
}
string comando_mkdisk::aMinuscula(string cadena) {
  for (int i = 0; i < cadena.length(); i++) cadena[i] = tolower(cadena[i]);
  return cadena;
}
