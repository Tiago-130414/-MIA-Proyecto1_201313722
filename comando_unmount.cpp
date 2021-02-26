#include "comando_unmount.h"

comando_unmount::comando_unmount()
{

}

void comando_unmount::ejecutarUnmount(vector<string> parametrosUnmount){
  int tamanioParametrosUnmount = parametrosUnmount.size();
  for(int i = 0;i<tamanioParametrosUnmount;i++){
      cout<<parametrosUnmount[i]<<endl;
    }
}
