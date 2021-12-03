/*
* Olau Sancho Souto & Maria Sauras Fernandez
*   First part of Minijulia Compiler
*           Lexical class (Flex)
*/

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "exemple.tab.h"
#include "exemple_funcions.h"
#include "symtab.h"

%}

%option yylineno
%option noyywrap
%option noinput
%option nounput

/* Definimos matrix y lo usaremos tanto para los vectores como para las matrices*/
/**/
%S MATRIX

lletra  [a-zA-Z]
digit   [0-9]
boolean (true|false)
float   {digit}+"."{digit}*("e-"{digit}+)? 
text    ["][^\n\t\"\']*["] 
comment ([#][^\n\"\']* | [#=][^\"\']*[=#])

%%
  
{boolean}                  {
                              yylval.st.value_data.ident.lexema = strdup(yytext);
                              yylval.st.value_data.ident.lenght = yyleng;
                              yylval.st.value_data.ident.value_type = BOOL_TYPE;
                              return BOOLEAN; 
                            }


{lletra}({lletra}|{digit})* {
                              yylval.st.value_data.ident.lexema = strdup(yytext);
                              yylval.st.value_data.ident.lenght = yyleng;
                              yylval.st.value_data.ident.line = yylineno;
                              yylval.st.value_data.ident.value_type = UNKNOWN_TYPE;
                              return ID;
                            }

"("                         { return OP; }

")"                         { return CP; }

"+"                         { return SUMA; }

"-"                         { return RESTA; }

"*"                         { return MUL; } 

"/"                         { return DIV; }

"%"                         { return MOD; }

"^"                         { return POW; }                    

"="                         { return ASSIGN; }

"["" "*                     { BEGIN MATRIX; return OC; }

<MATRIX>" "*;" "*           { return PC; }

<MATRIX>" "+                { return SPACE; }        

" "*"]"                     { BEGIN INITIAL; return CC; }


{text}                      {
                              yylval.st.value_data.ident.lexema = strdup(yytext);
                              yylval.st.value_data.ident.lenght = yyleng;
                              yylval.st.value_data.ident.value_type = STRING_TYPE;
                              return STRING;
                            } 
  


{float}                     {
                              yylval.st.value_data.real = atof(yytext);
                              return FLOAT;
                            }


{digit}+                {
                              yylval.st.value_data.enter = atoi(yytext);
                              return INTEGER;
                            }


          

^[ \t]*[\n]                 {}

[\n]                        { return ENDLINE; }

.                           {}

%%
