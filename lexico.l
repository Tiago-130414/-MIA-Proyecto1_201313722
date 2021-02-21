%option case-insensitive
%option yylineno

%{
#include <iostream>
//#include <QString>
#include "parser.h"
#include <string>
//#include <QList>
    int yylex();
    void yyerror(const char *s);
    int linea = 0;
    int columna = 1;
    int anterior = 0;
%}
%option noyywrap
%option nounput




/*EXPRESIONES REGULARES*/
identificador ({letra}|{entero}|"_")+
entero [0-9]+
negativo -[0-9]+
letra [a-zA-Z]+
cadena [\"][^\"\n]*[\"\n]
ruta ([/]([^\n' '])*)
comentario #.*
/*caracter "\'"("\\")?({letra}|{entero})"\'"*/


%x COM


%%
"MKDISK"    {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_mkdisk;}
"RMDISK"    {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return c_rmdisk;}
"FDISK"     {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_fdisk;}
"MOUNT"     {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_mount;}
"UNMOUNT"   {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_unmount;}
"MKFS"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_mkfs;}
"LOGIN"     {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_login;}
"MKGRP"     {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_mkgrp;}
"RMGRP"     {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_rmgrp;}
"MKUSR"     {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_mkusr;}
"RMUSR"     {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_rmusr;}
"CHMOD"     {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_chmod;}
"MKFILE"    {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_mkfile;}
"CAT"       {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_cat;}
"REM"       {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_rem;}
"EDIT"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_edit;}
"REN"       {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_ren;}
"MKDIR"     {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_mkdir;}
"CP"        {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_cp;}
"MV"        {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_mv;}
"FIND"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_find;}
"CHOWN"     {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_chown;}
"CHGRP"     {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_chgrp;}
"LOGOUT"    {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_logout;}
"PAUSE"     {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_pause;}
"RECOVERY"  {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_recovery;}
"LOSS"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_loss;}
"EXEC"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_exec;}
"REP"       {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return c_rep;}


"SIZE"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_size;}
"PATH"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_path;}
"F"         {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_f;}
"U"         {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_u;}
"TYPE"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_type;}
"DELETE"    {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_delete;}
"NAME"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_name;}
"ADD"       {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_add;}
"ID"        {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_id;}
"FS"        {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_fs;}
"USR"       {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_usr;}
"PWD"       {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_pwd;}
"GRP"       {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_grp;}
"UGO"       {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_ugo;}
"R"         {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_r;}
"CONT"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_cont;}
"FILE"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_file;}
"P"         {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_p;}
"DEST"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_dest;}
"RUTA"      {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return p_ruta;}


{entero}          {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return entero;}
{negativo}        {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return entero;}
{cadena}          {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return cadena;}
{identificador}   {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return identificador;}
{ruta}            {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return ruta;}
{comentario}      {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return comentario;}


"."         {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return punto;}
"-"         {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return menos;}
"*"         {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return multiplicacion;}
"="         {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return igual;}
"?"         {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return interrogacion;}
"\n"        {linea++; columna=0; anterior=0;}
[[:blank:]] { columna++; }

.           {std::cout<<"Error Lexico: "<<linea<<"\n";}
