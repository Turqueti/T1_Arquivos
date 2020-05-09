#define N_PROX_REG 1
#define N_REG_INSER 5
#define N_REG_REMOV 9
#define N_REG_ATUALIZADOS 13
#define PRIMEIRO_REGISTRO 128

#include "binario.h"

FILE* cria_binario(char* nomeArquivo)
{
    int zero = 0;
    char lixo = '$';
    FILE *file;
    file = fopen(nomeArquivo, "wb+");

    for (int i = 0; i < 17; i++)
    {
        fwrite(&zero,1,1,file);
    }

    for (int i = 17; i < 128; i++)
    {
        fwrite(&lixo,1,1,file);
    } 
   return file;    
}

FILE* fecha_binario(FILE *file)
{
    fseek(file,0,SEEK_SET);
    fprintf(file,"%d", 1);
    fclose(file);
    return NULL;
}

void atualizaProxReg(FILE *file)
{
    int nUltimo = (int)ftell(file);
    fseek(file, N_PROX_REG, SEEK_SET);
    fwrite(&nUltimo, sizeof(int), 1, file);
    return;
}

void atualizaNReg(FILE *file)
{
    int nReg;
    fseek(file, N_REG_INSER, SEEK_SET);

    fread(&nReg, sizeof(int), 1, file);
    nReg++;
    fwrite(&nReg, sizeof(int), 1, file);
    return;

}

FILE* escreveLixo(FILE *file, int quantidade)
{
    char zero = '\0';
    char lixo = '$';
    fwrite(&zero, 1, 1, file);
    for (int i = 1; i < quantidade; i++)
    {
        fwrite(&lixo, 1, 1, file);
    }
    return file;
}

void insere_binario(FILE *file, int idNasc, int idadeM, char dataNascimento[10], char sexoBebe, char estadoMae[2], char estadoBebe[2], char *cidadeMae, char *cidadeFilho)
{
    int tam1 = strlen(cidadeMae) +1;
    int tam2 = strlen(cidadeFilho) +1;
    char lixo = '$';

    fseek(file, 0, SEEK_END);

    fwrite(&tam1, sizeof(int), 1, file);
    fwrite(&tam2, sizeof(int), 1, file);
    fwrite(cidadeMae, tam1 * sizeof(char), strlen(cidadeMae), file);
    fwrite(cidadeFilho, tam2 * sizeof(char), strlen(cidadeFilho), file);

    file = escreveLixo(file - 1, ( (104 - ftell(file))));
    
    fwrite(&idNasc, sizeof(int), 1, file);
    fwrite(&idadeM, sizeof(int), 1, file);

    if(strlen(dataNascimento) > 0)
        fwrite(dataNascimento,10 * sizeof(char), 1, file);
    else file = escreveLixo(file, 10);

    if(sexoBebe != '\0')
        fwrite(&sexoBebe, sizeof(char), 1, file);
    else file = escreveLixo(file, 1);

    if(strlen(estadoMae) > 0)
        fwrite(estadoMae, 2 * sizeof(char), 1, file);
    else file = escreveLixo(file, 2);

    if(strlen(estadoBebe) > 0)
        fwrite(estadoBebe, 2 * sizeof(char), 1, file);
    else file = escreveLixo(file, 2);

    atualizaProxReg(file);
    atualizaNReg(file);
    return;
}