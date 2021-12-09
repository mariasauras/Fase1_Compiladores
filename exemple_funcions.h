#ifndef EXEMPLE_FUNCIONS_H
    #define EXEMPLE_FUNCIONS_H
    #include "symtab.h"
    

    int init_analisi_lexica(char *);
    int end_analisi_lexica();

    int init_analisi_sintactica(char *);
    int end_analisi_sintactica(void);

    int analisi_semantica(void);

    void yyerror(char *explanation);

    /*********************************************************************/
    /*                  ARITMETICAL FUNCTIONS                            */
    /*********************************************************************/

    void sum_op(sym_value_type * val, sym_value_type v1, sym_value_type v2);

    void rest_op(sym_value_type * val, sym_value_type v1, sym_value_type v2);

    void mul_op(sym_value_type * val, sym_value_type v1, sym_value_type v2);

    void div_op(sym_value_type * val, sym_value_type v1, sym_value_type v2);

    void mod_op(sym_value_type * val, sym_value_type v1, sym_value_type v2);

    void pow_op(sym_value_type * val, sym_value_type v1, sym_value_type v2);

    /*********************************************************************/
    /*                 MATRIX&VECTOR FUNCTIONS                           */
    /*********************************************************************/

    void col_ini(sym_value_type * matrix, sym_value_type matrix_value);

    void col_value(sym_value_type * matrix, sym_value_type v1, sym_value_type v2);

    void row_value(sym_value_type * matrix, sym_value_type v1, sym_value_type v2);

    void acces_vector(sym_value_type * vector, char * id, sym_value_type valist);

    void acces_matrix(sym_value_type * matrix, char * id, sym_value_type v1, sym_value_type v2);

    /**********************************************************************/
    /*                  ARITHMETICAL FUNCTIONS                            */
    /**********************************************************************/



#endif
