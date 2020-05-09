#ifndef CSV2REG_H
#define CSV2REG_H
#include "Tad_Registro.h"

char* strtok_new(char * string, char const * delimitador);
REGISTRO* parseLine_csv2Reg(char* linha);

#endif
