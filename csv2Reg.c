#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "csv2Reg.h"



char* strtok_new(char * string, char const * delimitador){
    static char* source = NULL;
    char* p;
    char* ret = 0;
    
    if(string != NULL){
        source = string;
    }
        
    if(source == NULL){
        return NULL;
    }

    if((p = strpbrk (source, delimitador)) != NULL) {
        *p  = 0;
        ret = source;
        source = ++p;
    }
    return ret;
}

REGISTRO* parseLine_csv2Reg(char* linha){
    REGISTRO* reg;
    reg = cria_Registro();
    char* tempVet[8];
    char* token;
    char delimitador[] = ",\n";

    token = strtok_new(linha,delimitador);
    
    for (int i = 0; i < 8; i++)
    {
        if (*token)
        {
            tempVet[i] = token;
            
        }else
        {
            tempVet[i] = "-";
        }
        //printf("tempvet[%d]: %s\n",i,tempVet[i]);
        token = strtok_new(NULL, delimitador);
    }
    
    //cidadeMae,cidadeBebe,idNascimento,idadeMae,dataNascimento,sexoBebe,estadoMae,estadoBebe
    if (strcmp(tempVet[0],"-"))
    {
        setCidadeMae_Registro(reg,tempVet[0]);
    }
    if (strcmp(tempVet[1],"-"))
    {
        setCidadeBebe_Registro(reg,tempVet[1]);
    }
    if (strcmp(tempVet[2],"-"))
    {
        setIdNascimento_Registro(reg,atoi(tempVet[2]));
    }
    if (strcmp(tempVet[3],"-"))
    {
        setIdadeMae_Registro(reg,atoi(tempVet[3]));
    }
    if (strcmp(tempVet[4],"-"))
    {
        setDataNascimento_Registro(reg,tempVet[4]);
    }
    if (strcmp(tempVet[5],"-"))
    {
        setSexoBebe_Registro(reg,tempVet[5][0]);
    }
    if (strcmp(tempVet[6],"-"))
    {
        setEstadoMae_Registro(reg,tempVet[6]);
    }
    if (strcmp(tempVet[7],"-"))
    {
        setEstadoBebe_Registro(reg,tempVet[7]);
    }
    
    return reg;

}
