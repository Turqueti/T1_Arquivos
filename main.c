
/*
NOMES: vitor turqueti / Guilherme Holanda Sanches
#USP: 10844313 / 10734370
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tad_Registro.h"
#include "csv2Reg.h"
#include "binario.h"
#include "binarioNaTela.h"
#include "command.h"


void csvHandler(char* entrada, char* saida){
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    size_t read;

    fp = fopen(entrada,"r");
    
    if(fp == NULL){
        printf("arquivo csv invalido");
        return;
    }

    read = getline(&line, &len, fp); //read para tirar o cabecalho

    REGISTRO* regTemp;

    FILE *binario;
    binario = cria_binario(saida);

    while ((read = getline(&line, &len, fp)) != -1) {
        regTemp = parseLine_csv2Reg(line);

        insere_binario(binario, regTemp);
        
        free_Registro(regTemp);
    }

    binario = fecha_binario(binario);

    fclose(fp);
    
    if (line != NULL)
        free(line);

    return;

}

void completaRegistro_Pesquisa(char** argumentos, REGISTRO* reg_pesquisa)
{
    char* teste = argumentos[3];
    printf("\n argumentos: %s", argumentos[2]);
    for (int i = 1; i <= atoi(argumentos[2]); i++)
        {
            if(strcmp(argumentos[i+2], "idadeMae") == 0)
                setIdadeMae_Registro(reg_pesquisa, atoi(argumentos[i+3]));

            if(strcmp(argumentos[i+2], "dataNascimento") == 0)
                setDataNascimento_Registro(reg_pesquisa, argumentos[i+3]);
            
            if(strcmp(argumentos[i+2], "sexoBebe") == 0)
                setSexoBebe_Registro(reg_pesquisa, *argumentos[i+3]);

            if(strcmp(argumentos[i+2], "estadoMae") == 0)
                setEstadoMae_Registro(reg_pesquisa, argumentos[i+3]);

            if(strcmp(argumentos[i+2], "estadoBebe") == 0)
                setEstadoBebe_Registro(reg_pesquisa, argumentos[i+3]);
            
            if(strcmp(argumentos[i+2], "cidadeMae") == 0)
                setCidadeMae_Registro(reg_pesquisa, argumentos[i+3]);

            if(strcmp(argumentos[i+2], "cidadeBebe") == 0)
                setCidadeBebe_Registro(reg_pesquisa, argumentos[i+3]);
        }
}

void completaRegistro_Remocao(char** argumentos, REGISTRO* reg_pesquisa)
{
    for (int i = 1; i <= 2 * atoi(argumentos[0]); i+= 2)
        {
            if(strcmp(argumentos[i], "idadeMae") == 0)
                setIdadeMae_Registro(reg_pesquisa, atoi(argumentos[i+1]));

            if(strcmp(argumentos[i], "dataNascimento") == 0)
                setDataNascimento_Registro(reg_pesquisa, argumentos[i+1]);
            
            if(strcmp(argumentos[i], "sexoBebe") == 0)
                setSexoBebe_Registro(reg_pesquisa, *argumentos[i+1]);

            if(strcmp(argumentos[i], "estadoMae") == 0)
                setEstadoMae_Registro(reg_pesquisa, argumentos[i+1]);

            if(strcmp(argumentos[i], "estadoBebe") == 0)
                setEstadoBebe_Registro(reg_pesquisa, argumentos[i+1]);
            
            if(strcmp(argumentos[i], "cidadeMae") == 0)
                setCidadeMae_Registro(reg_pesquisa, argumentos[i+1]);

            if(strcmp(argumentos[i], "cidadeBebe") == 0)
                setCidadeBebe_Registro(reg_pesquisa, argumentos[i+1]);
        }
}

void formatPrintFunc2(REGISTRO* reg){
    char SexoBebeREG = getSexoBebe_Registro(reg);
    char sexoBebeFormatado[10];

    if (SexoBebeREG == '0')
    {
        strcpy(sexoBebeFormatado,"IGNORADO");
    }else if (SexoBebeREG == '1')
    {
        strcpy(sexoBebeFormatado,"MASCULINO");
    }else if (SexoBebeREG == '2')
    {
        strcpy(sexoBebeFormatado,"FEMININO");
    }
    
    
    
    char* dataNascREG = getDataNascimento_Registro(reg);
    char dataNascFormat[10];

    if (strcmp(dataNascREG,""))
    {
        strncpy(dataNascFormat,dataNascREG,10);
        // dataNascFormat[11] = '\0';
    }else
    {
        // strcpy(dataNascFormat,"-");
        dataNascFormat[0] = '-';
        dataNascFormat[1] = '\0';      
    }
    
    char* estadoBebeREG = getEstadoBebe_Registro(reg);
    char estadoBebeFormat[3] = {'\0','\0','\0'};

    if (!strcmp(estadoBebeREG,""))
    {
        strcpy(estadoBebeFormat,"-");
    }else
    {
        strcpy(estadoBebeFormat,estadoBebeREG);
    }
    
    char* cidadeBebeREG = getCidadeBebe_Registro(reg);
    char* cidadeBebeFormat = NULL;

    if (cidadeBebeREG == NULL)
    {
        cidadeBebeFormat = "-";
        // strcpy(cidadeBebeFormat,"-");
    }else
    {
        cidadeBebeFormat = cidadeBebeREG;
        // strcpy(cidadeBebeFormat,cidadeBebeREG);
    }
    
    

    //Nasceu em BAGRE/PA, em 2016-01-01, um bebê de sexo MASCULINO.

    printf("Nasceu em %s/%.*s, em %.*s, um bebê de sexo %s.\n",cidadeBebeFormat,2,estadoBebeFormat,10,dataNascFormat,sexoBebeFormatado);
    return;
}

void funcionalidade2(char* binFile){
    REGISTRO* regtemp;
    FILE* binario;
    int qntdRegistros;

    binario = abreLeitura_Binario(binFile);
    if (verificaIntegridade_binario(binario))
    {
        fseek(binario,5,SEEK_SET);
        fread(&qntdRegistros,sizeof(int),1,binario);
        for (int i = 1; i <= qntdRegistros; i++)
        {
            regtemp = getRegistro_Binario(binario,i);
            //
            // print_Registro(regtemp);
            formatPrintFunc2(regtemp);
            free_Registro(regtemp);
        }
        fecha_binario(binario);
    }else
    {
        printf("Falha no processamento do arquivo.");
    }
    return;
}

void funcionalidade3(char** argumentos)
{
    REGISTRO *reg_pesquisa = NULL;
    REGISTRO *reg_atual = NULL;
    FILE* binario = NULL;
    int qntdRegistros, flagEncontrado = 0;

    binario = abreLeitura_Binario(argumentos[1]);
    reg_pesquisa = cria_Registro();

    if(verificaIntegridade_binario(binario))
    {

        for (int i = 3; i <= atoi(argumentos[2]); i=i+2)
        {
            // printf("argumentos[%d]: %s\n",i,argumentos[i]);
            if(strcmp(argumentos[i], "idadeMae"))
                setIdadeMae_Registro(reg_pesquisa, atoi(argumentos[i+1]));
            
            else if(strcmp(argumentos[i], "dataNascimento"))
                setDataNascimento_Registro(reg_pesquisa, argumentos[i+1]);
            
            else if(strcmp(argumentos[i], "sexoBebe"))
                setSexoBebe_Registro(reg_pesquisa, *argumentos[i+1]);

            else if(strcmp(argumentos[i], "estadoMae"))
                setEstadoMae_Registro(reg_pesquisa, argumentos[i+1]);

            else if(strcmp(argumentos[i], "estadoBebe"))
                setEstadoBebe_Registro(reg_pesquisa, argumentos[i+1]);
            
            else if(strcmp(argumentos[i], "cidadeMae"))
                setCidadeMae_Registro(reg_pesquisa, argumentos[i+1]);

            else if(strcmp(argumentos[i], "cidadeBebe"))
                setCidadeBebe_Registro(reg_pesquisa, argumentos[i+1]);
        }

        for(int i = 1; i <= getQuantidadeRegistros_binario(binario); i++)
        {
            reg_atual = getRegistro_Binario(binario,i);

            if(verificaSemelhanca_Registro(reg_pesquisa, reg_atual)!= NULL)
            {
                formatPrintFunc2(reg_atual);
                flagEncontrado = 1;
            }
        }

        if(!flagEncontrado) printf("Registro Inexistente.");


        if (binario)
            fecha_binario(binario);
        if (reg_atual)
            free_Registro(reg_atual);
        if (reg_pesquisa)
            free_Registro(reg_pesquisa);        
    }
    else
    {
        printf("Falha no processamento do arquivo.");
    }
    return;
}

void funcionalidade4(char* binFile, int RNN)
{
    FILE* file;
    REGISTRO* reg;
    file = abreLeitura_Binario(binFile);

    if(verificaIntegridade_binario(file))
    {
        reg = getRegistro_Binario(file, RNN);

        if(reg != NULL)
            formatPrintFunc2(reg);
        else 
            printf("Registro inexistente.");

        fecha_binario(file);
        free_Registro(reg);
    }
    else
    {
        printf("Falha no processamento do arquivo.");
    }
    return;
}

char** lineToArgs_5()
{
    char* linha = NULL;
    size_t size;
    // __ssize_t read;
    getline(&linha, &size, stdin);

    int numArgs = 0;
    char** argumentos = commandIntoArgs(linha,&numArgs);

    free(linha);
     return argumentos;
}

void funcionalidade5(char* nomeArq,int nRemocoes)
{
    REGISTRO *reg_pesquisa, *reg_atual;
    FILE* binario;

    binario = abreEscrita_Binario(nomeArq);

    if(verificaIntegridade_binario(binario))
    {
        for (int i = 0; i < nRemocoes; i++)
        {
            reg_pesquisa = cria_Registro();

            char** argumentos = lineToArgs_5(); //desalocar depois

            completaRegistro_Remocao(argumentos, reg_pesquisa);

            for(int i = 1; i <= getQuantidadeRegistros_binario(binario); i++)
            {
                reg_atual = getRegistro_Binario(binario,i);

                if(verificaSemelhanca_Registro(reg_pesquisa, reg_atual)!= NULL)
                {
                    excluiRegistro_binario(binario, i);
                }
                free_Registro(reg_atual);
            }

            free_Registro(reg_pesquisa);
            free(argumentos);
        }

        binarioNaTela(nomeArq);
        fecha_binario(binario);
    }
    else
    {
        printf("Falha no processamento do arquivo.");
    }
    return;   
}

void menu(){
    char* command = NULL;
    size_t size;
    // __ssize_t read;
    getline(&command, &size, stdin);

    int numArgs = 0;
    char** argumentos = commandIntoArgs(command,&numArgs);

    
    if(!strcmp(argumentos[0],"0")){
    }
    if(!strcmp(argumentos[0],"1")){
        csvHandler(argumentos[1], argumentos[2]);
        binarioNaTela(argumentos[2]);
    }
    if(!strcmp(argumentos[0],"2")){
        funcionalidade2(argumentos[1]);
    }

    if(!strcmp(argumentos[0],"3")){
        funcionalidade3(argumentos);
    }

    if(!strcmp(argumentos[0],"4")){
        funcionalidade4(argumentos[1], atoi(argumentos[2]));
    }

    if(!strcmp(argumentos[0],"5")){
        funcionalidade5(argumentos[1], atoi(argumentos[2]));
    }

    if (command)
    {
        free(command);
    }
    if (argumentos)
    {
        free(argumentos);
    }
}

int main(int argc, char const *argv[])
{
    menu();
    return 0;
}