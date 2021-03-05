/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    c_mkdisk = 258,
    c_rmdisk = 259,
    c_fdisk = 260,
    c_mount = 261,
    c_unmount = 262,
    c_mkfile = 263,
    c_cat = 264,
    c_rem = 265,
    c_mkfs = 266,
    c_login = 267,
    c_mkgrp = 268,
    c_rmgrp = 269,
    c_mkusr = 270,
    c_rmusr = 271,
    c_chmod = 272,
    c_edit = 273,
    c_ren = 274,
    c_mkdir = 275,
    c_cp = 276,
    c_mv = 277,
    c_find = 278,
    c_chown = 279,
    c_chgrp = 280,
    c_logout = 281,
    c_pause = 282,
    c_recovery = 283,
    c_loss = 284,
    c_exec = 285,
    c_rep = 286,
    p_size = 287,
    p_path = 288,
    p_f = 289,
    p_u = 290,
    p_type = 291,
    p_delete = 292,
    p_name = 293,
    p_add = 294,
    p_id = 295,
    p_fs = 296,
    p_usr = 297,
    p_pwd = 298,
    p_grp = 299,
    p_ugo = 300,
    p_r = 301,
    p_cont = 302,
    p_file = 303,
    p_p = 304,
    p_dest = 305,
    p_ruta = 306,
    entero = 307,
    negativo = 308,
    cadena = 309,
    identificador = 310,
    comentario = 311,
    punto = 312,
    menos = 313,
    multiplicacion = 314,
    igual = 315,
    interrogacion = 316,
    ruta = 317
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 50 "parser.y"

//se especifican los tipo de valores para los no terminales y lo terminales
//char TEXT [256];
//QString TEXT;
char TEXT[256];

#line 127 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
