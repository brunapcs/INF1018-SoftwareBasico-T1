#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gravacomp.h"


int main(){
    
    int nstructs=2;
    char descritor[6] = "is07u";
    Estrutura valores[2];
    
    valores[0].i = -127;
    strcpy(valores[0].s, "Oi ir");
    valores[0].u = 255;
    
    valores[1].i = 250;
    strcpy(valores[1].s, "0123");
    valores[1].u = 1232436;
    
    /***** [INÍCIO] Abertura do Arquivo Para Gravacao *****/
    
    FILE *file = fopen ("arquivo.txt", "wb");
    if (file == NULL){
        printf("Problemas na abertura do arquivo\n");
        exit(1);
    }
    
    /***** [FIM] Abertura do Arquivo *****/
    
    
    gravacomp(nstructs, valores, descritor, file); 
        
    fclose (file);
    
    
    /***** [INÍCIO] Abertura do Arquivo Para Leitura *****/
    
    file = fopen ("arquivo.txt", "rb");
    if (file == NULL){
        printf("Problemas na abertura do arquivo\n");
        exit(1);
    }
    
    /***** [FIM] Abertura do Arquivo *****/
    
    mostracomp(file);
    
    fclose (file);
    
    
    
    
    return 0;
} 
