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
}

%union{
    struct {
        char *lexema;
        int lenght;
        int line;
        value_info id_val;
    } ident;
    int enter;
    float real;
    value_info expr_val;
    void *sense_valor;
}

%token <sense_valor> ASSIGN ENDLINE
%token <enter> INTEGER
%token <ident> ID
%token <real> FLOAT
%token <ident> STRING
%token <ident> BOOLEAN



%type <sense_valor> programa
%type <expr_val> expressio
%type <expr_val> valor

%start programa

%%

programa : programa expressio {
             fprintf(yyout, "programa -> expressio :\n  expressio = '%s'\n", value_info_to_str($2));
           }
           | expressio {
             fprintf(yyout, "programa -> expressio :\n  expressio = '%s'\n", value_info_to_str($1));
           }

expressio : ID ASSIGN valor ENDLINE  {
              $$.val_type = $3.val_type;

              if($$.val_type == STRING_TYPE){
                fprintf(yyout, "ID: %s pren per valor: %s\n",$1.lexema, $3.val_string);
                $$.val_string = $3.val_string;
              } else if($$.val_type == FLOAT_TYPE){
                fprintf(yyout, "ID: %s pren per valor: %f\n",$1.lexema, $3.val_float);
                $$.val_float = $3.val_float;
              } else if($$.val_type == BOOL_TYPE){
                fprintf(yyout, "ID: %s pren per valor: %s\n",$1.lexema, $3.val_bol);
                $$.val_bol = $3.val_bol;
              } else{
                fprintf(yyout, "ID: %s pren per valor: %d\n",$1.lexema, $3.val_int);
                $$.val_int = $3.val_int;
              } 
              
            

            }

valor : FLOAT { $$.val_type = FLOAT_TYPE; $$.val_float = $1; }
      | INTEGER { $$.val_type = INT_TYPE; $$.val_int = $1; }
      | STRING { $$.val_type = STRING_TYPE; $$.val_string = $1.lexema; }
      | BOOLEAN { $$.val_type = BOOL_TYPE; $$.val_bol = $1.lexema; }

%%
