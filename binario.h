#ifndef TAD_BINARIO_H
#define TAD_BINARIO_H

#define N_PROX_REG 1
#define N_REG_INSER 5
#define N_REG_REMOV 9
#define N_REG_ATUALIZADOS 13
#define PRIMEIRO_REGISTRO 128

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "Tad_Registro.h"

FILE* cria_binario(char* nomeArquivo);
FILE* fecha_binario(FILE *file);
void atualizaProxReg(FILE *file);
void atualizaNReg(FILE *file, char opt);
void atualizaRemovidos(FILE *file);
FILE* escreveLixo(FILE *file, int quantidade);
FILE* escreveLixoEstatico(FILE *file, int quantidade);
FILE* abreLeitura_Binario(char *nomeArquivo);
FILE* abreEscrita_Binario(char *nomeArquivo);
REGISTRO* getRegistro_Binario(FILE *file, int RRN);
int excluiRegistro_binario(FILE* file, int RRN);
int getQuantidadeRegistros_binario(FILE *file);
int getQuantidadeRegistrosTotal_binario(FILE *file);
void insere_binario(FILE *file, REGISTRO *reg);
void atualizaRegistro_binario(FILE* file, REGISTRO* reg);
int verificaIntegridade_binario(FILE* file);

#endif
