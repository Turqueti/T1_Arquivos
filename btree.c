#include "btree.h"

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

void busca_btree()
{

}