#include <stdlib.h>
#include <string.h>

/*
    conta o nummero de argumentos em uma linha finalizada com '/n'

    argumentos:
    [in] char* line

    retorno:
    int numArgs

*/
int countArgs(char* line){
    int i = 0;
    char* scroll = line;

    while ((scroll = strpbrk(scroll," \n")))
    {
        i++;
        scroll++;
    }
    return i;
}

/*
    tokeniza um comando(char*) com base nos espacos e '\n' 
    e retorna um char** com os argumentos em forma de "vetor de tokens" e o numero de argumentos, 
    caso falha retorna NULL,
    nao se pode desalocar o  argumento command da memoria
    e necessario desalocar o ponteiro retornado

    argumentos:
    [in] char* command
    [out] int numArgs


    retorno:
    char** argumentos


*/
char** commandIntoArgs(char* command, int* numArgs){
    
    if (command == NULL)
    {
        return NULL;
    }
    
    *numArgs = countArgs(command);
    char** args = (char**)malloc(sizeof(char*)*(*numArgs));
    if (args == NULL)
    {
        return NULL;
    }
    


    char delim[] = " \n";
    char* temp;


    int i = 0; 
    temp = strtok(command,delim);
    while(temp != NULL){
        args[i] = temp;
        temp = strtok(NULL,delim);
        i++;
    }
    
    return args;

}
