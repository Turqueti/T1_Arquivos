#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tad_Registro.h"


struct _registro
{
    int idNascimento;
    int idadeMae;
    char dataNascimento[10];
    char sexoBebe;
    char estadoMae[2];
    char estadoBebe[2];

    char* cidadeMae;
    char* cidadeBebe;
};



/*
    Alloca o registro na memoria e seta os valores iniciais como:
    -1 caso seja inteiro
    '\0' na primeira posicao de um vetor de char ou em um char
    NULL nos ponteiros para char

    Retorno:
    REGISTRO*: ponteiro para struct do tipo registro

*/
REGISTRO* cria_Registro(){
    REGISTRO* reg;
    reg = (REGISTRO*)malloc(sizeof(REGISTRO));
    if (reg == NULL)
    {
        printf("ERRO ao alocar registro");
        return NULL;
    }
    

    reg->idNascimento = -1;
    reg->idadeMae = -1;
    reg->dataNascimento[0]= '\0';
    reg->sexoBebe = '0';
    reg->estadoMae[0] = '\0';
    reg->estadoBebe[0] = '\0';
    reg->cidadeMae = NULL;
    reg->cidadeBebe = NULL;

    return reg;

}


/*
    Verifica se dois registros têm os valores validos(not dafault) iguais:

    Retorno:
    REGISTRO*: ponteiro para registro semelhante (reg atual);

*/

REGISTRO* verificaSemelhanca_Registro(REGISTRO* reg_pesquisa, REGISTRO* reg_atual)
{
    if(reg_atual == NULL) return NULL;
    
    if(reg_pesquisa->idadeMae != -1)
        if(reg_pesquisa->idadeMae != reg_atual->idadeMae) return NULL;

    if(reg_pesquisa->dataNascimento[0] != '\0')
        if(strcmp(reg_pesquisa->dataNascimento, reg_atual->dataNascimento) != 0) return NULL;

    if(reg_pesquisa->idadeMae != reg_atual->idadeMae) return NULL;


    if(reg_pesquisa->estadoBebe[0] != '\0')
        if(strcmp(reg_pesquisa->estadoBebe, reg_atual->estadoBebe) != 0) return NULL;

    if(reg_pesquisa->estadoMae[0] != '\0')
        if(strcmp(reg_pesquisa->estadoMae, reg_atual->estadoMae) != 0) return NULL;

    if(reg_pesquisa->cidadeMae != NULL)
        if(strcmp(reg_pesquisa->cidadeMae, reg_atual->cidadeMae) != 0) return NULL;

    if(reg_pesquisa->cidadeBebe != NULL)
        if(strcmp(reg_pesquisa->cidadeBebe, reg_atual->cidadeBebe) != 0) return NULL;

    return reg_atual;
}


/*
    Desaloca um ponteiro para Registro(reg) e todas as strings dentro dele

    Parametros:
    [in] REGISTRO* reg
*/
void free_Registro(REGISTRO* reg){
    if (reg == NULL)
    {
        return;
    }

    free(reg->cidadeMae);
    free(reg->cidadeBebe);
    free(reg);
    
}

//--------------------------------------GETERS------------------------------------------------------

/* 
    Retorna o atributo IdNascimento de um ponteiro para registro reg

    Parametros:
    [in]REGISTRO* reg

    Retorno:
    int IdNascimento
*/
int getIdNascimento_Registro(REGISTRO* reg){
    return reg->idNascimento;
}

/* 
    Retorna o atributo IdadeMae de um ponteiro para registro reg

    Parametros:
    [in]REGISTRO* reg

    Retorno:
    int IdadeMae
*/
int getIdadeMae_Registro(REGISTRO* reg){
    return reg->idadeMae;
}

/* 
    Retorna o atributo SexoBebe de um ponteiro para registro reg

    Parametros:
    [in]REGISTRO* reg

    Retorno:
    int SexoBebe
*/
int getSexoBebe_Registro(REGISTRO* reg){
    return reg->sexoBebe;
}

/* 
    Retorna o atributo DataNascimento de um ponteiro para registro reg

    Parametros:
    [in]REGISTRO* reg
    [out]char retorno[10]

*/
char* getDataNascimento_Registro(REGISTRO* reg){
    return reg->dataNascimento;
}

/* 
    Retorna o atributo EstadoMae de um ponteiro para registro reg

    Parametros:
    [in]REGISTRO* reg
    [out]char retorno[2]

*/
char* getEstadoMae_Registro(REGISTRO* reg){
    return reg->estadoMae;
}

/* 
    Retorna o atributo EstadoBebe de um ponteiro para registro reg

    Parametros:
    [in]REGISTRO* reg
    [out]char retorno[2]

*/
char* getEstadoBebe_Registro(REGISTRO* reg){
    return reg->estadoBebe;
}

