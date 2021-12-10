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

%S MATRIX

lletra  [a-zA-Z]
digit   [0-9]
boolean (true|false)
float   {digit}+"."{digit}*("e-"{digit}+)? 
text    ["][^_\n\t\"\']*["] 
comment ([#][^\n\"\']* | [#=][^\"\']*[=#])

%%

"div"                      { return FP_D; }

{boolean}                  {
                              if (strcmp(strdup(yytext),"false") == 0)
                                yylval.st.value_data.boolean = 0;
                              else
                                yylval.st.value_data.boolean = 1;
                                
                              yylval.st.value_data.ident.value_type = BOOL_TYPE;
                              return BOOLEAN; 
                            }


{lletra}({lletra}|{digit})*_*({lletra}|{digit})* {
                              yylval.st.value_data.ident.lexema = strdup(yytext);
                              yylval.st.value_data.ident.lenght = yyleng;
                              yylval.st.value_data.ident.line = yylineno;
                              yylval.st.value_data.ident.value_type = UNKNOWN_TYPE;
                              sym_value_type b;
                              if(sym_lookup(yylval.st.value_data.ident.lexema, &b) == SYMTAB_NOT_FOUND) return ID;
                              if(b.value_type == BOOL_TYPE) return ID_BOOL;
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

","                         { return COMMA; } 

"["" "*                     { BEGIN MATRIX; return OC; }

<MATRIX>" "*;" "*           { return PC; }

<MATRIX>" "+                { return SPACE; }        

" "*"]"                     { BEGIN INITIAL; return CC; }

">"                         { return GREATERTHAN; }

">="                        { return GREATEREQ; }

"<"                         { return LESSTHAN; }

"<="                        { return LESSEQ; }

"=="                        { return EQ; }

"!="                        { return DIF; }

"!"                         { return NOT; }

"&&"                        { return AND; }

"||"                        { return OR; }

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


{digit}+                    {
                              yylval.st.value_data.enter = atoi(yytext);
                              return INTEGER;
                            }

          
^[ \t]*[\n]                 {}

[\n]                        { return ENDLINE; }

.                           {}

%%
