#include "comando_rep.h"

comando_rep::comando_rep()
{

}

void comando_rep::ejecutarReporte(vector<string> parametrosRep){
  int tamRep = parametrosRep.size();
  //variables para recolectar los valores para generar reporte
  string name = "";
  string path = "";
  string id = "";
  string ruta = "-1";
  //booleanas para saber si existen los parametros obligatorios
  int existName = 0;
  int existPath = 0;
  int existId = 0;
  for(int i =0;i<tamRep;i++){
      //cout<<parametrosRep[i]<<endl;
      if(aMinuscula(parametrosRep[i]) == "name"){
          name = aMinuscula(parametrosRep[i+1]);
          existName = 1;
        }else if(aMinuscula(parametrosRep[i]) == "path"){
          path = parametrosRep[i+1];
          existPath = 1;
        }else if(aMinuscula(parametrosRep[i]) == "id"){
          id = parametrosRep[i+1];
          existId = 1;
        }else if(aMinuscula(parametrosRep[i]) == "ruta"){
          ruta = parametrosRep[i+1];
        }
    }
  //verificar si vienen los parametros obligatorios
  //si existe el nombre
  if(existName == 1){
      //si existe el path
      if(existPath == 1){
          //si existe el id
          if(existId == 1){
              if(validarNombreReportes(name) == 1){
                  //cout<<"parametros obligatorios completos"<<endl;
                  generarReporte(name,path,id,ruta);
                }else{
                  cout<<"*** Error -name de reporte invalido ***"<<endl;
                }
            }else{
              cout<<"*** Comando rep incompleto falta parametro -id ***"<<endl;
            }
        }else{
          cout<<"*** Comando rep incompleto falta parametro -path ***"<<endl;
        }
    }else{
      cout<<"*** Comando rep incompleto falta parametro -name ***"<<endl;
    }
}

//metodo que validan los nombres de los reportes que pueden haber
int comando_rep::validarNombreReportes(string name){
  int valido = 0;
  if(name == "mbr" ||name == "disk"||name == "inode"){
      valido = 1;
    }else if(name == "journaling"||name == "block"||name == "bm_inode"){
      valido = 1;
    }else if(name == "bm_block"||name == "tree"||name == "sb"){
      valido = 1;
    }else if(name == "file"||name == "ls"){
      valido = 1;
    }
  return valido;
}

//metodo que redirige al metodo que crea cada reporte
void comando_rep::generarReporte(string name,string path,string id,string ruta){
  if(name == "mbr"){
      ReporteMBR(path,id);
    }else if(name == "disk"){
      reporteDisco(path,id);
    }else if(name == "inode"){

    }else if(name == "journaling"){

    }else if(name == "block"){

    }else if(name == "bm_inode"){
      reporteBitmapI(path,id);
    }else if(name == "bm_block"){
      reporteBitmapB(path,id);
    }else if(name == "tree"){

    }else if(name == "sb"){
      reporteSuperBloque(path,id);
    }else if(name == "file"){

    }else if(name == "ls"){

    }
}

////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// REPORTE MBR //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

//reporte del mbr
void comando_rep::ReporteMBR(string path,string id){
  string idDisco = retornarIndiceDisco(id);
  int posDisco = stoi(idDisco);
  string pathDisco = retornarPathDisco(posDisco);
  string reporte="";
  if(pathDisco != "-1"){
      mbr MBRDISCO = retornarMBRdisco(pathDisco);
      vector <string> temp(descomponerRuta(path));
      string nomArchivo = temp[temp.size()-1];
      string nomTemp = quitarExtension(nomArchivo);
      string ext = aMinuscula(retornarExtension(nomArchivo));
      string carpetas = rRuta(temp);
      string fecha = MBRDISCO.mbr_fecha_creacion;
      string fit(MBRDISCO.disk_fit);
      reporte += "label=\" * REPORTE MBR * \";\n" ;
      reporte += "ReporteMBR[label=<\n";
      reporte += "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">\n";
      reporte += "<tr><td><i>NOMBRE</i></td><td><i>VALOR</i></td></tr>\n";
      reporte += "<tr><td>Tamanio MBR</td><td>"+ to_string(MBRDISCO.mbr_tamano) + "</td></tr>\n";
      reporte += "<tr><td>Fecha de creacion</td><td>"+fecha+"</td></tr>\n";
      reporte += "<tr><td>Disk signature</td><td>"+to_string(MBRDISCO.mbr_disk_signature)+"</td></tr>\n";
      reporte += "<tr><td>Disk fit</td><td>"+fit+"</td></tr>\n";
      reporte += infoParticiones(MBRDISCO);
      reporte += "</table>>];\n";
      escribirReporte(reporte,carpetas,nomTemp,ext);
    }else{
      cout<<"*** Ruta no encontrada, disco no esta montado o no existe ***"<<endl;
    }
}

