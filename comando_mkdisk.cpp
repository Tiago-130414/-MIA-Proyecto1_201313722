#include "comando_mkdisk.h"
comando_mkdisk::comando_mkdisk()
{

}
//METODO QUE RECIBE VALORES DE BISON Y EJECUTA EL CREAR DISCO
void comando_mkdisk::ejecutarMkdisk(vector<string> mkdiskP){
  //temporales
  int ePath = 0; //existe path
  int eSize = 0; //existe size
  //atributos del disco
  int size = 0;
  string path = "";
  string unit = "-1";
  string fit = "-1";
  //recorriendo vector con datos de comando mkdisk
  for(int i = 0;i<mkdiskP.size();i++){
      if(aMinuscula(mkdiskP[i])=="size"){
          eSize = 1;
          size = stoi(mkdiskP[i+1]);
          //cout<<"size casteo: "<<size<<endl;
        }else if(aMinuscula(mkdiskP[i])=="path"){
          ePath = 1;
          path = mkdiskP[i+1];
        }else if(aMinuscula(mkdiskP[i])=="f"){
          fit = aMinuscula(mkdiskP[i+1]);
        }else if(aMinuscula(mkdiskP[i])=="u"){
          unit = aMinuscula(mkdiskP[i+1]);
        }
    }
  //validando comandos necesarios para crear disco
  if(ePath!=0&&eSize!=0){
      if(unit=="m"||unit=="k"||unit=="-1"){
          if(fit=="bf"||fit=="ff"||fit=="wf"||fit=="-1"){
              crearDisco(size,path,unit,fit);
            }else{
              cout<<"Error de parametro -f"<<endl;
            }
        }else{
          cout<<"Error de parametro -u"<<endl;
        }
    }else{
      cout<<"Parametros obligatorio faltante"<<endl;
    }
}

//CREA EL DISCO CON PARAMETROS OBTENIDOS
void comando_mkdisk::crearDisco(int size,string path,string unit,string fit){
  string nombreArchivo;
  string rutaCarpetas;
  vector<string> carpetas(descomponerRuta(path));
  nombreArchivo = carpetas[carpetas.size()-1];
  bool valida= extensionRutaValida(nombreArchivo);
  //Verificando si la extension del archivo es valida
  if(valida != false){
      rutaCarpetas = rRuta(carpetas);
      mkdir(rutaCarpetas.c_str(), 0777);
      string te =rutaCarpetas+"/"+nombreArchivo;
      generarDisco(size,te,unit,fit);
      cout << "*** Disco creado correctamente ***"<<endl;
      imprimirDisco(te);
    }else{
      cout<<"extension de disco invalida"<<endl;
    }
}

//CREA EL ARCHIVO Y LO LLENA CON EL MBR Y LE DA EL TAMANO SOLICITADO POR USUARIO
void comando_mkdisk::generarDisco(int size,string path, string unit, string fit){
  mbr disco;
  FILE *archivo;
  archivo = fopen(path.c_str(),"wb");
  if(archivo!=NULL){
      char buffer[1024];
      //SI LA UNIDAD NO ES ENVIDADA POR EL USUARIO
      if(unit=="-1"){
          unit = "m";
        }
      //SE VERIFICA EL TIPO DE UNIDAD PARA CREAR EL DISCO
      if(aMinuscula(unit)=="k"){
          //CREANDO ARCHIVOS EN KILOBYTES
          //cout<<"size: "<<size<<endl;
          disco.mbr_tamano = size *1024;
          for(int i =0;i<1024;i++){
              buffer[i]='\0';
            }
          for(int i=0;i<size;i++){
              fwrite(buffer,1024,1,archivo);
            }
          fclose(archivo);
        }else if(aMinuscula(unit)=="m"){
          //CREANDO ARCHIVO EN MEGAS
          //cout<<"size: "<<size<<endl;
          disco.mbr_tamano = size*1024*1024;
          for(int i =0;i<1024;i++){
              buffer[i]='\0';
            }
          for(int i=0;i<size*1024;i++){
              fwrite(buffer,1024,1,archivo);
            }
          fclose(archivo);
        }

      //OBTENIENDO TIEMPO
      time_t rawtime;
      struct tm * timeinfo;
      char fC [16];
      time (&rawtime);
      timeinfo = localtime (&rawtime);
      strftime(fC,16,"%d/%m/%y %H:%M",timeinfo);
      strcpy (disco.mbr_fecha_creacion, fC);
      disco.mbr_disk_signature = rand();

      //VALIDANDO EL AJUSTE DEL DISCO
      if(fit=="-1"){
          fit="F";
        }else if(fit=="bf"){
          fit="B";
        }else if(fit=="ff"){
          fit="F";
        }else if(fit=="wf"){
          fit="W";
        }
      //AGREGANDO EL AJUSTE DEL DISCO
      strcpy (disco.disk_fit,fit.c_str());

      //ANADIENDO PARTICIONES AL DISCO
      particion new_partition;
      //AGREGANDO VALORES POR DEFECTO A SUS ATRIBUTOS

      new_partition.part_status='0';
      new_partition.part_start=-1;
      new_partition.part_size=0;

      //AGREGANDO PARTICIONES AL MBR
      /*
      disco.mbr_partition_1 = new_partition;
      disco.mbr_partition_2 = new_partition;
      disco.mbr_partition_3 = new_partition;
      disco.mbr_partition_4 = new_partition;
      */
      for(int i = 0;i<4;i++){
          disco.mbr_particiones[i] = new_partition;
        }
      //AGREGANDO MBR AL DISCO
      archivo = fopen(path.c_str(),"rb+");
      if(archivo != NULL){
          fseek(archivo,0,SEEK_SET);
          fwrite(&disco,sizeof(mbr),1,archivo);
          fclose(archivo);
          //cout<<"DISCO CREADO CORRECTAMENTE"<<endl;
        }else{
          cout<<"Problema al crear el mbr"<<endl;
        }
    }else{
      cout<<"Problema al crear disco"<<endl;
    }
}



