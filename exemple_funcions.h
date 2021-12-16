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
    /*                  ARITHMETICAL FUNCTIONS                            */
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
    /*                 BOOLEAN & RELATIONAL FUNCTIONS                     */
    /**********************************************************************/

    void not_op(sym_value_type * not, sym_value_type v1);

    void and_op(sym_value_type * and, sym_value_type v1, sym_value_type v2);

    void or_op(sym_value_type * or, sym_value_type v1, sym_value_type v2);

    void gt_op(sym_value_type * gt, sym_value_type v1, sym_value_type v2);

    void ge_op(sym_value_type * ge, sym_value_type v1, sym_value_type v2);

    void lt_op(sym_value_type * lt, sym_value_type v1, sym_value_type v2);

    void le_op(sym_value_type * le, sym_value_type v1, sym_value_type v2);

    void eq_op(sym_value_type * eq, sym_value_type v1, sym_value_type v2);

    void dif_op(sym_value_type * dif, sym_value_type v1, sym_value_type v2);



#endif
