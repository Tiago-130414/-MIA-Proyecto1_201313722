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
          int initPart = particionTemp.part_start;
          superBloque sb (retornarSuperBloque(pathDisco,particionTemp.part_start));
          if(sb.s_filesystem_type != 2 ||sb.s_filesystem_type != 3){
              inodo primerInodo(retornarInodo(pathDisco,initPart,0));
              vector<string> ruta (descomponerRuta("/users.txt"));
              int temp = recorrerSistemaArchivos(ruta, primerInodo,pathDisco,initPart);
              string usuariosArchivo = recorrerBloqueArchivos(temp,pathDisco,initPart);
              if(!usuariosArchivo.empty()){
                  vector<datosUSR> temp(obtenerDatos(usuariosArchivo));
                  realizarLogin(temp,usuario,password);
                }
            }else{
              cout<<"*** No existe un sistema de archivos ***"<<endl;
            }
        }else{
          cout<<"*** La particion que se busco para iniciar sesion no se encuentra montada ***"<<endl;
        }
    }else{
      cout<<"*** El disco que busca para iniciar sesion no se encuentra ***"<<endl;
    }
}

vector<datosUSR> comando_login::obtenerDatos(string usuarios){
  vector<datosUSR> datos;
  int posInit = 0;
  int posFound = 0;
  string splitted;
  string pattern = "\n";
  while(posFound >= 0){
      posFound = usuarios.find(pattern, posInit);
      splitted = usuarios.substr(posInit, posFound - posInit);
      posInit = posFound + 1;
      vector <datosUSR> temp(splitPorComasUSR(splitted));
      copy(temp.begin(),temp.end(),back_inserter(datos));
    }
  return datos;
}

vector<datosUSR> comando_login::splitPorComasUSR(string usuario){
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
  vector<datosUSR> usuariosEnInodos;
  datosUSR usr (analizarUsuarios(datos));
  if(!usr.usuario.empty() && usr.usuario!="-1"){
      usuariosEnInodos.push_back(usr);
    }
  return usuariosEnInodos;
}

datosUSR comando_login::analizarUsuarios(vector<string> usuario){
  datosUSR nuevoUsr;
  if(usuario.size()==5){
      nuevoUsr.usuario = usuario[3];
      nuevoUsr.contrasena = usuario[4];
    }else{
      nuevoUsr.usuario == "-1";
      nuevoUsr.contrasena == "-1";
    }
  return nuevoUsr;
}


////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// VALIDAR USUARIOS ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

void comando_login::realizarLogin(vector<datosUSR>usuariosSistema,string nombre,string contra){
  extern string usuario;
  int encontreUS = 0;
  if(usuario.empty()){
      for(int i = 0;i<usuariosSistema.size();i++){
          if(usuariosSistema[i].usuario == nombre){
              if(usuariosSistema[i].contrasena == contra){
                  usuario = nombre;
                  encontreUS = 1;
                  break;
                }
            }
        }
    }else{
      cout<<"*** Ya hay un usuario logueado, es necesario cerrar sesion antes de iniciar una nueva ***"<<endl;
      encontreUS = 2;
    }

  if(encontreUS == 0){
      cout<<"*** Problema con nombre de usuario o contrasena ***"<<endl;
    }else if(encontreUS == 1){
      cout<<"->>> Inicio sesion correctamente "<< nombre<<" <<<-"<<endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// VALIDAR USUARIOS ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
