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

lletra  [a-zA-Z]
digit   [0-9]
boolean (true|false)
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

"="                         { return ASSIGN; }

 

{text}                      {
                              yylval.st.value_data.ident.lexema = strdup(yytext);
                              yylval.st.value_data.ident.lenght = yyleng;
                              yylval.st.value_data.ident.value_type = STRING_TYPE;
                              return STRING;
                            }                                 
  

{digit}+"."{digit}+("e-"{digit}+)?    {
                                      yylval.st.value_data.real = atof(yytext);
                                      return FLOAT;
                                      }


{digit}+                    {
                              yylval.st.value_data.enter = atoi(yytext);
                              return INTEGER;
                            }

"+"                         { return SUMA; }

"-"                         { return RESTA; }            

^[ \t]*[\n]                 {}

[\n]                        { return ENDLINE; }

.                           {}

%%

