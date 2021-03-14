#include "comando_logout.h"

comando_logout::comando_logout()
{

}

void comando_logout::ejecutarLogout(){
  extern string usuario;
  extern datosUSR infoUSR;
  if(!usuario.empty()){
      usuario = "";
      infoUSR.usuario = "";
      infoUSR.contrasena = "";
      infoUSR.idParticion = "";
      infoUSR.nombreParticion = "";
      infoUSR.rutaDisco = "";
      cout<<"-> sesion cerrada correctamente"<<endl;
    }else{
      cout<<"*** Error al cerrar sesion, no existe ningun usuario en linea ***"<<endl;
    }
}
