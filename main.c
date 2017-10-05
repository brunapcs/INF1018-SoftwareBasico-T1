#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gravacomp.h"


int main(){
    
    int nstructs=2;
    char descritor[6] = "is07u";
    Estrutura est[2];
    
    est[0].i = 130;
    strcpy(est[0].s, "Oi ir");
    est[0].u = 255;
    
    est[1].i = 250;
    strcpy(est[1].s, "0123");
    est[1].u = 1232436;
    
    
    //printf("Oi");
    /***** [INÍCIO] Abertura do Arquivo Para Gravacao *****/
    
    FILE *file = fopen ("arquivo.txt", "wb");
    if (file == NULL){
        printf("Problemas na abertura do arquivo\n");
        exit(1);
    }
    
    /***** [FIM] Abertura do Arquivo *****/
    
    gravacomp(nstructs, est, descritor, file);     
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
