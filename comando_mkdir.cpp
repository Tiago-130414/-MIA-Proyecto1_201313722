#include "comando_mkdir.h"

comando_mkdir::comando_mkdir()
{

}

void comando_mkdir::ejecutarMkdir(vector<string> parametrosMkdir){
  //cout<<" tamanio "<<parametrosMkdir.size()<<endl;
  //informacion de mkdir
  string path;
  //booleana si existe parametro obligatorio
  int existePath = -1;
  int existeP = -1;
  for(int i =0 ;i<parametrosMkdir.size();i++){
      //cout<<parametrosMkdir[i]<<endl;
      if(aMinuscula(parametrosMkdir[i]) == "path" ){
          path = quitarComillas(parametrosMkdir[i+1]);
          existePath =1;
        }else if(aMinuscula(parametrosMkdir[i]) == "p" ){
          existeP = 1;
        }
    }
  //verificando parametros obligatorios
  if(existePath == 1){
      generarCarpeta(path,existeP);
    }else{
      cout<<"*** Es necesario tener una ruta para poder crear carpetas ***"<<endl;
    }
}

void comando_mkdir:: generarCarpeta(string path,int existeP){
  //path es la ruta que se crea
  extern datosUSR infoUSR;

  if(infoUSR.usuario != ""){
      //vector que tiene ruta completa
      vector <string> carpetas = descomponerRuta(path);
      //evaluando si se envio la raiz como ruta para crear
      if(carpetas[0].empty() && carpetas.size()==1){
          cout<<"*** Error se envio la raiz como ruta ***"<<endl;
        }else{
          //vector que tiene las carpetas padre (hasta una posicion antes de la que se tiene que crear)
          vector <string> carpetasPadre;
          //obteniendo carpetas padre
          for(int i = 0;i<carpetas.size()-1;i++){
              carpetasPadre.push_back(carpetas[i]);
            }

          cout<<"\n-> Informacion"<<endl;
          cout<<" -"<<infoUSR.usuario<<endl;
          cout<<" -"<<infoUSR.rutaDisco<<endl;
          cout<<" -"<<infoUSR.idParticion<<"\n"<<endl;
          //ruta del disco en el que se inicio sesion
          string pathDisco = infoUSR.rutaDisco;
          //nombre de la particion
          string nombreParticion = infoUSR.nombreParticion;
          //particion que tiene el sistema de archivos que se esta usando
          particion particionUsada = retornarParticion(pathDisco,nombreParticion);

          //inicio de la particion
          int inicioParticion = particionUsada.part_start;

          //verificar si la ruta completa existe
          int exist = buscarCarpeta(carpetas,pathDisco,inicioParticion);
          //cout<<exist<<endl;
          //validando si se puede crear la ruta
          if(exist != 1){
              //cout<<"comenzando"<<endl;
              //verificando las carpetas padre
              int existCP = buscarCarpeta(carpetasPadre,pathDisco,inicioParticion);
              //cout<<"CP"<<existCP<<endl;//si es -1 significa que hay que crearlas
              if(existeP == 1){
                  //si existe p se pueden crear carpetas o no se hace nada
                  if(existCP == 1){
                      //si existen las carpetas padre no se hace nada y se agrega la carpeta nueva
                    }else{
                      //si no existen se crean las carpetas que faltan
                      //guarda el indice de donde hace falta la ruta
                      int indF = rutaFaltanteCarpeta(carpetasPadre,pathDisco,inicioParticion);
                      //ruta faltante -> cout<<rRutaFaltante(carpetasPadre,indF)<<rRutaFaltante(carpetasPadre,indF).length()<<endl;
                      //ultimo inodo  -> cout<<"UltIno"<<retornarIndiceUltimoInodo(carpetas,pathDisco,inicioParticion)<<endl;
                      //cout<<"UltBlo"<<retornarIndiceUltimoBloque(carpetas,pathDisco,inicioParticion)<<endl;
                    }
                }else{
                  if(existCP == 1){
                      //se procede a crear carpeta nueva
                    }else{
                      cout<<"*** Se necesita el parametro p, ya que hay carpetas que se necesitan crear***"<<endl;
                    }
                }
            }else{
              //si ya existe se marca error
              cout<<"*** La carpeta que desea crear ya existe ***"<<endl;
            }
        }

    }else{
      cout<<"*** Necesita iniciar sesion en una particion ***"<<endl;
    }
}
//metodo que retorna la ruta faltante
string comando_mkdir::rRutaFaltante(vector<string> ruta,int ind){
  string cad = "";
  for(int i = ind;i<ruta.size();i++){
      cad+= "/" + ruta[i];
    }
  return cad;
}

