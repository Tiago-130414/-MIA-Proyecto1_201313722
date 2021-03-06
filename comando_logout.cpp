#include "comando_logout.h"

comando_logout::comando_logout()
{

}

void comando_logout::ejecutarLogout(){
  extern string usuario;
  if(!usuario.empty()){
      usuario = "";
      cout<<"-> sesion cerrada correctamente"<<endl;
    }else{
      cout<<"*** Error al cerrar sesion, no existe ningun usuario en linea ***"<<endl;
    }
}
