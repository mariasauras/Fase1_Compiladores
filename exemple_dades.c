#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "exemple_dades.h"

char *type_to_str(sym_value_type st)
{
  if (st.value_type == UNKNOWN_TYPE) {
    return strdup("Unknown type");
  } else if (st.value_type == INT_TYPE) {
    return strdup("Integer");
  } else if (st.value_type == FLOAT_TYPE) {
    return strdup("Float");
  } else if(st.value_type == STRING_TYPE){
    return strdup("Cadena");
  }else if(st.value_type == BOOL_TYPE){
    return strdup("Boolean");
  }else if(st.value_type == MATRIX_TYPE){
    return strdup("Vector/Matrix");
  }else if(st.value_type == ID_TYPE){
    return strdup("ID");
  }else{
    return strdup("Error: incorrect value for 'st'");
  }
}


char *value_info_to_str(sym_value_type st)
{
  char buffer[STR_MAX_LENGTH];

  if (st.value_type == UNKNOWN_TYPE) {
    sprintf(buffer, "Unknown value type");
  } else if (st.value_type == INT_TYPE) {
    sprintf(buffer, "Integer: %ld", st.value_data.enter);
  } else if (st.value_type == FLOAT_TYPE) {
    sprintf(buffer, "Float: %f", st.value_data.real);
  } else if(st.value_type == STRING_TYPE){
    sprintf(buffer, "Cadena: %s", st.value_data.ident.lexema); 
  } else if(st.value_type == BOOL_TYPE){
    if(st.value_data.boolean == 0){
      sprintf(buffer, "Boolean: FALSE");

    }else sprintf(buffer, "Boolean: TRUE");

  } else if(st.value_type == ID_TYPE){
    sprintf(buffer, "ID: %s", st.value_data.ident.lexema);
  } else if (st.value_type == MATRIX_TYPE){
    if(st.value_data.matrix_type == INT_TYPE) sprintf(buffer, "KK");
  }
  else {
    sprintf(buffer, "Error: incorrect value ");
  }
  return strdup(buffer);
}
