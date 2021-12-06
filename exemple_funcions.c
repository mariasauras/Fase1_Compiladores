#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

/**********************************************************************/
/*                  ARITHMETICAL FUNCTIONS                            */
/**********************************************************************/

void sum_op(sym_value_type * val, sym_value_type v1, sym_value_type v2){

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
      (*val).value_type = FLOAT_TYPE;
      (*val).value_data.real = v1.value_data.real + v2.value_data.real;
      
    }
  }
}

void rest_op(sym_value_type * val, sym_value_type v1, sym_value_type v2){

  if(v1.value_type == BOOL_TYPE || v2.value_type == BOOL_TYPE  || v1.value_type == STRING_TYPE || v2.value_type == STRING_TYPE){
    yyerror("Can't operate with these value type");
  } else {
    if (v1.value_type == INT_TYPE && v2.value_type == INT_TYPE){
      (*val).value_type = INT_TYPE;
      (*val).value_data.enter = v1.value_data.enter - v2.value_data.enter;
    } else if(v1.value_type == INT_TYPE && v2.value_type == FLOAT_TYPE){
      (*val).value_type = FLOAT_TYPE;
      (*val).value_data.real = v1.value_data.enter - v2.value_data.real;
    } else if(v1.value_type == FLOAT_TYPE && v2.value_type == INT_TYPE){
       (*val).value_type = FLOAT_TYPE;
      (*val).value_data.real = v1.value_data.real - v2.value_data.enter;
    } else {
      (*val).value_type = FLOAT_TYPE;
      (*val).value_data.real = v1.value_data.real - v2.value_data.real;
      
    }
  }
}

void mul_op(sym_value_type * val, sym_value_type v1, sym_value_type v2){

  if(v1.value_type == BOOL_TYPE || v2.value_type == BOOL_TYPE ){
    yyerror("Can't operate with these value type");
  } else {
    if (v1.value_type == INT_TYPE && v2.value_type == INT_TYPE){
      (*val).value_type = INT_TYPE;
      (*val).value_data.enter = v1.value_data.enter * v2.value_data.enter;
    } else if(v1.value_type == INT_TYPE && v2.value_type == FLOAT_TYPE){
      (*val).value_type = FLOAT_TYPE;
      (*val).value_data.real = v1.value_data.enter * v2.value_data.real;
    } else if(v1.value_type == FLOAT_TYPE && v2.value_type == INT_TYPE){
       (*val).value_type = FLOAT_TYPE;
      (*val).value_data.real = v1.value_data.real * v2.value_data.enter;
    } else if(v1.value_type == FLOAT_TYPE && v2.value_type == FLOAT_TYPE) {
      (*val).value_type = FLOAT_TYPE;
      (*val).value_data.real = v1.value_data.real * v2.value_data.real;
    } else{
      /* CONCAT*/
      (*val).value_type = STRING_TYPE;
      (*val).value_data.ident.lexema = malloc(strlen(v1.value_data.ident.lexema) + strlen(v2.value_data.ident.lexema) + 1);
      strcpy((*val).value_data.ident.lexema, v1.value_data.ident.lexema);
      strcat((*val).value_data.ident.lexema, v2.value_data.ident.lexema);
    }
  }
}

void div_op(sym_value_type * val, sym_value_type v1, sym_value_type v2){

  if(v1.value_type == BOOL_TYPE || v2.value_type == BOOL_TYPE  || v1.value_type == STRING_TYPE || v2.value_type == STRING_TYPE){
    yyerror("Can't operate with these value type");
  } else {
    if (v1.value_type == INT_TYPE && v2.value_type == INT_TYPE){
      (*val).value_type = FLOAT_TYPE;
      (*val).value_data.real = (float)v1.value_data.enter / v2.value_data.enter;
    } else if(v1.value_type == INT_TYPE && v2.value_type == FLOAT_TYPE){
      (*val).value_type = FLOAT_TYPE;
      (*val).value_data.real = v1.value_data.enter / v2.value_data.real;
    } else if(v1.value_type == FLOAT_TYPE && v2.value_type == INT_TYPE){
       (*val).value_type = FLOAT_TYPE;
      (*val).value_data.real = v1.value_data.real / v2.value_data.enter;
    } else {
      (*val).value_type = FLOAT_TYPE;
      (*val).value_data.real = v1.value_data.real / v2.value_data.real;
      
    }
  }
}

