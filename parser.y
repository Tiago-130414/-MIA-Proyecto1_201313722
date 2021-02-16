%{
#include "scanner.h"//se importa el header del analisis sintactico
#include <QString>
#include <string>
#include "qdebug.h"
#include <iostream>
//#include "obmkdisk.h"
using namespace std;
extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON
//string vec_p_mkdisk[2]={" "," "};
int yyerror(const char* mens)
{
std::cout << mens <<" "<<yytext<< std::endl;
return 0;
}
%}
//error-verbose si se especifica la opcion los errores sintacticos son especificados por BISON
%defines "parser.h"
%output "parser.cpp"
//%error-verbose
%locations
%union{
//se especifican los tipo de valores para los no terminales y lo terminales
//char TEXT [256];
//QString TEXT;
char TEXT[256];
class ejecutar_mkdisk *mkdisk;
}
//TERMINALES DE TIPO TEXT, SON STRINGS

%token<TEXT> c_mkdisk;
%token<TEXT> c_rmdisk;
%token<TEXT> c_fdisk;
%token<TEXT> c_mount;
%token<TEXT> c_unmount;
%token<TEXT> c_mkfs;
%token<TEXT> c_login;
%token<TEXT> c_mkgrp;
%token<TEXT> c_rmgrp;
%token<TEXT> c_mkusr;
%token<TEXT> c_rmusr;
%token<TEXT> c_chmod;
%token<TEXT> c_mkfile;
%token<TEXT> c_cat;
%token<TEXT> c_rem;
%token<TEXT> c_edit;
%token<TEXT> c_ren;
%token<TEXT> c_mkdir;
%token<TEXT> c_cp;
%token<TEXT> c_mv;
%token<TEXT> c_find;
%token<TEXT> c_chown;
%token<TEXT> c_chgrp;
%token<TEXT> c_logout;
%token<TEXT> c_pause;
%token<TEXT> c_recovery;
%token<TEXT> c_loss;
%token<TEXT> c_exec;
%token<TEXT> c_rep;


%token<TEXT> p_size;
%token<TEXT> p_path;
%token<TEXT> p_f;
%token<TEXT> p_u;
%token<TEXT> p_type;
%token<TEXT> p_delete;
%token<TEXT> p_name;
%token<TEXT> p_add;
%token<TEXT> p_id;
%token<TEXT> p_fs;
%token<TEXT> p_usr;
%token<TEXT> p_pwd;
%token<TEXT> p_grp;
%token<TEXT> p_ugo;
%token<TEXT> p_r;
%token<TEXT> p_cont;
%token<TEXT> p_file;
%token<TEXT> p_p;
%token<TEXT> p_dest;
%token<TEXT> p_ruta;
%token<TEXT> entero;
%token<TEXT> cadena;
%token<TEXT> identificador;


%token<TEXT> punto;
%token<TEXT> menos;
%token<TEXT> multiplicacion;
%token<TEXT> igual;
%token<TEXT> interrogacion;
%token<TEXT> ruta;


//%type<mkdisk> LS_PAR_MKDISK; // lista de instrucciones
//%type <string> PARAMETROS_MKDISK;
%start INICIO
%%

INICIO : LISTA_COMANDOS;

LISTA_COMANDOS : LISTA_COMANDOS COMANDOS 
               | COMANDOS
;

COMANDOS : MKDISK; 

MKDISK : c_mkdisk LS_PAR_MKDISK {printf("MKDISK RECONOCIDO");};

LS_PAR_MKDISK : LS_PAR_MKDISK PARAMETROS_MKDISK
              | PARAMETROS_MKDISK
;

PARAMETROS_MKDISK :   menos p_size igual entero 
                    | menos p_path igual RUTA
                    | menos p_f igual identificador
                    | menos p_u igual identificador
;

RUTA : cadena
     | ruta
;