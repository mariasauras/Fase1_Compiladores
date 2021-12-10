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

#ifndef YY_YY_EXEMPLE_TAB_H_INCLUDED
# define YY_YY_EXEMPLE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 18 "exemple.y"

  /* Les definicions que s'utilitzen al %union han d'estar aqui */
  #include "exemple_dades.h"
  #include "exemple_funcions.h"
  #include "symtab.h"

#line 55 "exemple.tab.h"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ASSIGN = 258,
    ENDLINE = 259,
    INTEGER = 260,
    ID = 261,
    ID_BOOL = 262,
    FLOAT = 263,
    STRING = 264,
    BOOLEAN = 265,
    SUMA = 266,
    RESTA = 267,
    MUL = 268,
    DIV = 269,
    MOD = 270,
    POW = 271,
    OP = 272,
    CP = 273,
    OC = 274,
    CC = 275,
    PC = 276,
    SPACE = 277,
    COMMA = 278,
    GREATERTHAN = 279,
    LESSTHAN = 280,
    GREATEREQ = 281,
    LESSEQ = 282,
    EQ = 283,
    DIF = 284,
    FP_D = 285,
    NOT = 286,
    AND = 287,
    OR = 288
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 25 "exemple.y"

  sym_value_type st;

#line 104 "exemple.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_EXEMPLE_TAB_H_INCLUDED  */
