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

int gravacomp (int nstructs, void* valores, char* descritor, FILE *arquivo){
	unsigned char c; 									// inicializando byte de cabecalho
	char* desc;									
	char nstructs_c = nstructs;

	
	fwrite(&nstructs_c, sizeof(char), 1, arquivo); 		// Primeiro byte do arquivo com nstructs.	
	
	while(nstructs){
		desc = descritor;									// variável auxiliar para o descritor
	
		while(desc[0] != '\0'){
			c = 0x00;										// inicializando byte de cabeçalho
			char bytes;
		
			if (desc[0] != 's'){
			
				if (desc[0] == 'i'){						// se for signed int
					int* aux = valores;						
					c |= 0x20; 								// 0x20 = 0[01]0 0000
					bytes = contaBytesSigned(*aux);
					c |= bytes;								// grava o valor de bytes no cabeçalho					 
				}
				else{										// se for unsigned int
			  		unsigned int* aux = valores;
			  		bytes = contaBytesUnsigned(*aux);
			  		c |= bytes;								// grava o valor de bytes no cabeçalho
			  	}
			  	
			  	desc ++;
				if (desc[0] == '\0')						// se esse for o último campo do descritor, o 7º bit é ligado
					c |= 0x80;								// c = 1000 0000.
				
				fwrite(&c, sizeof(char), 1, arquivo);
			
				valores = valores + (bytes - 1);			// faz valores apontar para o ultimo byte gravavel (mais signific)
				for (int i = 0; i < bytes; i++){
					fwrite(valores, sizeof(char), 1 , arquivo);	// big endian
					valores--;									//valores-- até apontar para uma pos antes do inicio
				}
				valores = valores + 4 + 1;						// valores agora aponta para o início do próximo dado.
			}  

			else{											// se for string
				char *aux = valores;
				char tamanho = 0;
				tamanho = (desc[1] - 48)*10 + desc[2] - 48; //pegando o tamanho da string (s03 dá 3 por exemplo)
				bytes = 0; 	
				c |= 0x40;									// 0[1]00 0000	
	
				while(*aux != '\0'){ 						// pega o tamanho da string 
					bytes++; 
					aux++; 
				}
	
				desc += 3;									//pula 3 posiçoes(prox campo da struct) 
	
				if (desc[0] == '\0' ) 						// se esse for o último campo do descritor, o 7º bit é ligado
					c |= 0x80;								// c = 1000 0000.
	
				c |= bytes; 
		
				fwrite(&c, sizeof(char), 1 , arquivo); 		//escreve no arquivo cabecalho
			
				for(int i = 0; i < bytes ; i ++) {
					fwrite(valores, sizeof(char), 1 , arquivo ); 	//escreve no arquivo todos os campos da string
					valores ++;
				}
			
				valores = valores - bytes;
			
				char padding;
				padding = (tamanho/4) * 4 + 4 - tamanho % 4 + 1;	// tamanho/4 dá um inteiro. é a qtd de bytes inteiros
				valores = valores + padding ;						// ocupados. vezes 4 do padding. mais 4-tamanho mod 4 p/ 
			}														// descobrir qts bytes de padding estao sozinhos. 
		}
		nstructs--;
	}
	
	return 1;
}















//int gravacomp (int nstructs, void* valores, char* descritor, FILE* arq){

    //fwrite(&nstructs_c, sizeof(char), 1, arq); 		// Primeiro byte do arquivo.
    //unsigned char *cab;
    //char bytes;
    
   	/*while (nstructs--){	
   		
   		for (int i = 0; descritor[i] != '\0'; i++){
    		cabecalho(valores, descritor, bytes);
  			
  			valores++;
  		}
  	}*/
    
    /*while (nstructs--){
    	for (int i = 0; descritor[i] != '\0'; i++){
    		char bytes;
    		cabecalho(valores,descritor,&bytes);
    		valores++;
    	}
    }*/
    
//	return 1;
//}




//void mostracomp (FILE* arquivo);


