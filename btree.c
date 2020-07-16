#include "btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binario.h"
#include "Tad_Registro.h"

#define ORDEM 6
#define NAOENCONTRADO -1
#define TAMPAG 72

struct _CHAVE
{
    int idregistro;
    int rrnRegistro;
};

struct _PAGINA
{
    int nivel;
    int nroChaves;
    CHAVE* chaves[ORDEM-1];
    int descendentes[ORDEM];
};

struct _BTREE
{
    char status;
    int raiz;
    int nroNiveis;
    int proxRNN;
    int nroChaves;

};

FILE* cria_Btree(char* nomeArq){
    BTREE* cabecalho = incializa_Btree_Vazia();
    FILE* file = NULL;
    file = fopen(nomeArq,"wb+");
    if (file == NULL)
    {
        return file;
    }
    

    fseek(file,0,SEEK_SET);
    fwrite(&cabecalho->status,1,1,file);
    fwrite(&cabecalho->raiz,4,1,file);
    fwrite(&cabecalho->nroNiveis,4,1,file);
    fwrite(&cabecalho->proxRNN,4,1,file);
    fwrite(&cabecalho->nroChaves,4,1,file);

    char lixo[TAMPAG-17];
    for (int i = 0; i < TAMPAG - 17; i++)
    {
        lixo[i] = '$';
    }
    

    fwrite(&lixo,1,TAMPAG-17,file);
    free(cabecalho);
    return file;

}

BTREE* incializa_Btree_Vazia(){
    BTREE* btree = malloc(sizeof(BTREE));
    if (btree == NULL)
    {
        return btree;
    }
    

    btree->status = '1';
    btree->raiz = -1;
    btree->nroChaves = 0;
    btree->nroNiveis = 0;
    return btree;
}

BTREE* carrega_Btee_from_bin(FILE* file){
    BTREE* btree = malloc(sizeof(BTREE));


    fseek(file,0,SEEK_SET);
    fread(&btree->status,1,1,file);
    fread(&btree->raiz,4,1,file);
    fread(&btree->nroNiveis,4,1,file);
    fread(&btree->proxRNN,4,1,file);
    fread(&btree->nroChaves,4,1,file);

    print_btree(btree);

    return btree;
}

void print_btree(BTREE* btree){
    printf("status: %c\n",btree->status);
    printf("raiz: %d\n",btree->raiz);
    printf("nroNiveis: %d\n",btree->nroNiveis);
    printf("proxRNN: %d\n",btree->proxRNN);
    printf("nroChaves: %d\n",btree->nroChaves);
}

CHAVE* cria_chave(){
    CHAVE* chave = malloc(sizeof(CHAVE));
    chave->idregistro = -1;
    chave->rrnRegistro = -1;

    return chave;
}

PAGINA* cria_pagina(){
    PAGINA* pag = malloc(sizeof(PAGINA));
    pag->nivel = -1;
    pag->nroChaves = 0;
    
    for (int i = 0; i < (ORDEM - 1); i++)
    {
        pag->chaves[i] = cria_chave();
        pag->descendentes[i] = -1;
    }
    
    pag->descendentes[ORDEM - 1] = -1;

    return pag;
}

/*
    insere uma pagina no rnn indicado
*/
void insere_pagina(FILE* file,PAGINA* pagina,int rnn){

    fseek(file,TAMPAG*rnn,SEEK_SET);
    fwrite(&pagina->nivel,4,1,file);
    fwrite(&pagina->nroChaves,4,1,file);
    for (int i = 0; i < ORDEM - 1 ; i++)
    {
        fwrite(&pagina->chaves[i]->idregistro,4,1,file);
        fwrite(&pagina->chaves[i]->rrnRegistro,4,1,file);

    }
    for (int i = 0; i < ORDEM; i++)
    {
        fwrite(&pagina->descendentes[i],4,1,file);
    }
    
}

PAGINA* carrega_pagina(FILE* file,int rnn){
    
    PAGINA* pag = cria_pagina();

    fseek(file,TAMPAG*rnn,SEEK_SET);
    fread(&pag->nivel,4,1,file);
    fread(&pag->nroChaves,4,1,file);

    for (int i = 0; i < ORDEM - 1; i++)
    {
        fread(&pag->chaves[i]->idregistro,4,1,file);
        fread(&pag->chaves[i]->rrnRegistro,4,1,file);
    }

    for (int i = 0; i < ORDEM; i++)
    {
        fread(&pag->descendentes[i],4,1,file);
    }
    

    return pag;
}

void print_pagina(PAGINA* pag){
    
    printf("nivel: %d\n",pag->nivel);
    printf("nroChaves: %d\n",pag->nroChaves);

    printf("\nchaves:\n");
    for (int i = 0; i < ORDEM - 1; i++)
    {
        print_chave(pag->chaves[i]);
    }

    printf("\ndescendentes:\n");
    for (int i = 0; i < ORDEM; i++)
    {
        printf("descendente[%d]: %d\n",i,pag->descendentes[i]);
    }

    printf("\n");
}

void print_chave(CHAVE* chave){
    printf("chave: %02d   rnnRegistro: %02d\n",chave->idregistro,chave->rrnRegistro);
}

void free_pagina(PAGINA* pag){
    for (int i = 0; i < ORDEM - 1; i++)
    {
        free(pag->chaves[i]);
    }
    free(pag);

}

int buscaRecursiva_btree(FILE* file, int* rrnPag, int id)
{
    int ret = 0;
    if(rrnPag == -1) return NAOENCONTRADO;
    PAGINA *pag = carrega_pagina(file, rrnPag);

    for (int i = 0; i < pag->nroChaves - 1; i++)
    {
        if(pag->chaves[i]->idregistro == id)
        {
            ret = pag->chaves[i]->rrnRegistro;
            free_pagina(pag);
            return ret;
        }
        if(pag->chaves[i]->idregistro > id)
        {
            ret = buscaRecursiva_btree(file, pag->descendentes[i], id);
            free_pagina(pag);
            return ret;
        }
    }
    ret = buscaRecursiva_btree(file, pag->descendentes[pag->nroChaves], id);
    free_pagina(pag);
    return ret;
}

int busca_btree(FILE *file, int id)
{
    BTREE *tree = carrega_Btee_from_bin(file);
    return buscaRecursiva_btree(file, tree->raiz, id);
    free(tree);
}

int insere_btree(FILE* indexAB, FILE* binario)
{
    if(indexAB == NULL || binario == NULL)return -1;

    int nRegistros = 0;
    REGISTRO *regAux = NULL;
    CHAVE *chaveAux = NULL;
    chaveAux = cria_chave();

    fseek(binario, N_REG_INSER, SEEK_SET);
    fread(&nRegistros, 4, 1, binario);

    for (int i = 0; i < nRegistros; i++)
    {
        regAux = getRegistro_Binario(binario, i);
        chaveAux = cria_chave();
        chaveAux->rrnRegistro = i;
        chaveAux->idregistro = getIdNascimento_Registro(regAux);

        
        free_Registro(regAux);
        free(chaveAux);
    }
}

