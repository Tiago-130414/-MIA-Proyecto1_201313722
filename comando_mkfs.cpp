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
              //cout<<tType<<endl;
              //cout<<tFS<<endl;
              //cout<<id<<endl;
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