void mod_op(sym_value_type * val, sym_value_type v1, sym_value_type v2){

  if(v1.value_type == BOOL_TYPE || v2.value_type == BOOL_TYPE  || v1.value_type == STRING_TYPE || 
  v2.value_type == STRING_TYPE || v1.value_type == FLOAT_TYPE || v2.value_type == FLOAT_TYPE ){
    yyerror("Can't operate with these value type");
  } else {
    (*val).value_type = INT_TYPE;
    (*val).value_data.enter = v1.value_data.enter % v2.value_data.enter;
  }
}

void pow_op(sym_value_type * val, sym_value_type v1, sym_value_type v2){

  if(v1.value_type == BOOL_TYPE || v2.value_type == BOOL_TYPE  || v1.value_type == STRING_TYPE || v2.value_type == STRING_TYPE){
    yyerror("Can't operate with these value type");
  } else {
    if (v1.value_type == INT_TYPE && v2.value_type == INT_TYPE){
      (*val).value_type = INT_TYPE;
      (*val).value_data.enter = pow(v1.value_data.enter,v2.value_data.enter);  
    } else if(v1.value_type == INT_TYPE && v2.value_type == FLOAT_TYPE){
      (*val).value_type = FLOAT_TYPE;
      (*val).value_data.real = pow(v1.value_data.enter,v2.value_data.real);
    } else if(v1.value_type == FLOAT_TYPE && v2.value_type == INT_TYPE){
       (*val).value_type = FLOAT_TYPE;
      (*val).value_data.real = pow(v1.value_data.real,v2.value_data.enter);
    } else {
      (*val).value_type = FLOAT_TYPE;
      (*val).value_data.real = pow(v1.value_data.real,v2.value_data.real);
      
    }
  }
}

/*********************************************************************/
/*                 MATRIX&VECTOR FUNCTIONS                           */
/*********************************************************************/

/* Function to inicialize columns */

void col_ini(sym_value_type * matrix, sym_value_type matrix_value){

  (*matrix).value_type = MATRIX_TYPE;
  /* Indico que tipo de valor tendra */
  if(matrix_value.value_type == INT_TYPE){

    (*matrix).value_data.matrix_type = INT_TYPE;

    (*matrix).value_data.integer_matrix = calloc(1, sizeof(long));
    if((*matrix).value_data.integer_matrix == NULL) yyerror("Error. Can't inicialize heap memory");
    (*matrix).value_data.integer_matrix[0] = matrix_value.value_data.enter;

  } else if(matrix_value.value_type == FLOAT_TYPE){
   
    (*matrix).value_data.matrix_type = FLOAT_TYPE;

    (*matrix).value_data.float_matrix = calloc(1, sizeof(float));
     if((*matrix).value_data.float_matrix  == NULL) yyerror("Error. Can't inicialize heap memory");
    (*matrix).value_data.float_matrix[0] = matrix_value.value_data.real;

  } else yyerror(" Matrix only accept Integer or Float.");
  
  (*matrix).value_data.num_elems = 1;
  (*matrix).value_data.column = 1;
  
}

