#include <stdio.h>

typedef struct s {
	int i;
	char s[7];
	unsigned int u;
} Estrutura;


int gravacomp (int nstructs, void* valores, char* descritor, FILE* arquivo);
//int cabecalho (int nstructs, void* valores, char* descritor, FILE* arquivo);

//void mostracomp (FILE* arquivo);

