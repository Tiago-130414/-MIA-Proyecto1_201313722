#include "comando_mkdir.h"

comando_mkdir::comando_mkdir()
{

}

void comando_mkdir::ejecutarMkdir(vector<string> parametrosMkdir){
  cout<<" tamanio "<<parametrosMkdir.size()<<endl;
  for(int i =0 ;i<parametrosMkdir.size();i++){
      cout<<parametrosMkdir[i]<<endl;
    }
}
