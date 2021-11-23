#include <stdio.h>
#include <stdlib.h>

extern int yyparse();
extern FILE *yyin;
extern FILE *yyout;
extern int yylineno;
#include "exemple_funcions.h" 


/*********************************************************************/
/*                   Funciones FLEX                                  */
/*********************************************************************/

int init_analisi_lexica(char *filename)
{
  int error;
  yyin = fopen(filename,"r");
  if(yyin == NULL) {
    error = EXIT_FAILURE;
  } else {
    error = EXIT_SUCCESS;
  }
  return error;
}


int end_analisi_lexica()
{
  int error;
  error = fclose(yyin);
  if (error == 0) {
    error = EXIT_SUCCESS;
  } else {
    error = EXIT_FAILURE;
  }
  return error;
}


int init_analisi_sintactica(char* filename)
{
  int error = EXIT_SUCCESS;
  yyout = fopen(filename,"w");
  if (yyout == NULL) {
    error = EXIT_FAILURE;
  }
  return error;
}


int end_analisi_sintactica(void)
{
  int error;

  error = fclose(yyout);

  if(error == 0) {
    error = EXIT_SUCCESS;
  } else {
    error = EXIT_FAILURE;
  }
  return error;
}


int analisi_semantica(void)
{
  int error;

  if (yyparse() == 0) {
    error =  EXIT_SUCCESS;
  } else {
    error =  EXIT_FAILURE;
  }
  return error;
}


void yyerror(char *explanation)
{
  fprintf(stderr, "Error: %s , in line %d\n", explanation, yylineno);
}

/*********************************************************************/
/*                   Funciones ARITMETICA                            */
/*********************************************************************/

 void op(sym_value_type * val, sym_value_type v1, sym_value_type v2){

  if(v1.value_type == BOOL_TYPE || v2.value_type == BOOL_TYPE  || v1.value_type == STRING_TYPE || v2.value_type == STRING_TYPE){
    yyerror("Can't operate with these value type");
  } else {
    if (v1.value_type == INT_TYPE && v2.value_type == INT_TYPE){
       (*val).value_type = INT_TYPE;
      (*val).value_data.enter = v1.value_data.enter + v2.value_data.enter;
    } else if(v1.value_type == INT_TYPE && v2.value_type == FLOAT_TYPE){
      (*val).value_type = FLOAT_TYPE;
      (*val).value_data.real = v1.value_data.enter + v2.value_data.real;
    } else if(v1.value_type == FLOAT_TYPE && v2.value_type == INT_TYPE){
       (*val).value_type = FLOAT_TYPE;
      (*val).value_data.real = v1.value_data.real + v2.value_data.enter;
    } else {
      (*val).value_data.real = v1.value_data.real + v2.value_data.real;
      (*val).value_type = FLOAT_TYPE;
    }
  }
}

  /*void op(sym_value_type * val, sym_value_type v1, sym_value_type v2){

  if(v1.value_type == BOOL_TYPE || v2.value_type == BOOL_TYPE  || v1.value_type == STRING_TYPE || v2.value_type == STRING_TYPE){
    yyerror("Can't operate with these value type");
  } 

  switch (v1.value_type){
    case INT_TYPE:
        switch(v2.value_type){
          case INT_TYPE:
              (*val).value_type = INT_TYPE;
              (*val).value_data.enter = v1.value_data.enter + v2.value_data.enter;
              break;
          case FLOAT_TYPE:
              (*val).value_type = FLOAT_TYPE;
              (*val).value_data.real = v1.value_data.enter + v2.value_data.real;
              break;
        };
        break;
    case FLOAT_TYPE:
      switch(v2.value_type){
            case INT_TYPE:
                (*val).value_type = FLOAT_TYPE;
                (*val).value_data.real = v1.value_data.real + v2.value_data.enter;
                break;
            case FLOAT_TYPE:
                (*val).value_type = FLOAT_TYPE;
                (*val).value_data.real = v1.value_data.real + v2.value_data.real;
                break;
          };
          break;
  }; 
}*/
  
