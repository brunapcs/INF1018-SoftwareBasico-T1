#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gravacomp.h"

int main(){

	//int num=2, i=0; //numero de arrays da estrutura
    char desc[4] = "s03";
    unsigned char cab;

    /***** [INÍCIO] Abertura do Arquivo *****/
        
	FILE *arq = fopen ("Arquivo.txt", "wb");
	if (arq == NULL){
        printf("Problemas na abertura do arquivo\n");
        exit(1);
  	}
  	
  	
  	cab = cabecalho(desc);
  	
  	fwrite (&cab, sizeof(char), 1, arq);
    
    /***** [FIM] Abertura do Arquivo *****/

   
   
	fclose (arq);
	return 0;
} 
