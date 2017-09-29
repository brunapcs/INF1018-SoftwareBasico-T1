#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gravacomp.h"

/*char defineTamanho(char* descritor){
	char tamanho = 0;
	for (int i=0; descritor[i] != '\0'; i++){
		if (descritor[i] == 'c'){
			int aux = descritor[i+1] * 10 + descritor[i+2];
			i = i + 3;
			tamanho += sizeof(char) * aux;
		}
		else
			tamanho += sizeof(int);
	}
	return tamanho;
}*/

unsigned char cabecalho (char *descritor){
	unsigned char c = 0x00; 						// inicializando byte de cabecalho
	unsigned char d = *descritor;					// pegando o primeiro elemento (byte) da string descritor
	//descritor++; 									// descritor aponta para proximo elemento (+1 byte)
	
    if(*descritor == '\0' ){ 						// se esse for o último campo do descritor, o 1 bit é ligado
        c |= 0x01;									// joga bit 1 para o indice 6.
		c = c << 7;									// c = 1000 0000. 
    }
   	
    if (d != 's'){
        if (d == 'i')								// adicionar o bit de tipo 1 no indice 6
        	c |= 0x20; 								// 0x20 = 0[01]0 0000
        	
        descritor++;								// vai para o proximo elemento do descritor
        if (*descritor == '\0' ){ 					// se esse for o último campo do descritor, o 1 bit é ligado
			c |= 0x80;								// c = 1000 0000. 
	  	}
	  	
	  	/* INSERIR FUNÇÃO PARA CALC TAMANHO */	
    }
    
    else {														// se for string
		c |= 0x40; 												// 0[1]00 0000
    	unsigned char aux = descritor[0] * 10 + descritor[1]; 	// pega o tamanho da string
    	c |= aux;    	
    }	
    
	return c;
}


int gravacomp (int nstructs, void *valores, char* descritor, FILE* arq){

    /*unsigned char nstructs_c = nstructs 			// convertendo para um unsigned char
    fwrite(&nstructs_c, sizeof(char), 1, arq); 		// Primeiro byte do arquivo.
    */
    return 1;
}




//void mostracomp (FILE* arquivo);


