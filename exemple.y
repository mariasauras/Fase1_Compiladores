%{

#include <stdio.h>
#include <stdlib.h>
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
%token <st.value_data.boolean> BOOLEAN
%token  SUMA
%token  RESTA


%type <st> programa
%type <st> expressio
%type <st> valor
%type <st> oplist

%start programa

%%

programa : programa expressio {
             fprintf(yyout, "programa -> expressio :\n  expressio = '%s'\n", value_info_to_str($2));
           }
           | expressio {
             fprintf(yyout, "programa -> expressio :\n  expressio = '%s'\n", value_info_to_str($1));
           }

expressio : ID ASSIGN oplist ENDLINE  {
              $$.value_type = $3.value_type;

              if($$.value_type == INT_TYPE){
                fprintf(yyout, "ID: %s pren per valor: %d\n",$1.lexema, $3.value_data.enter);
                $$.value_data.enter= $3.value_data.enter;
              } else if($$.value_type == FLOAT_TYPE){
                fprintf(yyout, "ID: %s pren per valor: %f\n",$1.lexema, $3.value_data.real);
                $$.value_data.real = $3.value_data.real;
              } else if($$.value_type == BOOL_TYPE){
                $$.value_data.boolean = $3.value_data.boolean;
                if($$.value_data.boolean == 1){
                  fprintf(yyout, "True\n"); 
                } else {
                  fprintf(yyout, "False\n");
                }
              }else{
                 fprintf(yyout, "ID: %s pren per valor: %s\n",$1.lexema, $3.value_data.ident.lexema);
                $$.value_data.ident.lexema = $3.value_data.ident.lexema;
              }

            }

valor : FLOAT { $$.value_type = FLOAT_TYPE; $$.value_data.real = $1; }
      | INTEGER { $$.value_type = INT_TYPE; $$.value_data.enter = $1; }
      | STRING { $$.value_type = STRING_TYPE; $$.value_data.ident.lexema = $1.lexema; }
      | BOOLEAN { $$.value_type = BOOL_TYPE; $$.value_data.boolean = $1; }


oplist : oplist SUMA valor { op(&$$,$$,$3); }
        | oplist RESTA valor 
        | valor

%%
