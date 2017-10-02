#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gravacomp.h"

/* [INÍCIO] FUNÇÕES STATIC ( AUXILIARES ) */

/*static char defineTamanho(char* descritor){						// funcao para calcular o tamanho de uma struct
	char tamanho = 0;											// NÃO DEVE SER ÚTIL
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

static int int_pow(int base, int exp) 							// função para cálculo de potência com int
{
    int result = 1;
    while (exp)
    {
        if (exp & 1)
           result *= base;
        exp /= 2;
        base *= base;
    }
    return result;
}

static char contaBytesUnsigned(unsigned int x){					// função auxiliar para calculo do numero de bytes para uint
	char bytes = 4;
	
	for(int i = 3; i > 0; i--){									// se x = 0, o numero de bytes é 1 de qqr jeito
		if (x <= (unsigned int) (int_pow(2, 8*i) - 1))			// verifica se esta no range x <= 2^(8*n)-1
			(bytes)--;
		else
			i = 0;
	}
	return bytes;
}

static char contaBytesSigned(int x){							// função auxiliar para calculo do numero de bytes para int
	char bytes = 4;
	
	for(int i = 3; i > 0; i--){										 // se x = 0, o numero de bytes é 1 de qqr jeito
		if ( x >= -int_pow(2,8*i-1) && x <= (int_pow(2, 8*i-1) - 1)) //verifica se esta no range -2^(8*n-1) <=x<= 2^(8*n-1)-1
			(bytes)--;
		else
			i = 0;
	}
	return bytes;
}

/* [FIM] FUNÇÕES STATIC ( AUXILIARES ) */


unsigned char cabecalho (void* valores, char* descritor, char* bytes){
	unsigned char c = 0x00; 						// inicializando byte de cabecalho
	unsigned char d = descritor[0];					// pegando o primeiro elemento (byte) da string descritor
	
    if (d != 's'){
        if (d == 'i'){								// se for signed int
		    int *aux = valores;
		    c |= 0x20; 								// 0x20 = 0[01]0 0000
		    *bytes = contaBytesSigned(*aux);
        }

	  	else{										// se for unsigned int
	  		unsigned int* aux = valores;
	  		*bytes = contaBytesUnsigned(*aux);
	  	}
	  	c |= *bytes;								// grava o valor de bytes no cabeçalho
	  	descritor ++;
    }  
    
    else {																	// se for string
		c |= 0x40; 															// 0[1]00 0000
    	unsigned char aux = (descritor[1] - 48)*10  + (descritor[2] - 48); 	// pega o tamanho da string 
    	c |= aux;    														//(-48 pq 0 na ASCII é 48)
    	descritor +=3;														// pula 3 posicoes (proximo campo da struct)
    	
    }
    
    if (descritor[0] == '\0' ) 						// se esse for o último campo do descritor, o 7º bit é ligado
			c |= 0x80;								// c = 1000 0000.
    
	return c;
}

int gravacomp (int nstructs, void* valores, char* descritor, FILE* arq){

	unsigned char nstructs_c = nstructs; 			// convertendo para um unsigned char
    fwrite(&nstructs_c, sizeof(char), 1, arq); 		// Primeiro byte do arquivo.
    
    
    /*while (nstructs--){
    	for (int i = 0; descritor[i] != '\0'; i++){
    		char bytes;
    		cabecalho(valores,descritor,&bytes);
    		valores++;
    	}
    }*/
    
	return 1;
}




//void mostracomp (FILE* arquivo);


