#include "comando_mount.h"

comando_mount::comando_mount()
{

}
//funcion que ejecuta el mount de discos
void comando_mount::ejecutarMount(vector <string> parametrosMount){
  extern vector <disco> registro;
  //int numeroDisco = registro.size();//tamano que me sirve para generar el id
  int tamanioParametrosMount = parametrosMount.size(); //tamanio para recorrer el vector de informacion que me enviaron de gramatica
  string path;
  string name;
  int existPath = 0;
  int existName =0;
  for(int i = 0;i<tamanioParametrosMount;i++){
      if(aMinuscula(parametrosMount[i]) == "path"){
          path = quitarComillas(parametrosMount[i+1]);
          existPath = 1;
        }else if(aMinuscula(parametrosMount[i])=="name"){
          name = quitarComillas(parametrosMount[i+1]);
          name = aMinuscula(name);
          existName=1;
        }
    }
  if(existPath == 1){
      if(existName ==1){
          FILE *archivo;//creo un archivo para verificar la existencia del disco
          vector<string> rutaD (descomponerRuta(path)); //separo por diagonales la direccion
          string nombreArchivo = rutaD[rutaD.size()-1];
          if(extensionRutaValida(nombreArchivo)){
              string rTemporal = rRutaDeArchivo(rRuta(rutaD),nombreArchivo); //formo nuevamente la ruta sin comillas y con la extension validada
              archivo = fopen(rTemporal.c_str(),"rb"); //abriendo el archivo para verificar su existencia
              if(archivo!=NULL){
                  fclose(archivo);
                  //validar si existe en el disco, la particion que enviaron
                  if(existeParticion(name,rTemporal)==1){
                      //verificando si el disco existe en el registro
                      if(existeDisco(rTemporal)==1){
                          int tamanioRegistro = registro.size();
                          for(int i = 0;i<tamanioRegistro;i++){
                              //si las rutas son iguales
                              if(strcmp(registro[i].path.c_str(), path.c_str())==0){
                                  int numeroParticiones = registro[i].particiones.size();
                                  //recorro el vector de las particiones
                                  int encontreParticion =0;
                                  for(int j=0;j<numeroParticiones;j++){
                                      //busco si la particion ya esta montada
                                      if(registro[i].particiones[j].nombre == name){
                                          encontreParticion =1;
                                          break;
                                        }
                                    }
                                  if(encontreParticion == 0){
                                      //aqui va la nueva particion
                                      particionMontada nuevaParticion;
                                      int numeroDisco = registro.size() +1;
                                      nuevaParticion.id = generarID(registro[i].id,numeroParticiones);
                                      nuevaParticion.nombre = name;
                                      registro[i].particiones.push_back(nuevaParticion);
                                      mostrarRegistro();
                                      break;
                                    }else{
                                      cout<<"*** La particion buscada ya se encuentra montada en el registro ***"<<endl;
                                      break;
                                    }
                                }
                            }
                        }else{
                          // si no existe el disco hay que crear uno nuevo en el registro
                          particionMontada nuevaParticion;
                          disco nuevoDisco;
                          int numeroDisco = registro.size() +1;
                          //llenando particion
                          nuevaParticion.id = generarID(numeroDisco,0);
                          nuevaParticion.nombre = name;
                          //creando disco nuevo
                          nuevoDisco.id =numeroDisco;
                          nuevoDisco.path = path;
                          //insertando
                          nuevoDisco.particiones.push_back(nuevaParticion);
                          registro.push_back(nuevoDisco);
                          mostrarRegistro();
                        }
                    }else{
                      cout<<"*** La particion buscada no se encuentra"<<endl;
                    }
                }else{
                  cout<<"*** El disco buscado no se encuentra ***"<<endl;
                }

            }else{
              cout<<"*** La extension del disco no es valida ***"<<endl;
            }
        }else{
          cout<<"*** Falta parametro obligatorio -name***"<<endl;
        }
    }else{
      cout<<"*** Falta parametro obligatorio -path***"<<endl;
    }
}

//metodo que retorna IDS para las particiones
string comando_mount::generarID(int numeroDisco,int numeroParticiones){
  string id = "22";
  int letra = 65 + numeroParticiones;
  char letraTemp = (char)letra;
  id += to_string(numeroDisco) + letraTemp;
  return id;
}

//metodo que valida la existencia de una particion por su nombre dentro de un disco
int comando_mount::existeParticion(string name,string path){
  int existe=0;
  FILE *archivo;//creo un archivo
  archivo = fopen(path.c_str(),"rb");//abro el archivo
  if(archivo!=NULL){
      fseek(archivo, 0, SEEK_SET); //me posiciono en el inicio del disco
      mbr MBR;//creo un MBR temporal que guardara el ya creado en el disco
      fread(&MBR,sizeof(mbr),1,archivo);//leo el MBR  y asigno al temporal
      //recorro el vector de particiones en busca de la particion correspondiente por nombre
      for(int i=0;i<4;i++){
          string nomParticion (MBR.mbr_particiones[i].part_name);
          if(nomParticion == name){
              existe =1;
              break;
            }
        }
    }else{
      cout<<"problema al abrir el archivo en comando mount"<<endl;
    }
  fclose(archivo);
  return existe;
}

//metodo que busca las rutas en el registro
int comando_mount::existeDisco(string ruta){
  extern vector <disco> registro;
  int tamanioRegistro = registro.size();
  int existe = 0;
  for(int i = 0;i<tamanioRegistro;i++){
      string ruta2 = registro[i].path;
      if(strcmp(ruta2.c_str(), ruta.c_str())==0){
          existe = 1;
          break;
        }
    }
  return existe;
}

void comando_mount::mostrarRegistro(){
  extern vector <disco> registro;
  int tamanioRegistro = registro.size();
  for(int i =0;i<tamanioRegistro;i++){
      int tamanioParticiones = registro[i].particiones.size();
      cout<<"\n*** DISCO ***"<<endl;
      cout<<"ID disco: "<<registro[i].id<<endl;
      cout<<"Ruta disco: "<<registro[i].path<<endl;
      for(int j=0;j<tamanioParticiones;j++){
          cout<<endl;
          cout<<"*** PARTICION "<<j<<" ***"<<endl;
          cout<<"ID particion: "<<registro[i].particiones[j].id<<endl;
          cout<<"Nombre particion: "<<registro[i].particiones[j].nombre<<endl;
        }
    }
}
