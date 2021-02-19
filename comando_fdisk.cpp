#include "comando_fdisk.h"

comando_fdisk::comando_fdisk()
{

}

void comando_fdisk::ejecutarFdisk(vector<string>fdisk){
  string path;
  string unit;
  int size = -1;
  string type;
  string fit;
  string name;
  string p_delete;
  string p_add;
  //BOOLEANAS PARA VERIFICAR QUE TIPO DE ACCION SE REALIZARA
  int existAdd=0;
  int existDelete=0;
  //BOOLEANAS QUE VERIFICAN SI VIENEN LOS DATOS OBLIGATORIOS
  int existPath =0;
  int existName =0;
  int existSize =0;
  //ENTEROS QUE GUARDAN LA POSICION DE PARAMETROS SIZE Y ADD
  int posicionSize =0;
  int posicionAdd =0;
  //RECOLECTANDO DATO
  for(int i=0;i<fdisk.size();i++){
      if(aMinuscula(fdisk[i])=="path"){
          path = fdisk[i+1];
          existPath =1;
        }else if(aMinuscula(fdisk[i])=="u"){
          unit = fdisk[i+1];
        }else if(aMinuscula(fdisk[i])=="size"){
          size = stoi(fdisk[i+1]);
          posicionSize= i+1;
          existSize =1;
        }else if(aMinuscula(fdisk[i])=="type"){
          type = fdisk[i+1];
        }else if(aMinuscula(fdisk[i])=="f"){
          fit = fdisk[i+1];
        }else if(aMinuscula(fdisk[i])=="name"){
          name = fdisk[i+1];
          existName=1;
        }else if(aMinuscula(fdisk[i])=="delete"){
          p_delete = fdisk[i+1];
          existDelete =1;
        }else if(aMinuscula(fdisk[i])=="add"){
          p_add = fdisk[i+1];
          existAdd =1;
          posicionAdd = i+1;
        }
    }

  if(existName && existPath){
      if(existAdd==0 && existDelete==1||existAdd==1 && existDelete==0){
          if(existAdd == 1){
              //agregar particion
              if(existSize){

                }else{
                  cout<<"*** Se necesita parametro -size para crear particion ***"<<endl;
                }
            }else{
              //eliminar particion
            }
        }else{
          cout<<"*** Parametros exist y add no se pueden ejecutar al mismo tiempo ***"<<endl;
        }
    }else{
      if(existName==1){
          cout<<"*** Parametro -path faltante para completar comando fdisk ***"<<endl;
        }else{
          cout<<"*** Parametro -name faltante para completar comando fdisk ***"<<endl;
        }
    }
}


