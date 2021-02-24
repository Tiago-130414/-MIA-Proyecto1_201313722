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
      if((existAdd==0 && existDelete==1)||(existAdd==1 && existDelete==0) || (existAdd==0 && existDelete ==0)){
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
      string rTemporal = rRutaDeArchivo(rRuta(rutaD),nombreArchivo);
      archivo = fopen(rTemporal.c_str(),"rb+");
      //si el archivo se abrio correctamente
      if(archivo!=NULL){
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
                      //segun el tipo de ajuste se obtiene el inicio de la particion
                      if(fitT == 'B'){
                          //Mejor ajuste
                        }else if(fitT == 'F'){
                          //Primer ajuste

                        }else if(fitT == 'W'){
                          //Peor ajuste
                        }
                      //aqui se procede a crear la particion
                      tamanioParticion = tamanoParticionNueva(unit,size);
                      //aqui se tendrian que agregar todos los datos
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
