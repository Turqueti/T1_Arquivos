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
void insere_binario(FILE *file, int idNasc, int idadeM, char dataNascimento[10], char sexoBebe, char estadoMae[2], char estadoBebe[2], char *cidadeMae, char *cidadeFilho);

#endif