#include <QCoreApplication>
#include <iostream>
#include <QString>
#include <parser.h>  // Nuestro parser
#include <scanner.h>  // Nuestro scanner
#include <QTextStream>
#include <estructuras.h>
extern int yyparse(); //
//static QList<discosmontados> discosenmemoria;
extern int linea; // Linea del token
extern int columna; // Columna de los tokens
extern int yylineno;
vector <disco> registro;
using namespace std;
int main()
{
    QTextStream qtin(stdin);
    QString line;

    while(line!="salir"){    //esto me sirve para seguir leyendo siempre los comandos sin salirme
        printf("********************* Ingrese Comando *********************\n\n");
        line = qtin.readLine();
        if(line!="salir"){
            if(line.isEmpty()==false){
                YY_BUFFER_STATE buffer = yy_scan_string(line.toUtf8().constData());
                linea = 0;
                columna = 0;
                yylineno = 0;
                if(yyparse()==0)
                {
                    printf("\n\n************* Comando ejecutado correctamente *************\n\n");

                }else {

                    printf("\n\nHay errores lexicos o sintacticos \n\n");
                }

            }
        }
    }
}
