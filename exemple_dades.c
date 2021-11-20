#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "exemple_dades.h"


char *type_to_str(data_type val_type)
{
  if (val_type == UNKNOWN_TYPE) {
    return strdup("Unknown type");
  } else if (val_type == INT_TYPE) {
    return strdup("Integer");
  } else if (val_type == FLOAT_TYPE) {
    return strdup("Float");
  } else if(val_type == STRING_TYPE){
    return strdup("Cadena");
  }else if(val_type == BOOL_TYPE){
    return strdup("Boolean");
  }else{
    return strdup("Error: incorrect value for 'val_type'");
  }
}


char *value_info_to_str(value_info value)
{
  char buffer[STR_MAX_LENGTH];

  if (value.val_type == UNKNOWN_TYPE) {
    sprintf(buffer, "Unknown value type");
  } else if (value.val_type == INT_TYPE) {
    sprintf(buffer, "Integer: %d", value.val_int);
  } else if (value.val_type == FLOAT_TYPE) {
    sprintf(buffer, "Float: %f", value.val_float);
  } else if(value.val_type == STRING_TYPE){
    sprintf(buffer, "Cadena: %s", value.val_string);
  } else if(value.val_type == BOOL_TYPE){
    sprintf(buffer, "Boolean: %s", value.val_bol);
  }else {
    sprintf(buffer, "Error: incorrect value for 'value.val_type'");
  }
  return strdup(buffer);
}
