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
    fgets(command,30,stdin);
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

    }
}


int main(int argc, char const *argv[])
{
    menu();
  
    /*REGISTRO* regTemp;

    FILE *binario;
    binario = abreLeitura_Binario("agoravai.bin");
    for (int i = 1; i < 6; i++)
    {
        regTemp = getRegistro_Binario(binario, i);
        print_Registro(regTemp);
    }*/
    return 0;
}
