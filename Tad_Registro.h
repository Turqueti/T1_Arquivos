#ifndef TAD_REGISTRO_H
#define TAD_REGISTRO_H

typedef struct _registro REGISTRO;

REGISTRO* cria_Registro();
void free_Registro(REGISTRO* reg);
int getIdNascimento_Registro(REGISTRO* reg);
int getIdadeMae_Registro(REGISTRO* reg);
int getSexoBebe_Registro(REGISTRO* reg);
char* getDataNascimento_Registro(REGISTRO* reg);
char* getEstadoMae_Registro(REGISTRO* reg);
char* getEstadoBebe_Registro(REGISTRO* reg);
char* getCidadeMae_Registro(REGISTRO* reg);
char* getCidadeBebe_Registro(REGISTRO* reg);
void setIdNascimento_Registro(REGISTRO* reg, int idNascimento);
void setIdadeMae_Registro(REGISTRO* reg, int idadeMae);
void setSexoBebe_Registro(REGISTRO* reg, char sexoBebe);
void setDataNascimento_Registro(REGISTRO* reg, char dataNascimento[10]);
void setEstadoMae_Registro(REGISTRO* reg, char estadoMae[2]);
void setEstadoBebe_Registro(REGISTRO* reg, char estadoBebe[2]);
void setCidadeBebe_Registro(REGISTRO* reg, char* cidadeBebe);
void setCidadeMae_Registro(REGISTRO* reg, char* cidadeMae);
void print_Registro(REGISTRO* reg);

#endif
