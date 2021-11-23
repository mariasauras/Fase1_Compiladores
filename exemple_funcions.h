#ifndef EXEMPLE_FUNCIONS_H
    #define EXEMPLE_FUNCIONS_H
    #include "symtab.h"


    int init_analisi_lexica(char *);
    int end_analisi_lexica();

    int init_analisi_sintactica(char *);
    int end_analisi_sintactica(void);

    int analisi_semantica(void);

    void yyerror(char *explanation);

    void op(sym_value_type * val, sym_value_type v1, sym_value_type v2);


#endif
