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

    }else if(name == "inode"){

    }else if(name == "journaling"){

    }else if(name == "block"){

    }else if(name == "bm_inode"){
      reporteBitmapI(path,id);
    }else if(name == "bm_block"){
      reporteBitmapB(path,id);
    }else if(name == "tree"){

    }else if(name == "sb"){

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
      escribirReporte(reporte,carpetas,nomTemp);
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
          string nomTemp = quitarExtension(nomArchivo);
          string carpetas = rRuta(temp);
          escribirBitmapTXT(carpetas,nomTemp,bitmap);
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
          string nomTemp = quitarExtension(nomArchivo);
          string carpetas = rRuta(temp);
          escribirBitmapTXT(carpetas,nomTemp,bitmap);
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

/*
 *
 *
 // assigning value to string s
    string s = "geeksforgeeks";

    int n = s.length();

    // declaring character array
    char char_array[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(char_array, s.c_str());
 *
 *
 *if(contador<20){
                  nuevaCadena += vector_bitmap[i] + " ";
                  contador++;
                }else if(contador==20){
                  nuevaCadena +="\n";
                  contador=0;
                }
 *
 *
Foo [label=<
<table border="0" cellborder="1" cellspacing="0">
  <tr><td><i>Input Foo</i></td><td><i>Input Foo</i></td></tr>
  <tr><td port="1">one</td><td port="1">one</td></tr>
  <tr><td port="2">two</td><td port="1">one</td></tr>
  <tr><td port="3">three</td><td port="1">one</td></tr>
  <tr><td port="4">four</td><td port="1">one</td></tr>
  <tr><td port="5">five</td><td port="1">one</td></tr>
  <tr><td port="6">six</td><td port="1">one</td></tr>
</table>>];
*/



