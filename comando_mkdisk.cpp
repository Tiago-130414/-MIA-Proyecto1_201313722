#include "comando_mkdisk.h"
comando_mkdisk::comando_mkdisk()
{

}


void comando_mkdisk::prueba(string size,string path, string unit,string fit){
  cout<<"size: "<<size<<" path: "<<path<<" unit: "<<unit<<" fit: "<<fit<<endl;
}

void comando_mkdisk::prueba2(vector<string> mkdiskP){
  for(int i =0; i<mkdiskP.size();i++){
      cout<<mkdiskP[i]<<endl;
    }
}
