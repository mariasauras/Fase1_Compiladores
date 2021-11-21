%{

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
extern FILE *yyout;
extern int yylineno;
extern int yylex();
/*extern void yyerror(char*);*/

%}

%code requires {
  /* Les definicions que s'utilitzen al %union han d'estar aqui */
  #include "exemple_dades.h"
  #include "exemple_funcions.h"
  #include "symtab.h"
}

%union{
    sym_value_type st;
}

%token <st.value_data.sense_valor> ASSIGN ENDLINE
%token <st.value_data.enter> INTEGER
%token <st.value_data.ident> ID
%token <st.value_data.real> FLOAT
%token <st.value_data.ident> STRING
%token <st.value_data.ident> BOOLEAN
%token  SUMA


%type <st> programa
%type <st> expressio
%type <st> valor
%type <st> sumlist

%start programa

%%

programa : programa expressio {
             fprintf(yyout, "programa -> expressio :\n  expressio = '%s'\n", value_info_to_str($2));
           }
           | expressio {
             fprintf(yyout, "programa -> expressio :\n  expressio = '%s'\n", value_info_to_str($1));
           }

expressio : ID ASSIGN valor ENDLINE  {
              $$.value_type = $3.value_type;

              if($$.value_type == STRING_TYPE){
                fprintf(yyout, "ID: %s pren per valor: %s\n",$1.value_data.ident.lexema, $3.value_data.ident.lexema);
                $$.value_data.ident.lexema = $3.value_data.ident.lexema;
               
              } else if($$.value_type == FLOAT_TYPE){
                fprintf(yyout, "ID: %s pren per valor: %f\n",$1.value_data.ident.lexema, $3.value_data.real);
                $$.value_data.real = $3.value_data.real;
                
              } else if($$.value_type == BOOL_TYPE){
                fprintf(yyout, "ID: %s pren per valor: %s\n",$1.value_data.ident.lexema, $3.value_data.ident.lexema);
                $$.value_data.ident.lexema = $3.value_data.ident.lexema;
              }else{
                fprintf(yyout, "ID: %s pren per valor: %d\n",$1.value_data.ident.lexema, $3.value_data.enter);
                $$.value_data.enter= $3.value_data.enter; 
              } 
            }

valor : FLOAT { $$.value_type = FLOAT_TYPE; $$.value_data.real = $1; }
      | INTEGER { $$.value_type = INT_TYPE; $$.value_data.enter = $1; }
      | STRING { $$.value_type = STRING_TYPE; $$.value_data.ident.lexema = $1.lexema; }
      | BOOLEAN { $$.value_type = BOOL_TYPE; $$.value_data.ident.lexema = $1.lexema; }


sumlist : sumlist SUMA valor 
        | valor

%%
