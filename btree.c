#include "btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
    CHAVE chaves[ORDEM-1];
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

// int PesquisaBinaria (int vet[], int chave, int Tam)
// {
//      int inf = 0;
//      int sup = Tam-1;
//      int meio;
//      while (inf <= sup)
//      {
//           meio = (inf + sup)/2;
//           if (chave == vet[meio])
//                return meio;
//           if (chave < vet[meio])
//                sup = meio-1;
//           else
//                inf = meio+1;
//      }
//      return -1;   // não encontrado
// }

// int buscaRecursiva_btree(PAGINA *pag, int idPesquisa)
// {
//     if(pag == NULL) return NAOENCONTRADO;

// }

// int busca_btree(BTREE *indice, int idPesquisa)
// {
//     return buscaRecursiva_btree(indice->raiz, idPesquisa);
// }

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

PAGINA* cria_pagina(){
    
}