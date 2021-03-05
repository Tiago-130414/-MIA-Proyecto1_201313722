#include "comando_login.h"

comando_login::comando_login()
{

}

void comando_login::ejecutarLogin(vector<string> parametrosLogin){
  int tamParam = parametrosLogin.size();
  //booleanas que me confirman si todos los parametros existen
  int existUsuario = 0;
  int existPassword = 0;
  int existId = 0;
  //variables que guardaran los datos que se recolectaron
  string usuario;
  string password;
  string id;
  for(int i=0;i<tamParam;i++){
      if(aMinuscula(parametrosLogin[i])=="usr"){
          usuario = quitarComillas(parametrosLogin[i+1]);
          existUsuario = 1;
        }else if(aMinuscula(parametrosLogin[i])=="pwd"){
          password = quitarComillas(parametrosLogin[i+1]);
          existPassword = 1;
        }else if(aMinuscula(parametrosLogin[i])=="id"){
          id = parametrosLogin[i+1];
          existId = 1;
        }
    }

  if(existUsuario==1 && existPassword==1 && existId==1){
      validarDatos(usuario,password,id);
    }else{
      if(existUsuario == 0){
          cout<<"*** El parametro -usr faltante para iniciar sesion ***"<<endl;
        }else if(existPassword == 0){
          cout<<"*** El parametro -pwd faltante para iniciar sesion ***"<<endl;
        }else if(existId == 0){
          cout<<"*** El parametro -id faltante para iniciar sesion ***"<<endl;
        }
    }
}

void comando_login::validarDatos(string usuario, string password,string id){
  int idDisco = stoi(retornarIndiceDisco(id));
  string pathDisco = retornarPathDisco(idDisco);
  string nombreParticion = retornarNombreParticion(idDisco,id);
  if(pathDisco != "-1"){
      if(nombreParticion != "-1"){
          particion particionTemp = retornarParticion(pathDisco,nombreParticion);
          string contenidoArchivoUsr = "1,G,root\n";
          contenidoArchivoUsr += "1,U,root,root,123\n";
          vector<string> temp(obtenerDatos(contenidoArchivoUsr));
        }else{
          cout<<"*** La particion que se busco para iniciar sesion no se encuentra montada ***"<<endl;
        }
    }else{
      cout<<"*** El disco que busca para iniciar sesion no se encuentra ***"<<endl;
    }
}


vector<string> comando_login::obtenerDatos(string usuarios){
  vector<string> datos;
  int posInit = 0;
  int posFound = 0;
  string splitted;
  string pattern = "\n";
  //cout<<rTemp<<endl;
  vector<string> usuario;
  while(posFound >= 0){
      posFound = usuarios.find(pattern, posInit);
      splitted = usuarios.substr(posInit, posFound - posInit);
      posInit = posFound + 1;
      usuario = splitPorComasUSR(splitted);
    }
  return datos;
}

vector<string> comando_login::splitPorComasUSR(string usuario){
  vector<string> datos;
  int posInit = 0;
  int posFound = 0;
  string splitted;
  string pattern = ",";
  while(posFound >= 0){
      posFound = usuario.find(pattern, posInit);
      splitted = usuario.substr(posInit, posFound - posInit);
      posInit = posFound + 1;
      datos.push_back(splitted);
    }
  analizarUsuarios(datos);
  return datos;
}

void comando_login::analizarUsuarios(vector<string> usuario){
  datosUSR nuevoUsr;
  if(usuario.size()==5){
      cout<<usuario[3]<<endl;
      cout<<usuario[4]<<endl;
    }
}




