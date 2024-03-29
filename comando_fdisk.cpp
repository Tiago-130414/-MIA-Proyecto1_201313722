#include "comando_fdisk.h"

comando_fdisk::comando_fdisk()
{

}
//fdisk -size=50 -u=m -path=/home/santi/discos/archivo17.dk -f=ff -name=prueba4
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
  int tamVector = fdisk.size();
  for(int i=0;i<tamVector;i++){
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
          name = quitarComillas(fdisk[i+1]);
          name = name;
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
      if((existAdd==0 && existDelete==1)||(existAdd==1 && existDelete==0) || (existAdd==0 && existDelete ==0)){
          //si existe el size es por que se creara una particion
          if(existSize){
              //si existe agregar/disminuir espacio
              if(existAdd){
                  //si el size llego antes que el add
                  if(posicionSize<posicionAdd){
                      //se crea particion
                      if(validarParametrosOpcionales(unit,type,fit)==1){
                          //si el tamanio de la particion es mayor que 0
                          if(size>0){
                              if(name.length()<17){
                                  crearParticion(size,unit,path,type,name,fit);
                                }else{
                                  cout<<"*** Los nombres de la particion unicamente pueden ser de 16 caracteres ***"<<endl;
                                }
                            }else{
                              cout<<"*** Las particiones unicamente se pueden crear mayores que 0 ***"<<endl;
                            }
                        }
                    }else{
                      //se agrega o disminuye tamano de particion
                    }
                }else if(existDelete){
                  //si el size llego antes que el delete
                  if(posicionSize<posicionDelete){
                      //se crea particion
                      if(size>0){
                          if(name.length()<17){
                              crearParticion(size,unit,path,type,name,fit);
                            }else{
                              cout<<"*** Los nombres de la particion unicamente pueden ser de 16 caracteres ***"<<endl;
                            }
                        }else{
                          cout<<"*** Las particiones unicamente se pueden crear mayores que 0 ***"<<endl;
                        }
                    }else{
                      //se elimina particion
                    }
                }else{
                  //si no viene delete ni add
                  if(validarParametrosOpcionales(unit,type,fit)==1){
                      //si el tamanio de la particion es mayor que 0
                      if(size>0){
                          if(name.length()<17){
                              crearParticion(size,unit,path,type,name,fit);
                            }else{
                              cout<<"*** Los nombres de la particion unicamente pueden ser de 16 caracteres ***"<<endl;
                            }
                        }else{
                          cout<<"*** Las particiones unicamente se pueden crear mayores que 0 ***"<<endl;
                        }
                    }
                }
              //si no esta solo se puede eliminar y agregar espacio o disminuir
            }else{
              if(existAdd){
                  //se agrega/disminuye tamano de particion
                }else if(existDelete){
                  //se elimina particion
                  eliminarParticion(path,name,p_delete);
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
////////////////////////////////////////////////////////////////////
/// \brief comando_fdisk::crearParticion
/// \param size
/// \param unit
/// \param path
/// \param type
/// \param name         METODOS QUE CREAN LAS PARTICIONES
/// \param fit
/////////////////////////////////////////////////////////////////////
void comando_fdisk::crearParticion(int size,string unit,string path,string type,string name,string fit){
  //obligatorio size, path, name
  FILE *archivo;
  int tamanioParticion = 0;
  vector<string> rutaD (descomponerRuta(path));
  string nombreArchivo = rutaD[rutaD.size()-1];
  if(extensionRutaValida(nombreArchivo)){
      string rTemporal = rRutaDeArchivo(rRuta(rutaD),nombreArchivo);
      archivo = fopen(rTemporal.c_str(),"rb+");
      //si el archivo se abrio correctamente
      if(archivo!=NULL){
          ///buscando el tipo de ajuste de la particion para realizar la insercion de la particion
          fseek(archivo, 0, SEEK_SET); //me posiciono en el inicio del archivo
          mbr MBR;//mbr temporal que agarra el mbr que ya esta en el disco
          fread(&MBR,sizeof(mbr),1,archivo);
          char ajusteDisco = MBR.disk_fit[0];
          //numero de particiones libres
          int pVacias = particionesVacias(rTemporal);
          //si hay particiones vacias por agregar
          if(pVacias>0){
              char typeT = validarTipoParticion(type);
              //tipo de particion primaria
              if(typeT == 'P'){
                  int partPrimaria = numeroPartPrimarias(rTemporal);
                  //si el numero de particiones primarias es menor que el limite de las mismas
                  if(partPrimaria<3){
                      //se valida el ajuste
                      char fitT = validarAjuste(fit);
                      //aqui se procede a crear la particion
                      tamanioParticion = tamanoParticionNueva(unit,size);
                      //segun el tipo de ajuste se obtiene el inicio de la particion
                      if(tamanioParticion<MBR.mbr_tamano){
                          if(ajusteDisco == 'B'){
                              //Mejor ajuste
                              vector<vacios> infoEspacios(particionesOcupadas(rTemporal,ajusteDisco));
                              if(validarEspacioParaParticion(tamanioParticion,infoEspacios)==1){
                                  int inicio = posicionMejorAjuste(infoEspacios,tamanioParticion);
                                  escribirParticion(tamanioParticion,inicio,rTemporal,typeT,name,fitT);
                                }else{
                                  cout<<"*** Espacio insuficiente para ingresar particion ***"<<endl;
                                }
                            }else if(ajusteDisco == 'F'){
                              //Primer ajuste
                              vector<vacios> infoEspacios(particionesOcupadas(rTemporal,ajusteDisco));
                              if(validarEspacioParaParticion(tamanioParticion,infoEspacios)==1){
                                  int inicio = posicionPrimerAjuste(infoEspacios,tamanioParticion);
                                  escribirParticion(tamanioParticion,inicio,rTemporal,typeT,name,fitT);
                                }else{
                                  cout<<"*** Espacio insuficiente para ingresar particion ***"<<endl;
                                }
                            }else if(ajusteDisco == 'W'){
                              //Peor ajuste
                              vector<vacios> infoEspacios(particionesOcupadas(rTemporal,ajusteDisco));
                              if(validarEspacioParaParticion(tamanioParticion,infoEspacios)==1){
                                  int inicio = posicionPeorAjuste(infoEspacios,tamanioParticion);
                                  escribirParticion(tamanioParticion,inicio,rTemporal,typeT,name,fitT);
                                }else{
                                  cout<<"*** Espacio insuficiente para ingresar particion ***"<<endl;
                                }
                            }
                        }else{
                          cout<<"*** La particion que desea insertar es mas grande que el disco ***"<<endl;
                        }
                    }else{
                      cout<<"*** El limite de particiones primarias se ha alcanzado ***"<<endl;
                    }

                }else if(typeT == 'E'){
                  //tipo de particion extendida

                }else if(typeT == 'L'){
                  //tipo de particion logica
                }
            }else{
              cout<< "*** Limite de particiones alcanzado ***"<<endl;
            }
        }else{
          cout<<"*** Error el disco a particionar no existe! ***"<<endl;
        }
      fclose(archivo);
    }else{
      cout<<"*** La extension del archivo proporcionado no es valida ***"<<endl;
    }
}

int comando_fdisk::validarEspacioParaParticion(int tamParticion,vector<vacios> espaciosVacios){
  int puedoInsertar = 0;
  int tamEspaciosVacios = espaciosVacios.size();
  for(int i = 0;i<tamEspaciosVacios;i++){
      if(tamParticion <= espaciosVacios[i].espacioLibre){
          puedoInsertar = 1;
          break;
        }
    }
  return puedoInsertar;
}


void comando_fdisk::escribirParticion(int size,int start,string path,char type,string name,char fit){
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  fseek(archivo, 0, SEEK_SET); //me posiciono en el inicio del archivo
  mbr MBR;//mbr temporal que agarra el mbr que ya esta en el disco
  fread(&MBR,sizeof(mbr),1,archivo);
  int indice = 0;
  int nombIgual = 0;
  for(indice;indice<4;indice++){
      nombIgual = validarNombre(MBR.mbr_particiones[indice].part_name,name);
      if(nombIgual== 1){
          break;
        }
    }
  indice = 0;
  if(nombIgual == 0){
      for(indice;indice<4;indice++){
          if(MBR.mbr_particiones[indice].part_status == '0'){
              break;
            }
        }
      MBR.mbr_particiones[indice].part_status = '1';
      MBR.mbr_particiones[indice].part_start = start;
      MBR.mbr_particiones[indice].part_size = size;
      MBR.mbr_particiones[indice].part_type = type;
      MBR.mbr_particiones[indice].part_fit = fit;
      strcpy(MBR.mbr_particiones[indice].part_name,name.c_str());
      fseek(archivo, 0, SEEK_SET);//QUEREMOS modificar en donde estaba el MBR original
      fwrite(&MBR, sizeof(mbr), 1, archivo);
    }else{
      cout<<"*** Ya existe una particion con ese nombre ***"<<endl;
    }
  fclose(archivo);
  imprimirInfo(path);
}

//funcion que retorna si hay particiones libres
int comando_fdisk::particionesVacias(string path){
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  fseek(archivo, 0, SEEK_SET); //me posiciono en el inicio del archivo
  mbr MBR;//mbr temporal que agarra el mbr que ya esta en el disco
  fread(&MBR,sizeof(mbr),1,archivo);
  int nPartitionEmpty = 0;//numero de particiones vacias
  for(int i=0;i<4;i++){
      if(MBR.mbr_particiones[i].part_status == '0'){
          nPartitionEmpty +=1;
        }
    }
  fclose(archivo);
  return nPartitionEmpty;
}

//funcion que retorna cuantas particiones primarias hay
int comando_fdisk::numeroPartPrimarias(string path){
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  fseek(archivo, 0, SEEK_SET); //me posiciono en el inicio del archivo
  mbr MBR;//mbr temporal que agarra el mbr que ya esta en el disco
  fread(&MBR,sizeof(mbr),1,archivo);
  int nPrimaryPartition = 0;//numero de particiones vacias
  for(int i=0;i<4;i++){
      if(MBR.mbr_particiones[i].part_status == '1' && MBR.mbr_particiones[i].part_type == 'P'){
          nPrimaryPartition +=1;
        }
    }
  fclose(archivo);
  return nPrimaryPartition;
}

//funcion que retorna cuantas particiones extendidas hay
int comando_fdisk::numeroPartExtendidas(string path){
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  fseek(archivo, 0, SEEK_SET); //me posiciono en el inicio del archivo
  mbr MBR;//mbr temporal que agarra el mbr que ya esta en el disco
  fread(&MBR,sizeof(mbr),1,archivo);
  int nExtendedPartition = 0;//numero de particiones vacias
  for(int i=0;i<4;i++){
      if(MBR.mbr_particiones[i].part_status == '1' && MBR.mbr_particiones[i].part_type == 'E'){
          nExtendedPartition +=1;
        }
    }
  fclose(archivo);
  return nExtendedPartition;
}

//funcion que valida el unit y retorna el tamano de la particion
int comando_fdisk::tamanoParticionNueva(string unit,int size){
  int tamanioParticion= 0;
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
  return tamanioParticion;
}

//funcion que valida el tipo de ajuste y retorna la letra que representa el ajuste de la particion
char comando_fdisk::validarAjuste(string fit){
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
  return fitT;
}

//funcion que valida el tipo de partcion y retorna la letra que representa el tipo de particon que es
char comando_fdisk::validarTipoParticion(string type){
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
  return typeT;
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

//primero obtener particiones activa(me va a servir para el espacio libre)
vector<vacios> comando_fdisk::particionesOcupadas(string path,char ajuste){
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  fseek(archivo, 0, SEEK_SET); //me posiciono en el inicio del archivo
  mbr MBR;//mbr temporal que agarra el mbr que ya esta en el disco
  fread(&MBR,sizeof(mbr),1,archivo);
  //vector de datos
  vector<espacio> particionesOcupadas;
  //vector de sizes
  vector<int> tamanosP;
  //CON ESTE FOR RECOLECTO LOS DATOS
  for(int i=0;i<4;i++){
      if(MBR.mbr_particiones[i].part_status == '1'){
          espacio part;
          part.inicioParticion = MBR.mbr_particiones[i].part_start;
          part.tamanoParticion = MBR.mbr_particiones[i].part_size;
          particionesOcupadas.push_back(part);
        }
    }
  //ESTE FOR ME SIRVE DE PIVOTE PARA ORDENAR LAS PARTICIONES RECOLECTADAS POR EL INICIO
  int tam = particionesOcupadas.size();
  for(int i =0;i<tam;i++){
      int temp = particionesOcupadas[i].inicioParticion;
      tamanosP.push_back(temp);
    }
  int tamanosPsize= tamanosP.size();
  //ORDENO DE MENOR A MAYOR
  sort(tamanosP.begin(),tamanosP.end());

  //CREO UN VECTOR TEMPORAL PARA RETORNAR ORDENADO EL VECTOR
  vector<espacio> temporal;
  for(int i = 0;i<tamanosPsize;i++){
      int tamTemp = tamanosP[i];
      for(int j =0;j<tam;j++){
          int pOcTemp = particionesOcupadas[j].inicioParticion;
          if(tamTemp == pOcTemp){
              temporal.push_back(particionesOcupadas[j]);
              break;
            }
        }
    }
  //VECTOR DE ESPACIOS LIBRES
  vector<vacios> freeSpaces;
  //VARIABLES PARA CALCULOS
  int espaciosLibres = 0;//variable de espacios libres
  int inicio = sizeof(mbr);
  int inicioParticion = 0;
  int temporalSize = temporal.size();
  //CON ESTE FOR CALCULO LOS ESPACIOS LIBRES
  for(int i = 0;i<temporalSize;i++){
      inicioParticion = temporal[i].inicioParticion;
      espaciosLibres = inicioParticion - inicio;
      if(espaciosLibres>0){
          vacios ajustes;
          ajustes.inicio = inicio;
          ajustes.espacioLibre = espaciosLibres;
          freeSpaces.push_back(ajustes);
        }
      inicio = inicioParticion + temporal[i].tamanoParticion;
    }
  espaciosLibres = MBR.mbr_tamano - inicio;
  if(espaciosLibres>0){
      vacios ajustes;
      ajustes.inicio = inicio;
      ajustes.espacioLibre = espaciosLibres;
      freeSpaces.push_back(ajustes);
    }

  fclose(archivo);
  int fSpSize = freeSpaces.size();
  if(ajuste == 'F'){
      return freeSpaces;
    }else if(ajuste == 'B'){
      for(int i=0;i<fSpSize-1;i++){
          for(int j=i+1;j<fSpSize;j++){
              if(freeSpaces[i].inicio >freeSpaces[j].inicio){
                  vacios aux = freeSpaces[i];
                  freeSpaces[i] = freeSpaces[j];
                  freeSpaces [j] = aux;
                }
            }
        }

    }else if(ajuste == 'W'){
      for(int i=0;i<fSpSize-1;i++){
          for(int j=i+1;j<fSpSize;j++){
              if(freeSpaces[i].inicio <freeSpaces[j].inicio){
                  vacios aux = freeSpaces[j];
                  freeSpaces[j] = freeSpaces[i];
                  freeSpaces [i] = aux;
                }
            }
        }
    }
  return freeSpaces;
}

//primer ajuste
int comando_fdisk::posicionPrimerAjuste(vector<vacios> espaciosLib, int tamano){
  int posStart = 0;
  if(!espaciosLib.empty()){
      int tam = espaciosLib.size();
      for(int i = 0;i<tam;i++){
          if(tamano<espaciosLib[i].espacioLibre){
              posStart = espaciosLib[i].inicio;
              break;
            }
        }
    }
  return posStart;
}

//mejor ajuste
int comando_fdisk::posicionMejorAjuste(vector<vacios> espaciosLib, int tamano){
  int posStart = 0;
  if(!espaciosLib.empty()){
      int tam = espaciosLib.size();
      for(int i = 0;i<tam;i++){
          if(tamano<=espaciosLib[i].espacioLibre){
              posStart = espaciosLib[i].inicio;
              break;
            }
        }
    }
  return posStart;
}

//peor ajuste
int comando_fdisk::posicionPeorAjuste(vector<vacios> espaciosLib, int tamano){
  int posStart = 0;
  if(!espaciosLib.empty()){
      int tam = espaciosLib.size();
      for(int i = 0;i<tam;i++){
          if(tamano<espaciosLib[i].espacioLibre){
              posStart = espaciosLib[i].inicio;
              break;
            }
        }
    }
  return posStart;
}

////////////////////////////////////////////////////////////////////
/// \brief comando_fdisk::crearParticion
/// \param size
/// \param unit
/// \param path
/// \param type
/// \param name    METODOS QUE SIRVEN PARA ELIMINACION DE PARTICIONES
/// \param fit
/////////////////////////////////////////////////////////////////////

void comando_fdisk::eliminarParticion(string path,string name,string tipoEliminacion){
  FILE *archivo;
  vector<string> rutaD (descomponerRuta(path));
  string nombreArchivo = rutaD[rutaD.size()-1];
  if(extensionRutaValida(nombreArchivo)){
      string rTemporal = rRutaDeArchivo(rRuta(rutaD),nombreArchivo);
      archivo = fopen(rTemporal.c_str(),"rb+");
      //si el archivo se abrio correctamente
      if(archivo!=NULL){
          if(tipoEliminacion == "fast"){
              eliminacionFast(rTemporal,name);
            }else if(tipoEliminacion == "full"){
              eliminacionFull(rTemporal,name);
            }else{
              cout<<"*** El tipo de eliminacion elegida no es aplicable ***"<<endl;
            }
        }else{
          cout<<"*** Error el disco a particionar no existe! ***"<<endl;
        }
      fclose(archivo);
    }else{
      cout<<"*** La extension del archivo proporcionado no es valida ***"<<endl;
    }
}

void comando_fdisk::eliminacionFast(string path,string name){
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  fseek(archivo, 0, SEEK_SET); //me posiciono en el inicio del archivo
  mbr MBR;//mbr temporal que agarra el mbr que ya esta en el disco
  fread(&MBR,sizeof(mbr),1,archivo);
  string nombParticion ="";
  int existeParticion = 0;
  int i = 0;
  for(i;i<4;i++){
      if(MBR.mbr_particiones[i].part_status=='1'){
          nombParticion = rNombreParticion(MBR.mbr_particiones[i].part_name);
          if(nombParticion == name){
              existeParticion = 1;
              break;
            }
        }
    }
  if(existeParticion==1){
      MBR.mbr_particiones[i].part_status = '0';
      for(int j=0;j<15;j++){
          MBR.mbr_particiones[i].part_name[j] = '\0';
        }
      MBR.mbr_particiones[i].part_fit = '-1';
      MBR.mbr_particiones[i].part_type = '-1';
      MBR.mbr_particiones[i].part_start = -1;
      MBR.mbr_particiones[i].part_size = -1;
      fseek(archivo, 0, SEEK_SET);
      fwrite(&MBR, sizeof(mbr), 1, archivo);
    }else{
      cout<<"*** La particion buscada no se encuentra ***"<<endl;
    }
  fclose(archivo);
  imprimirInfo(path);
}

void comando_fdisk::eliminacionFull(string path,string name){
  FILE *archivo;
  archivo = fopen(path.c_str(),"rb+");
  fseek(archivo, 0, SEEK_SET); //me posiciono en el inicio del archivo
  mbr MBR;//mbr temporal que agarra el mbr que ya esta en el disco
  fread(&MBR,sizeof(mbr),1,archivo);
  string nombParticion ="";
  int existeParticion = 0;
  int i = 0;
  for(i;i<4;i++){
      if(MBR.mbr_particiones[i].part_status=='1'){
          nombParticion = rNombreParticion(MBR.mbr_particiones[i].part_name);
          if(nombParticion == name){
              existeParticion = 1;
              cout<<i<<endl;
              break;
            }
        }
    }

  if(existeParticion==1){
      int initPart = MBR.mbr_particiones[i].part_start;
      int tamPart = MBR.mbr_particiones[i].part_size;
      char ceros = '\0';
      fseek(archivo, initPart, SEEK_SET);
      for(int j = 0;j<tamPart;j++){
          fwrite(&ceros,sizeof(ceros),1,archivo);
        }

      MBR.mbr_particiones[i].part_status = '0';
      for(int j=0;j<15;j++){
          MBR.mbr_particiones[i].part_name[j] = '\0';
        }
      MBR.mbr_particiones[i].part_fit = '-1';
      MBR.mbr_particiones[i].part_type = '-1';
      MBR.mbr_particiones[i].part_start = -1;
      MBR.mbr_particiones[i].part_size = -1;
      fseek(archivo, 0, SEEK_SET);
      fwrite(&MBR, sizeof(mbr), 1, archivo);
    }else{
      cout<<"*** La particion buscada no se encuentra ***"<<endl;
    }

  fclose(archivo);
  imprimirInfo(path);
}

//funcion que retorna el nombre obtenido de un char de 16 posiciones
string comando_fdisk::rNombreParticion(char nomb[16]){
  string nombre(nomb);
  return nombre;
}
