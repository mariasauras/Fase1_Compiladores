%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "exemple.tab.h"
#include "exemple_funcions.h"

%}

%option yylineno
%option noyywrap
%option noinput
%option nounput

lletra  [a-zA-Z]
digit   [0-9]
boolean (true|false)
text    ["][^\n\t\"\']+["] 
com     ([ ]*[#][^\n\t\"\']+ | [ ]*[#=][^\t\"\']+[=#])



%%

{boolean}+                {
                              yylval.ident.lexema = strdup(yytext);
                              yylval.ident.lenght = yyleng;
                              yylval.ident.id_val.val_type = BOOL_TYPE;
                              return BOOLEAN; 
                            }

{lletra}({lletra}|{digit})* {
                              yylval.ident.lexema = strdup(yytext);
                              yylval.ident.lenght = yyleng;
                              yylval.ident.line = yylineno;
                              yylval.ident.id_val.val_type = UNKNOWN_TYPE;
                              return ID;
                            }

"="                         { return ASSIGN; }

 

{text}                      {
                              yylval.ident.lexema = strdup(yytext);
                              yylval.ident.lenght = yyleng;
                              yylval.ident.id_val.val_type = STRING_TYPE;
                              return STRING;
                            }                                 
  

{digit}+"."({digit}|{lletra}|-)+          {
                              yylval.real = atof(yytext);
                              return FLOAT;
                            }

{digit}+                    {
                              yylval.enter = atoi(yytext);
                              return INTEGER;
                            }




^[ \t]*[\n]                 {}

[\n]                        { return ENDLINE; }

.                           {}

%%

