#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gravacomp.h"

int main(){

	//int num=2, i=0; //numero de arrays da estrutura
    int nstructs=2;
    char descritor[6] = "is07u";
    Estrutura est[2];
    
    est[0].i = 0xFEEa;
    strcpy(est[0].s, "aaaa");
    est[0].u = 0x1b4;
    
    est[1].i = 250;
    strcpy(est[1].s, "0123");
    est[1].u = 1232436;
    
    

    /***** [INÍCIO] Abertura do Arquivo *****/
        
	FILE *file = fopen ("arquivo.txt", "wb");
	if (file == NULL){
        printf("Problemas na abertura do arquivo\n");
        exit(1);
  	}  	
  	
  	/***** [FIM] Abertura do Arquivo *****/
  	
  	gravacomp(nstructs, est, descritor, file);
    

   
   
	fclose (file);
	return 0;
} 
