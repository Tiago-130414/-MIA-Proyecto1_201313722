#include "comando_fdisk.h"

comando_fdisk::comando_fdisk()
{

}

void comando_fdisk::ejecutarFdisk(vector<string>fdisk){
  string path;
  string unit = "-1";
  int size = -1;
  string type = "-1";
  string fit  = "-1";
  string name = "-1";
  string p_delete = "-1";
  string p_add = "-1";
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
  int posicionDelete=0;
  //RECOLECTANDO DATO
  for(int i=0;i<fdisk.size();i++){
      if(aMinuscula(fdisk[i])=="path"){
          path = fdisk[i+1];
          existPath =1;
        }else if(aMinuscula(fdisk[i])=="u"){
          unit = aMinuscula(fdisk[i+1]);
        }else if(aMinuscula(fdisk[i])=="size"){
          size = stoi(fdisk[i+1]);
          posicionSize= i+1;
          existSize =1;
        }else if(aMinuscula(fdisk[i])=="type"){
          type = aMinuscula(fdisk[i+1]);
        }else if(aMinuscula(fdisk[i])=="f"){
          fit = aMinuscula(fdisk[i+1]);
        }else if(aMinuscula(fdisk[i])=="name"){
          name = fdisk[i+1];
          existName=1;
        }else if(aMinuscula(fdisk[i])=="delete"){
          p_delete = aMinuscula(fdisk[i+1]);
          existDelete =1;
          posicionDelete = i+1;
        }else if(aMinuscula(fdisk[i])=="add"){
          p_add = fdisk[i+1];
          existAdd =1;
          posicionAdd = i+1;
        }
    }
  //verificando si vienen los parametros obligatorios
  if(existName && existPath){
      if(existAdd==0 && existDelete==1||existAdd==1 && existDelete==0){
          //si existe el size es por que se creara una particion
          if(existSize){
              //si existe agregar/disminuir espacio
              if(existAdd){
                  //si el size llego antes que el add
                  if(posicionSize<posicionAdd){
                      //se crea particion
                    }else{
                      //se agrega o disminuye tamano de particion
                    }
                }else if(existDelete){
                  //si el size llego antes que el delete
                  if(posicionSize<posicionDelete){
                      //se crea particion
                    }else{
                      //se elimina particion
                    }
                }
              //si no esta solo se puede eliminar y agregar espacio o disminuir
            }else{
              if(existAdd){
                  //se agrega/disminuye tamano de particion
                }else if(existDelete){
                  //se elimina particion
                }else{
                  cout<<"*** Falta parametro -size para crear un disco ***"<<endl;
                }
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

void comando_fdisk::crearParticion(int size,string unit,string path,string type,string name,string fit){
  //obligatorio size, path, name
  FILE *archivo;
  int tamanioParticion = 0;
  vector<string> rutaD (descomponerRuta(path));
  string nombreArchivo = rutaD[rutaD.size()-1];
  if(extensionRutaValida(nombreArchivo)){
      archivo = fopen(path.c_str(),"rb+");
      if(archivo!=NULL){
          fseek(archivo,0,SEEK_SET);//este es el inicion del archivo
          mbr mbrTemp; //mbr temporal donde se guardaran los datos que se lean del archivo
          fread(&mbrTemp,sizeof(mbr),1,archivo);//mbrTemp donde se guarda, size el tamano del mbr que se lee, 1 es la cantidad de elementos que se leen y archivo es el disco
          //verificando el tipo de unidad dato en el que se creara la unidad
           if(unit == "-1"){
               unit = "K";
             }
           //calculando el tamanio de la particion
           if(unit == "b"){
               tamanioParticion = size;
             }else if(unit == "k"){
               tamanioParticion = size *1024;
             }else if(unit == "m"){
               tamanioParticion = size*1024*1024;
             }
            //aqui va lo del fit - tipo de ajuste


        }else{
          cout<<"*** Error el disco a particionar no existe! ***"<<endl;
        }
    }else{
      cout<<"*** La extension del archivo proporcionado no es valida ***"<<endl;
    }
}





