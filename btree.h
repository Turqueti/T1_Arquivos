#ifndef TAD_BTREE_H
#define TAD_BTREE_H
#include <stdio.h>


typedef struct _CHAVE CHAVE;
typedef struct _PAGINA PAGINA;
typedef struct _BTREE BTREE;

FILE* cria_Btree(char* nomeArq);
BTREE* incializa_Btree_Vazia();
BTREE* carrega_Btee_from_bin(FILE* file);
void print_btree(BTREE* btree);
CHAVE* cria_chave();
PAGINA* cria_pagina();
void insere_pagina(FILE* file,PAGINA* pagina,int rnn);
PAGINA* carrega_pagina(FILE* file,int rnn);
void print_pagina(PAGINA* pag);
void print_chave(CHAVE* chave);
void free_pagina(PAGINA* pag);

#endif
