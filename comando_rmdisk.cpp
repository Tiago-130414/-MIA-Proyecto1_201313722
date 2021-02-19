#include "comando_rmdisk.h"

comando_rmdisk::comando_rmdisk()
{

}

void comando_rmdisk::eliminarDisco(vector<string> ruta){
  string path;
  string nombreArchivo;
  string rArchivo;
  path = ruta[0];
  FILE *archivo;
  //OBTENGO UN ARRAY CON SPLIT POR SLASH
  vector <string> carpetas(descomponerRuta(path));
  //OBTENGO EL NOMBRE DEL ARCHIVO
  nombreArchivo = carpetas[carpetas.size()-1];
  //VERIFICO LA EXTENSION DEL ARCHIVO
  if(extensionRutaValida(nombreArchivo)){
      //OBTENGO RUTA COMPLETA CON NOMBRE DE ARCHIVO Y EXTENSION
      rArchivo = rRuta(carpetas) +"/"+nombreArchivo;
      //BUSCO EL ARCHIVO EN MODO LECTURA
      archivo = fopen(rArchivo.c_str(),"r");
      //VERIFICO SI EXISTE
      if(archivo!=NULL){
          //CIERRO EL ARCHIVO
          fclose(archivo);
          //ELIMINO EL ARCHIVO
          string op;
          cout<<"Desea eliminar disco [s/n]:"<<endl;
          cin>>op;
          op= aMinuscula(op);
          if(op=="s"){
              remove(rArchivo.c_str());
              cout<<"Disco eliminado con exito"<<endl;
            }else if(op =="n"){
              cout<<"Eliminacion cancelada por usuario"<<endl;
            }
        }else{
          //SI HAY ALGUN PROBLEMA AL ABRIR EL ARCHIVO
          cout<<"El disco buscado no se encuentra"<<endl;
        }
    }else{
      //SI LA EXTENSION DEL ARCHIVO NO EXISTE
      cout<<"Archivo a elminar con extension no valida"<<endl;
    }
}

bool comando_rmdisk::confirmarEliminarArchivo(){
  string op;
  int aux=1;
  bool answer = false;
  while(aux==1){
      cout<<"Desea eliminar disco [s/n]:"<<endl;
      cin>>op;
      op= aMinuscula(op);
      if(op=="s"){
          answer=true;
          aux =0;
        }else if(op =="n"){
          answer=false;
          aux=0;
        }
    }
  return answer;
}