/* Function to inicialice more than one columns */
void col_value(sym_value_type * matrix, sym_value_type v1, sym_value_type v2){
  
  (*matrix).value_type = MATRIX_TYPE;

  if(v2.value_type == INT_TYPE){

    (*matrix).value_data.matrix_type = INT_TYPE;

    (*matrix).value_data.integer_matrix = calloc(v1.value_data.column+1, sizeof(long));
    if((*matrix).value_data.integer_matrix  == NULL) yyerror("Error. Can't inicialize heap memory");

    for(int i = 0; i < v1.value_data.column; i++) 
      (*matrix).value_data.integer_matrix[i] = v1.value_data.integer_matrix[i];
    
    free(v1.value_data.integer_matrix);

    (*matrix).value_data.integer_matrix[v1.value_data.column] = v2.value_data.enter;

  } else if(v2.value_type == FLOAT_TYPE){
    /* Indico que tipo de valor tendra */
    (*matrix).value_data.matrix_type = FLOAT_TYPE;
    (*matrix).value_data.float_matrix = calloc(v1.value_data.column+1, sizeof(float));
    if((*matrix).value_data.float_matrix  == NULL) yyerror("Error. Can't inicialize heap memory");

    for(int i = 0; i < v1.value_data.column; i++) 
      (*matrix).value_data.float_matrix[i] = v1.value_data.float_matrix[i];
    
    free(v1.value_data.float_matrix);

    (*matrix).value_data.float_matrix[v1.value_data.column] = v2.value_data.real;

  } else yyerror(" Matrix only accept Integer or Float.");
  
  (*matrix).value_data.column=v1.value_data.column+1;
  (*matrix).value_data.num_elems++;
}

void row_value(sym_value_type *matrix, sym_value_type v1, sym_value_type v2){

  (*matrix).value_type = MATRIX_TYPE;
  
  if(v1.value_data.column != v2.value_data.column) yyerror("Error. Diferent size of columns in matrix");

  if(v1.value_data.matrix_type == INT_TYPE && v2.value_data.matrix_type == INT_TYPE){
    (*matrix).value_data.matrix_type = INT_TYPE;

    (*matrix).value_data.integer_matrix = calloc(v1.value_data.num_elems+v2.value_data.num_elems, sizeof(long));
    if((*matrix).value_data.integer_matrix  == NULL) yyerror("Error. Can't inicialize heap memory");

    for(int i=0; i<v1.value_data.num_elems ; i++) (*matrix).value_data.integer_matrix[i] = v1.value_data.integer_matrix[i];

    int j = 0;
    for(int i = v1.value_data.num_elems ; i<v2.value_data.column+v1.value_data.num_elems; i++){
      (*matrix).value_data.integer_matrix[i] = v2.value_data.integer_matrix[j];
      j++;
    }

    free(v1.value_data.integer_matrix);
    free(v2.value_data.integer_matrix);
   
  } else if (v1.value_data.matrix_type == FLOAT_TYPE && v2.value_data.matrix_type == FLOAT_TYPE){
    (*matrix).value_data.matrix_type = FLOAT_TYPE;

    (*matrix).value_data.float_matrix = calloc(v1.value_data.num_elems+v2.value_data.num_elems, sizeof(float));
    if((*matrix).value_data.float_matrix  == NULL) yyerror("Error. Can't inicialize heap memory");
  
    for(int i=0; i<v1.value_data.num_elems ; i++) (*matrix).value_data.float_matrix[i] = v1.value_data.float_matrix[i];

    int j = 0;
    for(int i = v1.value_data.num_elems ; i<v2.value_data.column+v1.value_data.num_elems; i++){
      (*matrix).value_data.float_matrix[i] = v2.value_data.float_matrix[j];
      j++;
    }

    free(v1.value_data.float_matrix);
    free(v2.value_data.float_matrix);
  } else yyerror("INCORRECT VALUE OF MATRIX & VECTOR");

  (*matrix).value_data.row = (*matrix).value_data.row + 1;
  (*matrix).value_data.column = v2.value_data.column;
  (*matrix).value_data.num_elems = (*matrix).value_data.row * (*matrix).value_data.column;


}



