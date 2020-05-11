#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tad_Registro.h"
#include "csv2Reg.h"
#include "binario.h"
#include "binarioNaTela.h"


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

void parse_command(char argumentos[3][30],int numArgumentos){
    char command[30];
    fgets(command,90,stdin);
    int i = 0;
    char delim[] = " \n";
    char* temp;


    temp = strtok(command,delim);
    while(temp != NULL){
        strcpy(argumentos[i],temp);
        temp = strtok(NULL,delim);
        i++;
    }
    numArgumentos = i + 1;

}

void funcionalidade2(char* binFile){
    REGISTRO* regtemp;
    FILE* binario;
    int qntdRegistros;

    binario = abreLeitura_Binario("agoravai.bin");
    if (binario != NULL)
    {
        fseek(binario,5,SEEK_SET);
        fread(&qntdRegistros,sizeof(int),1,binario);
        for (int i = 1; i <= qntdRegistros; i++)
        {
            regtemp = getRegistro_Binario(binario,i);
            print_Registro(regtemp);
        }
    }
}

void menu(){
    char argumentos[3][30];
    int numArgs = 0;
    
    parse_command(argumentos,numArgs);
    if(!strcmp(argumentos[0],"0")){
        printf("corno\n");
    }
    if(!strcmp(argumentos[0],"1")){
        csvHandler(argumentos[1], argumentos[2]);
        binarioNaTela(argumentos[2]);
    }
    if(!strcmp(argumentos[0],"2")){
        funcionalidade2(argumentos[1]);
    }
}

int main(int argc, char const *argv[])
{
    //csvHandler("test.csv");

    menu();
    //funcionalidade2("agoravai.bin");
    return 0;
}