//obtiene los datos de las particiones
string comando_rep::infoParticiones(mbr temp){
  string rep = "";
  for(int i = 0;i<4;i++){
      if(temp.mbr_particiones[i].part_status == '1'){
          string nm = temp.mbr_particiones[i].part_name;
          string fitT(1,temp.mbr_particiones[i].part_fit);
          rep+= "<tr><td>Particion </td><td>"+ to_string(i+1) +"</td></tr>\n";
          rep+= "<tr><td>Part status </td><td>"+ string(1,temp.mbr_particiones[i].part_status) +"</td></tr>\n";
          rep+= "<tr><td>Part type </td><td>"+ string(1,temp.mbr_particiones[i].part_type) +"</td></tr>\n";
          rep+= "<tr><td>Part fit </td><td>"+ fitT +"</td></tr>\n";
          rep+= "<tr><td>Part start </td><td>"+ to_string(temp.mbr_particiones[i].part_start) +"</td></tr>\n";
          rep+= "<tr><td>Part size </td><td>"+ to_string(temp.mbr_particiones[i].part_size) +"</td></tr>\n";
          rep+= "<tr><td>Part name </td><td>"+ nm +"</td></tr>\n";
        }
    }
  return rep;
}

////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// BM_INODO ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

//reporte bitmap de inodos
void comando_rep::reporteBitmapI(string path,string id){
  int idDisco = stoi(retornarIndiceDisco(id));
  string pathDisco = retornarPathDisco(idDisco);
  string nombreParticion = retornarNombreParticion(idDisco,id);
  if(pathDisco != "-1"){
      if(nombreParticion != "-1"){
          particion particionTemp = retornarParticion(pathDisco,nombreParticion);
          int initPart = particionTemp.part_start;
          string bitmap = leerBitmapI(pathDisco,initPart);
          vector <string> temp(descomponerRuta(path));
          string nomArchivo = temp[temp.size()-1];
          string ext = retornarExtension(nomArchivo);
          string nomTemp = quitarExtension(nomArchivo);
          string carpetas = rRuta(temp);
          if(aMinuscula(ext) == "txt"){
              escribirBitmapTXT(carpetas,nomTemp,bitmap);
            }else{
              cout<<"*** El reporte de bitmap inodos unicamente permite generar de tipo txt ***"<<endl;
            }
        }else{
          cout<<"*** La particion que se busco para reporte de BitMap no se encuentra montada ***"<<endl;
        }
    }else{
      cout<<"*** El disco que busca para reporte de BitMap no se encuentra ***"<<endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// BM_BLOQUE //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

//reporte bitmap de bloques
void comando_rep::reporteBitmapB(string path,string id){
  int idDisco = stoi(retornarIndiceDisco(id));
  string pathDisco = retornarPathDisco(idDisco);
  string nombreParticion = retornarNombreParticion(idDisco,id);
  if(pathDisco != "-1"){
      if(nombreParticion != "-1"){
          particion particionTemp = retornarParticion(pathDisco,nombreParticion);
          int initPart = particionTemp.part_start;
          string bitmap = leerBitmapB(pathDisco,initPart);
          vector <string> temp(descomponerRuta(path));
          string nomArchivo = temp[temp.size()-1];
          string ext = retornarExtension(nomArchivo);
          string nomTemp = quitarExtension(nomArchivo);
          string carpetas = rRuta(temp);
          if(aMinuscula(ext) == "txt"){
              escribirBitmapTXT(carpetas,nomTemp,bitmap);
            }else{
              cout<<"*** El reporte de bitmap de bloques unicamente permite generar de tipo txt"<<endl;
            }
        }else{
          cout<<"*** La particion que se busco para reporte de BitMap de bloques no se encuentra montada ***"<<endl;
        }
    }else{
      cout<<"*** El disco que busca para reporte de BitMap de bloques no se encuentra ***"<<endl;
    }
}

//metodo que crea archivos de texto de bitmaps
void  comando_rep::escribirBitmapTXT(string ruta,string nombre,string bitmap){
  ruta = ruta+"/";
  //verificando si la carpeta buscada esta creada si no se crea
  FILE *carpeta;
  carpeta = fopen(ruta.c_str(),"rb");
  if(carpeta==NULL){
      mkdir(ruta.c_str(), 0777);
      cout<<"*** La carpeta para generar reporte no se encuentra, se procedera a crearla ***"<<endl;
    }
  fclose(carpeta);
  //creando el archivo para compilar del dot
  string rt = ruta+nombre+".txt";

  //se crea el vector de char para agregarlo al aarchivo
  int longBitmap = bitmap.length();
  char vector_bitmap[longBitmap+1];
  strcpy(vector_bitmap,bitmap.c_str());

  //se creara el archivo
  ofstream archivo;
  archivo.open(rt);
  if(!archivo.fail()){
      int contador =0;
      for(int i = 0;i<longBitmap+1;i++){
          if(contador<20){
              archivo<<vector_bitmap[i]<<" ";
              contador++;
            }else if(contador ==20){
              i--;
              archivo<<endl;
              contador=0;
            }
        }
    }else {
      cout<<"*** Problema al crear archivo txt de reporte ***"<<endl;
    }
  archivo.close();
}

////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// SUPER_BLOQUE /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

void comando_rep::reporteSuperBloque(string path,string id){
  int idDisco = stoi(retornarIndiceDisco(id));
  string pathDisco = retornarPathDisco(idDisco);
  string reporte="";
  string nombreParticion = retornarNombreParticion(idDisco,id);
  if(pathDisco != "-1"){
      if(nombreParticion != "-1"){
          particion particionTemp = retornarParticion(pathDisco,nombreParticion);
          int initPart = particionTemp.part_start;
          superBloque sb (retornarSuperBloque(pathDisco,initPart));
          string fecha = sb.s_mtime;
          string fecha2 = sb.s_umtime;
          vector <string> temp(descomponerRuta(path));
          string nomArchivo = temp[temp.size()-1];
          string nomTemp = quitarExtension(nomArchivo);
          string ext = aMinuscula(retornarExtension(nomArchivo));
          string carpetas = rRuta(temp);
          reporte += "label=\" * REPORTE SUPER BLOQUE * \";\n" ;
          reporte += "ReporteSB[label=<\n";
          reporte += "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">\n";
          reporte += "<tr><td><i>NOMBRE</i></td><td><i>VALOR</i></td></tr>\n";
          reporte += "<tr><td>s_filesystem_type</td><td>"+ to_string(sb.s_filesystem_type) + "</td></tr>\n";
          reporte += "<tr><td>s_inodes_count</td><td>"+ to_string(sb.s_inodes_count) +"</td></tr>\n";
          reporte += "<tr><td>s_blocks_count</td><td>"+ to_string(sb.s_blocks_count) +"</td></tr>\n";
          reporte += "<tr><td>s_free_blocks_count</td><td>"+ to_string(sb.s_free_blocks_count) +"</td></tr>\n";
          reporte += "<tr><td>s_free_inodes_count</td><td>"+ to_string(sb.s_free_inodes_count) +"</td></tr>\n";
          reporte += "<tr><td>s_mtime</td><td>"+ fecha +"</td></tr>\n";
          reporte += "<tr><td>s_umtime</td><td>"+ fecha2 +"</td></tr>\n";
          reporte += "<tr><td>s_mnt_count</td><td>"+ to_string(sb.s_mnt_count) +"</td></tr>\n";
          reporte += "<tr><td>s_magic</td><td> 0xEF53 </td></tr>\n";
          reporte += "<tr><td>s_inode_size</td><td>"+ to_string(sb.s_inode_size) +"</td></tr>\n";
          reporte += "<tr><td>s_block_size</td><td>"+ to_string(sb.s_block_size) +"</td></tr>\n";
          reporte += "<tr><td>s_first_ino</td><td>"+ to_string(sb.s_first_ino) +"</td></tr>\n";
          reporte += "<tr><td>s_first_blo</td><td>"+ to_string(sb.s_first_blo) +"</td></tr>\n";
          reporte += "<tr><td>s_bm_inode_start</td><td>"+ to_string(sb.s_bm_inode_start) +"</td></tr>\n";
          reporte += "<tr><td>s_bm_block_start</td><td>"+ to_string(sb.s_bm_block_start) +"</td></tr>\n";
          reporte += "<tr><td>s_inode_start</td><td>"+ to_string(sb.s_inode_start) +"</td></tr>\n";
          reporte += "<tr><td>s_block_start</td><td>"+ to_string(sb.s_block_start) +"</td></tr>\n";
          reporte += "</table>>];\n";
          escribirReporte(reporte,carpetas,nomTemp,ext);
        }else{
          cout<<"*** La particion que se busco para reporte de Super bloque no se encuentra montada ***"<<endl;
        }
    }else{
      cout<<"*** Ruta no encontrada, disco no esta montado o no existe ***"<<endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// DISCO /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

void comando_rep::reporteDisco(string path,string id){
  int idDisco = stoi(retornarIndiceDisco(id));
  string pathDisco = retornarPathDisco(idDisco);
  string reporte="";
  string nombreParticion = retornarNombreParticion(idDisco,id);
  if(pathDisco != "-1"){
      if(nombreParticion != "-1"){
          mbr MBR = retornarMBRdisco(pathDisco);

          //vector de datos
          vector<espacio> particiones;
          //CON ESTE FOR RECOLECTO LOS DATOS
          for(int i=0;i<4;i++){
              espacio part;
              //cout<<"--------------------------------------------------"<<endl;
              //cout<<"Nombre de particion"<<string(MBR.mbr_particiones[i].part_name)<<endl;
              part.inicioParticion = MBR.mbr_particiones[i].part_start;
              //cout<<"inicio particion"<<MBR.mbr_particiones[i].part_start<<endl;
              part.tamanoParticion = MBR.mbr_particiones[i].part_size;
              //cout<<"tamano particion"<<MBR.mbr_particiones[i].part_size<<endl;
              particiones.push_back(part);
            }

          //ESTE FOR ME SIRVE DE PIVOTE PARA ORDENAR LAS PARTICIONES RECOLECTADAS POR EL INICIO
          //vector de sizes
          vector<int> tamano;
          int tam = particiones.size();
          for(int i =0;i<tam;i++){
              int temp = particiones[i].inicioParticion;
              tamano.push_back(temp);
            }

          int tamanosPsize= tamano.size();
          //ORDENO DE MENOR A MAYOR
          //sort(tamano.begin(),tamano.end());
          for(int i=0;i<tamanosPsize-1;i++){
              for(int j=i+1;j<tamanosPsize;j++){
                  if(tamano[i] >tamano[j]){
                      int aux = tamano[i];
                      tamano[i] = tamano[j];
                      tamano [j] = aux;
                    }
                }
            }

          //CREO UN VECTOR TEMPORAL PARA RETORNAR ORDENADO EL VECTOR
          vector<espacio> temporal;
          for(int i = 0;i<tamanosPsize;i++){
              int tamTemp = tamano[i];
              for(int j =0;j<tam;j++){
                  int pOcTemp = particiones[j].inicioParticion;
                  if(tamTemp == pOcTemp){
                      temporal.push_back(particiones[j]);
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

          //eliminando espacios con inicio <0
          vector <vacios> tempEspacios;
          for(int i=0;i<freeSpaces.size();i++){
              if(freeSpaces[i].inicio > 0){
                  vacios t = freeSpaces[i];
                  tempEspacios.push_back(t);
                }
            }
          //mostrando espacios libres
          /*for(int i=0;i<tempEspacios.size();i++){
              cout<<"--------------------------------------------------"<<endl;
              cout<<i<<" "<<tempEspacios[i].inicio<<" -- "<<tempEspacios[i].espacioLibre<<endl;
              //cout<<i<<" "<<freeSpaces[i].inicio<<" -- "<<freeSpaces[i].espacioLibre<<endl;

            }*/


          //recolectando particiones activas
          vector<particion> particionesActivas;
          for(int i = 0; i < 4;i++){
              if(MBR.mbr_particiones[i].part_status == '1'){
                  particion temp = MBR.mbr_particiones[i];
                  particionesActivas.push_back(temp);
                }
            }


          //mostrando particiones activas
          /*for(int i = 0; i < particionesActivas.size();i++){
              cout<<particionesActivas[i].part_status<<endl;
              cout<<string(particionesActivas[i].part_name)<<endl;
            }
          */

          for(int i=0;i<particionesActivas.size()-1;i++){
              for(int j=i+1;j<particionesActivas.size();j++){
                  if(particionesActivas[i].part_start >particionesActivas[j].part_start){
                      particion aux = particionesActivas[j];
                      particionesActivas[j] = particionesActivas[i];
                      particionesActivas [i] = aux;
                    }
                }
            }
          for(int i = 0;i<particionesActivas.size();i++){
              vacios temp;
              temp.inicio = particionesActivas[i].part_start;
              temp.espacioLibre = particionesActivas[i].part_size;
              temp.tipoParticion = particionesActivas[i].part_type;
              tempEspacios.push_back(temp);
            }


          for(int i=0;i<tempEspacios.size()-1;i++){
              for(int j=i+1;j<tempEspacios.size();j++){
                  if(tempEspacios[i].inicio >tempEspacios[j].inicio){
                      vacios aux = tempEspacios[j];
                      tempEspacios[j] = tempEspacios[i];
                      tempEspacios [i] = aux;
                    }
                }
            }

          //mostrando espacios libres
          for(int i=0;i<tempEspacios.size();i++){
              cout<<"--------------------------------------------------"<<endl;
              string lb = "LIBRE";
              if(!tempEspacios[i].tipoParticion.empty()){
                  lb = tempEspacios[i].tipoParticion;
                }
              cout<<i<<" "<<lb<<" "<<tempEspacios[i].inicio<<" -- "<<tempEspacios[i].espacioLibre<<endl;
            }


        }else{
          cout<<"*** La particion que se busco para reporte disk no se encuentra montada ***"<<endl;
        }
    }else{
      cout<<"*** Ruta no encontrada, disco no esta montado o no existe ***"<<endl;
    }
}
