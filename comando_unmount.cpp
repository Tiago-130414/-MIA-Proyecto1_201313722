#include "comando_unmount.h"

comando_unmount::comando_unmount()
{

}
//unmount -id=id123
void comando_unmount::ejecutarUnmount(vector<string> parametrosUnmount){
  extern vector <disco> registro;
  int tamanioParametrosUnmount = parametrosUnmount.size();
  int existeID=0;
  string identificador = "";
  for(int i = 0;i<tamanioParametrosUnmount;i++){
      //cout<<parametrosUnmount[i]<<endl;
      if(aMinuscula(parametrosUnmount[i]) == "id"){
          identificador = parametrosUnmount[i+1];
          existeID = 1;
          break;
        }
    }
  //verifico si el parametro obligatorio esta en el comando enviado
  if(existeID == 1){
      cout<<"id->"<<identificador<<endl;
      //buscar en el registro el id proporcionado
      int tamanioRegistro = registro.size();
      int existeParticion = 0;
      for(int i=0;i<tamanioRegistro;i++){
          int tamanioParticiones = registro[i].particiones.size();
          for(int j=0;j<tamanioParticiones;j++){
              if(registro[i].particiones[j].id == identificador){
                  registro[i].particiones.erase(registro[i].particiones.begin() + j);
                  existeParticion = 1;
                  mostrarRegistro();
                  break;
                }
            }
          if(existeParticion==1){
              break;
            }
        }
      if(existeParticion==0){
          cout<<"*** La particion que desea eliminar no existe ***"<<endl;
        }
    }else{
      cout<<"*** Falta comando -id ***"<<endl;
    }
}

