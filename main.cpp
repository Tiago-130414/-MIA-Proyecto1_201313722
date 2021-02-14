#include <QCoreApplication>
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  cout<<"si sirvo"<<endl;
  return a.exec();
}
