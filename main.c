#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tad_Registro.h"
#include "csv2Reg.h"


void csvHandler(char* fileName){
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(fileName,"r");
    
    if(fp == NULL){
        printf("arquivo csv invalido");
        return;
    }

    read = getline(&line, &len, fp); //read para tirar o cabecalho

    REGISTRO* regTemp;


    while ((read = getline(&line, &len, fp)) != -1) {
        regTemp = parseLine_csv2Reg(line);
        print_Registro(regTemp);
        //funcs que colocam o registro no binario
        free_Registro(regTemp);
    }

    fclose(fp);
    
    if (line)
        free(line);
    
    

}

int main(int argc, char const *argv[])
{

    // REGISTRO* reg;
    // char csvLine[] = "CACHOEIRA DO SUL,CACHOEIRA DO SUL,1,33,2016-01-01,2,RS,RS\n";
    // reg = parseLine_csv2Reg(csvLine);

    // print_Registro(reg);
    // printf("cidade mae: %s",getCidadeMae_Registro(reg));

    // free_Registro(reg);

    char FileName[] = "test.csv";

    csvHandler(FileName);

    return 0;
}
