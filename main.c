#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tad_Registro.h"
#include "csv2Reg.h"
#include "binario.h"


void csvHandler(char* fileName){
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    size_t read;

    fp = fopen(fileName,"r");
    
    if(fp == NULL){
        printf("arquivo csv invalido");
        return;
    }

    read = getline(&line, &len, fp); //read para tirar o cabecalho

    REGISTRO* regTemp;


    while ((read = getline(&line, &len, fp)) != -1) {
        regTemp = parseLine_csv2Reg(line);
        //print_Registro(regTemp);
        //funcs que colocam o registro no binario
        free_Registro(regTemp);
    }

    fclose(fp);
    
    if (line)
        free(line);
    
    

}

int main(int argc, char const *argv[])
{

    REGISTRO *reg, *teste;
    char csvLine[] = "CACHOEIRA DO SUllL,CACHOEIRA DO SUL,1,33,,2,RS,RS\n";
    reg = parseLine_csv2Reg(csvLine);

    FILE *binario;
    binario = cria_binario("agoravai.bin");
    insere_binario(binario, reg);
    binario = fecha_binario(binario);
    binario = abreLeitura_Binario("agoravai.bin");
    teste = getRegistro_Binario(binario, 1);

    print_Registro(teste);
    // print_Registro(reg);
    // printf("cidade mae: %s",getCidadeMae_Registro(reg));

    // free_Registro(reg);

    char FileName[] = "test.csv";

    csvHandler(FileName);

    return 0;
}
