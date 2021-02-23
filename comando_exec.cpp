#include "comando_exec.h"

comando_exec::comando_exec()
{

}

void comando_exec::leerScript(vector<string> ruta){
  string path = "";
  //recorriendo vector para obtener ruta
  for(int i=0;i<ruta.size();i++){
      if(aMinuscula(ruta[i]) == "path"){
          path = quitarComillas(ruta[i+1]);
        }
    }
  //separando la ruta enviada para extraer nombre del archivo
  vector <string> carpetas(descomponerRuta(path));
  //obteniendo nombre del archivo
  string nArchivo  = carpetas[carpetas.size()-1];
  //verificando extension valida del archivo
  if(extensionScriptValida(nArchivo)){
      ifstream archivo(path);
      //verificando si el archivo que enviaron existe
      if(archivo.good()){
          string line;
          //si el archivo se encuentra bien se lee linea por linea
          while(getline(archivo,line)){
              //verificando si la linea no viene vacia
              if(!line.empty()){
                  //ya se puede enviar codigo a la gramatica
                  int coment = 0;
                  if(line[0]!='#'){
                      printf("\n\n************************* Comando *************************\n\n");
                      //exec -path=/home/santi/Escritorio/archivo.script
                      cout<<line<<endl;
                    }else{
                      coment = 1;
                    }
                  YY_BUFFER_STATE buffer = yy_scan_string(line.c_str());
                  int val = yyparse();
                  if(val == 0 && coment == 0){
                      printf("\n\n************* Comando ejecutado correctamente *************\n\n");
                    }

                }
            }
        }else{
          cout<<"No existe el archivo"<<endl;
        }
    }else {
      cout<<"*** El archivo enviado no es un script ***"<<endl;
    }
}
