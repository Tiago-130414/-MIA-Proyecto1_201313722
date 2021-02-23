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
          name = aMinuscula(fdisk[i+1]);
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
      //falta agregar el caso de que no vengan ninguno de los 2
      if(existAdd==0 && existDelete==1||existAdd==1 && existDelete==0 || existAdd==0 && existDelete ==0){
          //si existe el size es por que se creara una particion
          if(existSize){
              //si existe agregar/disminuir espacio
              if(existAdd){
                  //si el size llego antes que el add
                  if(posicionSize<posicionAdd){
                      //se crea particion
                      if(validarParametrosOpcionales(unit,type,fit)==1){
                          crearParticion(size,unit,path,type,name,fit);
                        }
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
                }else{
                  //si no viene delete ni add
                  if(validarParametrosOpcionales(unit,type,fit)==1){
                      crearParticion(size,unit,path,type,name,fit);
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
      string rTemporal = rRuta(rutaD) + "/"+nombreArchivo;
      cout<<rTemporal<<endl;
      archivo = fopen(rTemporal.c_str(),"rb+");
      if(archivo!=NULL){
          fseek(archivo,0,SEEK_SET);//este es el inicion del archivo
          mbr mbrTemp; //mbr temporal donde se guardaran los datos que se lean del archivo
          fread(&mbrTemp,sizeof(mbr),1,archivo);//mbrTemp donde se guarda, size el tamano del mbr que se lee, 1 es la cantidad de elementos que se leen y archivo es el disco
          //verificando el tipo de unidad dato en el que se creara la unidad
          if(unit == "-1"){
              unit = "k";
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
          char fitT;
          if(fit == "-1"){
              fit = "wf";
            }
          if(fit == "bf"){
              fitT = 'B';
            }else if(fit == "ff"){
              fitT = 'F';
            }else if(fit == "wf"){
              fitT = 'W';
            }
          //verificando valor del type
          char typeT;
          if(type == "-1"){
              type= "p";
            }
          if(type == "p" ){
              typeT = 'P';
            }else if(type == "e"){
              typeT = 'E';
            }else if(type == "l"){
              typeT = 'L';
            }


          //primero obtengo el tamano del disco
          int tamanoDisco = mbrTemp.mbr_tamano;
          if(tamanioParticion<tamanoDisco){
              //obtengo el espacio ocupado
              int espacioOcupado = 0;
              for(int i=0;i<4;i++){
                  if(mbrTemp.mbr_particiones[i].part_status == '1'){
                      espacioOcupado += mbrTemp.mbr_particiones[i].part_size;
                    }
                }
              //sumo el tamano del mbr
              espacioOcupado += sizeof(mbr);
              //obtengo el espacio disponible
              int espacioDisponible = tamanoDisco - espacioOcupado;
              if(tamanioParticion<=espacioDisponible){
                  //si se puede insertar particion

                  //verificando la cantidad de particiones de cada tipo que hay
                  int pPrimarias = 0;
                  int pExtendidas = 0;
                  int existeNombre = 0;
                  int particionesActivas = 0;
                  for(int i=0;i<4;i++){
                      int aux = validarNombre(mbrTemp.mbr_particiones[i].part_name,name);
                      if(aux == 1){
                          existeNombre = 1;
                          break;
                        }
                      if(mbrTemp.mbr_particiones[i].part_type == 'P' && mbrTemp.mbr_particiones[i].part_status == '1'){
                          pPrimarias +=1;
                          particionesActivas+=1;
                        }else if(mbrTemp.mbr_particiones[i].part_type == 'E' && mbrTemp.mbr_particiones[i].part_status == '1'){
                          pExtendidas +=1;
                          particionesActivas+=1;
                        }
                    }

                  //validando cantidad de particiones
                  int agregoParticion = 0; //variable booleana que me sirve para saber si se agrega o no la particion al disco
                  if(existeNombre==0){
                      if(typeT == 'P'|| typeT == 'E'){
                          if(typeT == 'P' && pPrimarias == 3){
                              cout<<"*** Error no pueden haber mas de 3 particiones primarias ***"<<endl;
                            }else if(typeT == 'E' && pExtendidas == 1){
                              cout<<"*** Error no pueden haber mas de 1 particiones extendida ***"<<endl;
                            }else{
                              //si no hay error en la cantidad de particiones se procede a agregar dicha particion
                              for(int i = 0;i<4;i++){
                                  if(mbrTemp.mbr_particiones[i].part_status == '0'){
                                      mbrTemp.mbr_particiones[i].part_status = '1';
                                      mbrTemp.mbr_particiones[i].part_fit = fitT;
                                      mbrTemp.mbr_particiones[i].part_size = tamanioParticion;
                                      //mbrTemp.mbr_particiones[i].part_start = sizeof(mbr) +1 ;
                                      int part_start = 0;
                                      if(particionesActivas == 0){
                                          part_start = sizeof(mbr)+1;
                                        }else{
                                          part_start = mbrTemp.mbr_particiones[i-1].part_start + 1;
                                          part_start = part_start + mbrTemp.mbr_particiones[i-1].part_size;
                                        }
                                      mbrTemp.mbr_particiones[i].part_start = part_start ;
                                      strcpy(mbrTemp.mbr_particiones[i].part_name,name.c_str());
                                      mbrTemp.mbr_particiones[i].part_type = typeT;
                                      agregoParticion = 1;
                                      break;
                                    }
                                }
                            }
                        }else if(typeT == 'L' && pExtendidas == 1){
                          //falta agregar particiones logicas
                        }
                    }else{
                      cout<<"*** El nombre de particion que ingreso ya existe ***"<<endl;
                    }
                  //si se pudo crear la particion se escribe en el archivo
                  if(agregoParticion==1){
                      fseek(archivo, 0, SEEK_SET);//QUEREMOS modificar en donde estaba el MBR original
                      fwrite(&mbrTemp, sizeof(mbr), 1, archivo);
                      fclose(archivo);
                      imprimirInfo(rTemporal);
                    }
                }else{
                  cout<<"*** El espacio disponible es menor al tamano de la particion ***"<<endl;
                }
            }else{
              cout<<"*** El tamano de la particion que desea ingresar es mayor que el disco ***"<<endl;
            }

        }else{
          cout<<"*** Error el disco a particionar no existe! ***"<<endl;
        }
    }else{
      cout<<"*** La extension del archivo proporcionado no es valida ***"<<endl;
    }
}

//funcion que verifica el nombre contenido en el mbr y el nombre nuevo de la particion
int comando_fdisk::validarNombre(char nomb[16],string nomb2){
  int igual = 0;
  string nombre1;
  for(int i=0;i<16;i++){
      nombre1 += nomb[i];
    }
  if(strcmp(nombre1.c_str(), nomb2.c_str())==0){
      igual = 1;
    }
  return igual;
}

//funcion que valida que los parametros opcionales se encuentren en los que corresponden
int comando_fdisk::validarParametrosOpcionales(string unit,string type,string fit){
  int valido = 0;
  if(unit == "-1"||unit == "b"||unit == "k"||unit == "m"){
      if(type == "-1"||type == "p"||type == "e"||type == "l"){
          if(fit == "-1"||fit == "bf"||fit == "ff"||fit == "wf"){
              valido = 1;
            }else{
              cout<<"*** El valor ingresado en el parametro fit no corresponde con ninguno de los permitidos ***"<<endl;
            }
        }else{
          cout<<"*** El valor ingresado en type no corresponde con ninguno de los permitidos ***"<<endl;
        }
    }else {
      cout<<"*** El valor ingresado en unit no corresponde con ninguno de los permitidos ***"<<endl;
    }
  return valido;
}
