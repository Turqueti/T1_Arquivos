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
    /*
    int nUltimo = (int)ftell(file);
    fseek(file, N_PROX_REG, SEEK_SET);
    fwrite(&nUltimo, sizeof(int), 1, file);
    return;*/
    int nReg;
    fseek(file, N_PROX_REG, SEEK_SET);

    fread(&nReg, sizeof(int), 1, file);
    nReg++;
    fseek(file, N_PROX_REG, SEEK_SET);
    fwrite(&nReg, sizeof(int), 1, file);
    return;
}

void atualizaNReg(FILE *file)
{
    int nReg;
    fseek(file, N_REG_INSER, SEEK_SET);

    fread(&nReg, sizeof(int), 1, file);
    nReg++;
    fseek(file, N_REG_INSER, SEEK_SET);
    fwrite(&nReg, sizeof(int), 1, file);
    return;
}

FILE* escreveLixo(FILE *file, int quantidade)
{
    char lixo = '$';
    for (int i = 0; i < quantidade; i++)
    {
        fwrite(&lixo, 1, 1, file);
    }
    return file;
}

FILE* escreveLixoEstatico(FILE *file, int quantidade)
{
    char lixo = '$';
    char zero = '\0';
    fwrite(&zero, 1, 1, file);
    for (int i = 1; i < quantidade; i++)
    {
        fwrite(&lixo, 1, 1, file);
    }
    return file;
}

/*
    retorna o ponteiro para file binaria para ser editado, caso incosistencia no arquivo retorna NULL
*/

FILE* abreLeitura_Binario(char *nomeArquivo)
{
    FILE *file;
    file = fopen(nomeArquivo, "rb");
    if (file != NULL)
    {
        int integridade = verificaIntegridade_Binario(file);
        if (integridade == 0)
        {
            fclose(file);
            return NULL;
        }
        
    }
    

    return file;
}

REGISTRO* getRegistro_Binario(FILE *file, int ID_Desejado)
{
    fseek(file, 0, SEEK_END);
    if(ftell(file) < 128 + (ID_Desejado * 128)) return NULL;

    int tam1, tam2;
    int idNascimento;
    int idadeMae;
    char dataNascimento[10];
    char sexoBebe;
    char estadoMae[2];
    char estadoBebe[2];
    char cidMae[101], cidBB[101];

    fseek(file, 128 + ((ID_Desejado - 1) * 128), SEEK_SET);

    fread(&tam1, sizeof(int), 1,  file);
    if(tam1 == -1)return NULL;
    fread(&tam2, sizeof(int), 1,  file);

    REGISTRO *reg;
    reg = cria_Registro();
    
    if(tam1 != 0)
    {
        fread(cidMae, tam1, 1, file);
        cidMae[tam1] = '\0';
        setCidadeMae_Registro(reg, cidMae);
    }

    if(tam2 != 0)
    {
        fread(cidBB, tam2, 1, file);
        cidBB[tam2] = '\0';
        setCidadeBebe_Registro(reg, cidBB);
    }
    
    fseek(file, (104 - (tam1+tam2+7)), SEEK_CUR);

    fread(&idNascimento, sizeof(int), 1, file);
    fread(&idadeMae, sizeof(int), 1, file);
    fread(dataNascimento,10 * sizeof(char), 1, file);
    fread(&sexoBebe, sizeof(char), 1, file);
    fread(estadoMae, 2 * sizeof(char), 1, file);
    fread(estadoBebe, 2 * sizeof(char), 1, file);

    setIdNascimento_Registro(reg, idNascimento);
    setIdadeMae_Registro(reg, idadeMae);
    setDataNascimento_Registro(reg, dataNascimento);
    setSexoBebe_Registro(reg, sexoBebe);
    setEstadoMae_Registro(reg, estadoMae);
    setEstadoBebe_Registro(reg, estadoBebe);
    return reg;
}

int getQuantidadeRegistros_binario(FILE *file)
{
    int quantidade;

    fseek(file, N_REG_INSER, SEEK_SET);

    fread(&quantidade, sizeof(int), 1, file);

    return quantidade;
}

void insere_binario(FILE *file, REGISTRO *reg)
{
    char zero = '\0';
    int idNascimento = getIdNascimento_Registro(reg);
    int idadeMae = getIdadeMae_Registro(reg);
    char dataNascimento[10];
    strncpy(dataNascimento, getDataNascimento_Registro(reg),10);
    char sexoBebe = getSexoBebe_Registro(reg);
    char estadoMae[2];
    strncpy(estadoMae, getEstadoMae_Registro(reg),2);
    char estadoBebe[2];
    strncpy(estadoBebe,getEstadoBebe_Registro(reg),2);
    char *cidMae, *cidBB;

    cidMae = getCidadeMae_Registro(reg);
    cidBB = getCidadeBebe_Registro(reg);
    if(cidMae == NULL) cidMae = &zero;
    if(cidBB == NULL) cidBB = &zero;
    int tam1 = strlen(cidMae);
    int tam2 = strlen(cidBB);
    fseek(file, 0, SEEK_END);

    fwrite(&tam1, sizeof(int), 1, file);
    fwrite(&tam2, sizeof(int), 1, file);
    fwrite(cidMae, tam1 * sizeof(char), 1, file);
    fwrite(cidBB, tam2 * sizeof(char), 1, file);
    file = escreveLixo(file, ( (104 - (tam1+tam2+7)))); //TODO: Verificar se esta certo
    
    fwrite(&idNascimento, sizeof(int), 1, file);
    fwrite(&idadeMae, sizeof(int), 1, file);

    if(strlen(dataNascimento) > 0)
        fwrite(dataNascimento,10 * sizeof(char), 1, file);
    else file = escreveLixoEstatico(file, 10);

    //if(sexoBebe != '\0')
        fwrite(&sexoBebe, sizeof(char), 1, file);
    //else file = escreveLixoEstatico(file, 1);

    if(strlen(estadoMae) > 0)
        fwrite(estadoMae, 2 * sizeof(char), 1, file);
    else file = escreveLixoEstatico(file, 2);

    if(strlen(estadoBebe) > 0)
        fwrite(estadoBebe, 2 * sizeof(char), 1, file);
    else file = escreveLixoEstatico(file, 2);

    atualizaProxReg(file);
    atualizaNReg(file);
    return;
}

/*retorna 0 ou 1 caso o arquivo esteja inconsistente ou consistente respec.

    Parametros:
    [in]FILE* file

    retorno:
    int bool_integridade
*/
int verificaIntegridade_Binario(FILE* file){
    char ret;
    fread(&ret,sizeof(char),1,file);
    return (int)ret - '0';
}