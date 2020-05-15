#ifndef COMMAND_H
#define COMMAND_H


int countArgs(char* line);
char** commandIntoArgs(char* command, int* numArgs);

#endif
