#include "comando_pause.h"

comando_pause::comando_pause()
{

}

void comando_pause::ejecutarPause(){
  char caracter;
  cout<<"Presione cualquier tecla para continuar..."<<endl;
  caracter = getchar();
}
