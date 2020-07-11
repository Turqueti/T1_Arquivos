#define N_PROX_REG 1
#define N_REG_INSER 5
#define N_REG_REMOV 9
#define N_REG_ATUALIZADOS 13
#define PRIMEIRO_REGISTRO 128

#include "binario.h"

/*
    Cria um arquivo binario, o abre pare leitura e escrita e o inicializa com um
    cabeçalho.

    Parametros:
    [in] char* nomeArquivo

    Retorno:
    FILE*: ponteiro para o inicio do arquivo binario
    NULL: se algo der errado.
*/
FILE* cria_binario(char* nomeArquivo)
{
    int zero = 0;
    char lixo = '$';
    FILE *file = NULL;
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

/*
    Fecha um arquivo binario e ativa a integridade de seus dados

    Parametros:
    [in] FILE *file

    Retorno:
    NULL
*/
FILE* fecha_binario(FILE *file)
{
    if(file == NULL) return NULL;
    
    fseek(file,0,SEEK_SET);
    fprintf(file,"%c", '1');
    fclose(file);
    return NULL;
}

/*
    Atualiza o RRN do aquivo quando um registro é inserido

    Parametros:
    [in] FILE* file
*/
void atualizaProxReg(FILE *file)
{
    if(file == NULL) return;

    int nReg;
    fseek(file, N_PROX_REG, SEEK_SET);

    fread(&nReg, sizeof(int), 1, file);
    nReg++;
    fseek(file, N_PROX_REG, SEEK_SET);
    fwrite(&nReg, sizeof(int), 1, file);
    return;
}

/*
    Atualiza o cabeçalho com o numero de registros contidos no arquivo

    Parametros:
    [in] FILE* file
    [in] char opt  - '1' Insercao; '2' remocao
*/
void atualizaNReg(FILE *file, char opt)
{
    if(file == NULL) return;
    int nReg;
    fseek(file, N_REG_INSER, SEEK_SET);

    fread(&nReg, sizeof(int), 1, file);
    if(opt == '1')nReg++;
    else nReg--;
    fseek(file, N_REG_INSER, SEEK_SET);
    fwrite(&nReg, sizeof(int), 1, file);
    return;
}

void atualizaRemovidos(FILE *file)
{
    if(file == NULL) return;
    int nReg;
    fseek(file, N_REG_REMOV, SEEK_SET);

    fread(&nReg, sizeof(int), 1, file);
    nReg++;
    fseek(file, N_REG_REMOV, SEEK_SET);
    fwrite(&nReg, sizeof(int), 1, file);
    return;
}

/*
    Escreve uma quatidade de '$' em sequencia em algum ponto do arquivo

    Parametros:
    [in] FILE* file
    [in] int quantidade

    Retorno:
    FILE*: ponteiro para a continação do arquivo apos a sequencia de '$'
    NULL: se arquivo for nulo.
*/
FILE* escreveLixo(FILE *file, int quantidade)
{
    if(file == NULL) return NULL;

    char lixo = '$';
    for (int i = 0; i < quantidade; i++)
    {
        fwrite(&lixo, 1, 1, file);
    }
    return file;
}

/*
    Escreve um '\0' e uma quatidade de '$' em sequencia em algum ponto do arquivo

    Parametros:
    [in] FILE* file
    [in] int quantidade

    Retorno:
    FILE*: ponteiro para a continação do arquivo apos a sequencia de '$'
    NULL: se o arquivo for nulo
*/
FILE* escreveLixoEstatico(FILE *file, int quantidade)
{
    if(file == NULL) return NULL;

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
    Abre um arquivo binario ja existente apenas para leitura.

    Parametros:
    [in] char* nomeArquivo

    Retorno:
    FILE*: ponteiro para o inicio do arquivo binario
    NULL: se o arquivo estiver corrompido
*/
FILE* abreLeitura_Binario(char *nomeArquivo)
{
    FILE *file;
    file = fopen(nomeArquivo, "rb");
    if (file != NULL)
    {
        int integridade = verificaIntegridade_binario(file);
        if (integridade == 0)
        {
            fclose(file);
            return NULL;
        }
        
    }
    return file;
}

/*
    Abre um arquivo binario ja existente para leitura e escrita.

    Parametros:
    [in] char* nomeArquivo

    Retorno:
    FILE*: ponteiro para o inicio do arquivo binario
    NULL: se o arquivo estiver corrompido
*/
FILE* abreEscrita_Binario(char *nomeArquivo)
{
    FILE *file;
    file = fopen(nomeArquivo, "rb+");
    if (file != NULL)
    {
        int integridade = verificaIntegridade_binario(file);
        if (integridade == 0)
        {
            fclose(file);
            return NULL;
        }

        fseek(file,0,SEEK_SET); // Escreve a inconstancia
        fprintf(file,"%c", '0');
        
    }
    return file;
}
/*
    Recupera um certo registro já inserido no arquivo binario atraves do seu
    idNascimento e retorna suas informacoes atraves da estrutura REGISTRO

    Parametros:
    [in] FILE* file
    [in] RRN

    Retorno:
    REGISTRO*: ponteiro para o registro se ele for encontrado
    NULL: se o resgistro não for encontrado
*/
REGISTRO* getRegistro_Binario(FILE *file, int RRN)
{
    fseek(file, 0, SEEK_END);
    if(ftell(file) < 128 + (RRN * 128)) return NULL;

    int tam1, tam2;
    int idNascimento;
    int idadeMae;
    char dataNascimento[10];
    char sexoBebe;
    char estadoMae[2];
    char estadoBebe[2];
    char cidMae[101], cidBB[101];

    fseek(file, 128 + ((RRN - 1) * 128), SEEK_SET);

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

/*
    Exclui logicamente um registro a partir do seu RRN
    Parametros:
    [in] FILE* file
    [in] int RRN

    Retorno:
    int: 0 Se der errado (RRN não existir)
    int: 1 se a exlusão acontecer
*/
int excluiRegistro_binario(FILE* file, int RRN)
{
    fseek(file, 0, SEEK_END);
    if(ftell(file) < 128 + (RRN * 128)) return 0;

    int setter = -1;

    fseek(file, 128 + ((RRN - 1) * 128), SEEK_SET);

    fwrite(&setter, sizeof(int), 1,  file);
    atualizaRemovidos(file);
    atualizaNReg(file, '2');
    return 1;    
}

/*
    Recupera a quantidade de registro inseridos no arquivo binario

    Parametros:
    [in] FILE* file

    Retorno:
    int: [0 ate __INT8_MAX__] numero de registros inseridos
    int: -1 se o arquivo for nulo.
*/
int getQuantidadeRegistros_binario(FILE *file)
{
    if(file == NULL) return -1;

    int quantidade;

    fseek(file, N_REG_INSER, SEEK_SET);

    fread(&quantidade, sizeof(int), 1, file);

    return quantidade;
}

int getQuantidadeRegistrosTotal_binario(FILE *file)
{
    if(file == NULL) return -1;

    int quantidade;

    fseek(file, N_PROX_REG, SEEK_SET);

    fread(&quantidade, sizeof(int), 1, file);

    return quantidade;
}

/*
    Insere os dados de um REGISTRO* na ultima posicao do arquivo binario
    e atualiza o cabecalho do arquivo com as inforacoes necessarias

    Parametros:
    [in] FILE* file
    [in] REGISTRO* reg
*/
void insere_binario(FILE *file, REGISTRO *reg)
{
    if(file == NULL) return;
    if(!verificaIntegridade_binario(file)) return;
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

    
    fwrite(&sexoBebe, sizeof(char), 1, file);

    if(strlen(estadoMae) > 0)
        fwrite(estadoMae, 2 * sizeof(char), 1, file);
    else file = escreveLixoEstatico(file, 2);

    if(strlen(estadoBebe) > 0)
        fwrite(estadoBebe, 2 * sizeof(char), 1, file);
    else file = escreveLixoEstatico(file, 2);

    atualizaProxReg(file);
    atualizaNReg(file, '1');
    return;
}

/*
    Verifica a integridade de um arquivo binario atraves do seu primeiro byte

    Parametros:
    [in] FILE* file

    Retorno:
    int: 0 se os dados não forem integros
    int: 1 se os dados forem integros.
*/
int verificaIntegridade_binario(FILE* file)
{
    if(file == NULL) return 0;
    char ret;

    fseek(file, 0, SEEK_SET);
    fread(&ret,sizeof(char),1,file);
    return (int)ret - '0';
}

