#include "btree.h"
#include <stdio.h>
#include <stdio.h>
#include <string.h>

#define ORDEM 6
#define NAOENCONTRADO -1

struct CHAVE_
{
    int idregistro;
    int rrnRegistro;
};

struct PAGINA_
{
    int rrnpag;
    int nivel;
    int nDescendentes;
    CHAVE chaves[ORDEM-1];
    struct PAGINA_ *descendentes[ORDEM];
};

struct BTREE_
{
    struct PAGINA_ *raiz;
    int nChaves;
};

int PesquisaBinaria (int vet[], int chave, int Tam)
{
     int inf = 0;
     int sup = Tam-1;
     int meio;
     while (inf <= sup)
     {
          meio = (inf + sup)/2;
          if (chave == vet[meio])
               return meio;
          if (chave < vet[meio])
               sup = meio-1;
          else
               inf = meio+1;
     }
     return -1;   // não encontrado
}

int buscaRecursiva_btree(PAGINA *pag, int idPesquisa)
{
    if(pag == NULL) return NAOENCONTRADO;

}

int busca_btree(BTREE *indice, int idPesquisa)
{
    return buscaRecursiva_btree(indice->raiz, idPesquisa);
}