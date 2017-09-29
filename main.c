#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gravacomp.h"

int main(){

	//int num=2, i=0; //numero de arrays da estrutura
    char desc[4] = "ii";
    unsigned char cab;

    /***** [INÍCIO] Abertura do Arquivo *****/
        
	FILE *file = fopen ("arquivo.txt", "wb");
	if (file == NULL){
        printf("Problemas na abertura do arquivo\n");
        exit(1);
  	}  	
  	
  	cab = cabecalho(desc);
  	fwrite (&cab, sizeof(char), 1, file);
    
    /***** [FIM] Abertura do Arquivo *****/

   
   
	fclose (file);
	return 0;
} 
