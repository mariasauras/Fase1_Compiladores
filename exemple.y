/*
* Olau Sancho Souto & Maria Sauras Fernandez
*   First part of Minijulia Compiler
*        Sintactical class (BISON)
*/

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
%token  SUMA RESTA MUL DIV MOD POW OP CP

%type <st> programa
%type <st> expressio
%type <st> valor
%type <st> sumrest mullist powlist

%start programa

%%

programa : programa expressio {
             fprintf(yyout, "programa -> expressio :\n  expressio = '%s'\n", value_info_to_str($2));
           }
           | expressio {
             fprintf(yyout, "programa -> expressio :\n  expressio = '%s'\n", value_info_to_str($1));
           }

expressio : ID ASSIGN sumrest ENDLINE  {
              $$.value_type = $3.value_type;
              sym_enter($1.lexema, &$3);

              if($$.value_type == INT_TYPE){
                fprintf(yyout, "ID: %s value: %ld\n",$1.lexema, $3.value_data.enter);
                $$.value_data.enter= $3.value_data.enter;
              } else if($$.value_type == FLOAT_TYPE){
                fprintf(yyout, "ID: %s value: %f\n",$1.lexema, $3.value_data.real);
                $$.value_data.real = $3.value_data.real;
              } else if($$.value_type == BOOL_TYPE){
                $$.value_data.boolean = $3.value_data.boolean;
                if($$.value_data.boolean == 1){
                  fprintf(yyout, "ID: %s value: True\n",$1.lexema); 
                } else {
                  fprintf(yyout, "ID: %s value: False\n",$1.lexema);
                }
              }else{
                 fprintf(yyout, "ID: %s value: %s\n",$1.lexema, $3.value_data.ident.lexema);
                $$.value_data.ident.lexema = $3.value_data.ident.lexema;
              }
            }
          | sumrest ENDLINE  {
              $$.value_type = $1.value_type;

              if($$.value_type == INT_TYPE){
                fprintf(yyout, " INT value: %ld\n", $1.value_data.enter);
                $$.value_data.enter= $1.value_data.enter;
              } else if($$.value_type == FLOAT_TYPE){
                fprintf(yyout, "FLOAT value: %f\n", $1.value_data.real);
                $$.value_data.real = $1.value_data.real;
              } else if($$.value_type == BOOL_TYPE){
                $$.value_data.boolean = $1.value_data.boolean;
                if($$.value_data.boolean == 1){
                  fprintf(yyout, "BOOL value: True\n"); 
                } else {
                  fprintf(yyout, "BOOL value: False\n");
                }
              }else{
                 fprintf(yyout, "STRING value: %s\n", $1.value_data.ident.lexema);
                $$.value_data.ident.lexema = $1.value_data.ident.lexema;
              }
            }

valor : FLOAT     { $$.value_type = FLOAT_TYPE; $$.value_data.real = $1; }
      | INTEGER   { $$.value_type = INT_TYPE; $$.value_data.enter = $1; }
      | STRING    { $$.value_type = STRING_TYPE; $$.value_data.ident.lexema = $1.lexema; }
      | BOOLEAN   { $$.value_type = BOOL_TYPE; $$.value_data.boolean = $1; }
      | OP sumrest CP { $$ = $2; }
      | ID        { sym_lookup($1.lexema, &$$); }

/* Jerarquia de prioridades */
sumrest : sumrest SUMA mullist  { sum_op(&$$,$1,$3); }
        | sumrest RESTA mullist { rest_op(&$$,$1,$3); }
        | mullist

mullist : mullist MUL powlist { mul_op(&$$,$1,$3); } 
        | mullist DIV powlist { div_op(&$$,$1,$3); }
        | mullist MOD powlist { mod_op(&$$,$1,$3); }
        | powlist

powlist : powlist POW powlist { pow_op(&$$,$1,$3); }
        | valor 

%%