/* 
    Retorna o atributo CidadeMae de um ponteiro para registro reg

    Parametros:
    [in]REGISTRO* reg

    Retorno:
    char* CidadeMae
*/
char* getCidadeMae_Registro(REGISTRO* reg){
    return reg->cidadeMae;
}

/* 
    Retorna o atributo CidadeBebe de um ponteiro para registro reg

    Parametros:
    [in]REGISTRO* reg

    Retorno:
    char* CidadeBebe
*/
char* getCidadeBebe_Registro(REGISTRO* reg){
    return reg->cidadeBebe;
}

//--------------------------------------SETERS------------------------------------------------------

/* 
    atribui o atributo IdNascimento de um ponteiro para registro reg

    Parametros:
    [in]REGISTRO* reg
    [in]int idNascimento
*/
void setIdNascimento_Registro(REGISTRO* reg, int idNascimento){
    reg->idNascimento = idNascimento;
}

/* 
    atribui o atributo IdadeMae de um ponteiro para registro reg

    Parametros:
    [in]REGISTRO* reg
    [in]int IdadeMae
*/
void setIdadeMae_Registro(REGISTRO* reg, int idadeMae){
    reg->idadeMae = idadeMae;
}

/* 
    atribui o atributo SexoBebe de um ponteiro para registro reg

    Parametros:
    [in]REGISTRO* reg
    [in]int SexoBebe
*/
void setSexoBebe_Registro(REGISTRO* reg, char sexoBebe){
    reg->sexoBebe = sexoBebe;
}

/* 
    atribui o atributo DataNascimento de um ponteiro para registro reg

    Parametros:
    [in]REGISTRO* reg
    [in]char DataNascimento[10]
*/
void setDataNascimento_Registro(REGISTRO* reg, char dataNascimento[10]){
    
    for (int i = 0; i < 10; i++)
    {
        reg->dataNascimento[i] = dataNascimento[i];
    }
    
}

/* 
    atribui o atributo estadoMae de um ponteiro para registro reg

    Parametros:
    [in]REGISTRO* reg
    [in]char estadoMae[2]
*/
void setEstadoMae_Registro(REGISTRO* reg, char estadoMae[2]){
    
    for (int i = 0; i < 2; i++)
    {
        reg->estadoMae[i] = estadoMae[i];
    }
    
}

/* 
    atribui o atributo estadoBebe de um ponteiro para registro reg

    Parametros:
    [in]REGISTRO* reg
    [in]char estadoBebe[2]
*/
void setEstadoBebe_Registro(REGISTRO* reg, char estadoBebe[2]){
    
    for (int i = 0; i < 2; i++)
    {
        reg->estadoBebe[i] = estadoBebe[i];
    }
    
}

/* 
    atribui o atributo cidadeBebe de um ponteiro para registro reg

    Parametros:
    [in]REGISTRO* reg
    [in]char* cidadeBebe
*/
void setCidadeBebe_Registro(REGISTRO* reg, char* cidadeBebe){

    if(reg->cidadeBebe != NULL){
        free(reg->cidadeBebe);
    }
    int tam = strlen(cidadeBebe);
    char* temp = (char*)malloc((sizeof(char)*tam)+1);
    strcpy(temp,cidadeBebe);
    reg->cidadeBebe = temp;

}

/* 
    atribui o atributo cidadeMae de um ponteiro para registro reg

    Parametros:
    [in]REGISTRO* reg
    [in]char* cidadeMae
*/
void setCidadeMae_Registro(REGISTRO* reg, char* cidadeMae){

    if(reg->cidadeMae != NULL){
        free(reg->cidadeMae);
    }
    int tam = strlen(cidadeMae);
    char* temp = (char*)malloc((sizeof(char)*tam)+1);
    strcpy(temp,cidadeMae);
    reg->cidadeMae = temp;

}

//--------------------------------------AUX/DEBUG------------------------------------------------------

/*
    printa um registro

    parametros:
    [in]Registro* reg
*/
void print_Registro(REGISTRO* reg){
    // printf("----------------------------------------------------------------------------\n");
    printf("idNascimento: %d\n",reg->idNascimento);
    printf("idadeMae: %d\n",reg->idadeMae);
    printf("DataNascimento %.*s\n",10,reg->dataNascimento);
    printf("sexoBebe: %c\n",reg->sexoBebe);
    printf("EstadoMae: %.*s\n",2,reg->estadoMae);
    printf("EstadoBebe: %.*s\n",2,reg->estadoBebe);
    printf("cidadeMae: %s\n",reg->cidadeMae);
    printf("cidadeBebe: %s\n",reg->cidadeBebe);
}