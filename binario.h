#ifndef TAD_BINARIO_H
#define TAD_BINARIO_H

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "Tad_Registro.h"

FILE* cria_binario(char* nomeArquivo);
FILE* fecha_binario(FILE *file);
void atualizaProxReg(FILE *file);
void atualizaNReg(FILE *file);
FILE* escreveLixo(FILE *file, int quantidade);
FILE* escreveLixoEstatico(FILE *file, int quantidade);
FILE* abreLeitura_Binario(char *nomeArquivo);
FILE* abreEscrita_Binario(char *nomeArquivo);
REGISTRO* getRegistro_Binario(FILE *file, int ID_Desejado);
int excluiRegistro_binario(FILE* file, int RRN);
int getQuantidadeRegistros_binario(FILE *file);
int verificaIntegridade_binario(FILE *file);
void insere_binario(FILE *file, REGISTRO *reg);

#endif
