#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gravacomp.h"
 
/* [INÍCIO] FUNÇÕES STATIC ( AUXILIARES ) */

static int int_pow(int base, int exp){ 						// função para cálculo de potência com int
    int result = 1;
    
    while (exp){
        if (exp & 1)
            result *= base;
        exp /= 2;
        base *= base;
    }
    
    return result;
}

static char contaBytesUnsigned(unsigned int x){	// função auxiliar para cálculo do numero de bytes para uint
    char bytes = 4;
    
    for(int i = 3; i > 0; i--){
        if (x <= (unsigned int) (int_pow(2, 8*i) - 1))			// range: x -> 2^(8*n)-1
            bytes--;
        else
            i = 0;
    }
    
    return bytes;
}

static char contaBytesSigned(int x){ // função auxiliar para cálculo do numero de bytes para int
    char bytes = 4;
    
    for(int i = 3; i > 0; i--){										 
        if (x >= -int_pow(2,8*i-1) && x <= (int_pow(2, 8*i-1) - 1)) //range: -2^(8*n-1) -> 2^(8*n-1)-1
            bytes--;
        else
            i = 0;
    }
    
    return bytes;
}

/* [FIM] FUNÇÕES STATIC ( AUXILIARES ) */

int gravacomp (int nstructs, void* valores, char* descritor, FILE *arquivo){
    char* aux_descritor;
    char nstructs_c = nstructs;
    
    fwrite(&nstructs_c, sizeof(char), 1, arquivo); 			// Primeiro byte do arquivo com nstructs.
    
    while(nstructs){
        aux_descritor = descritor;							// variável auxiliar para o descritor
        
        while(aux_descritor[0] != '\0'){
            unsigned char cabecalho = 0x00;
            char bytes;
            
            if (aux_descritor[0] != 's'){
                
                if (aux_descritor[0] == 'i'){						// se for signed int
                    int* aux = valores;
                    cabecalho |= 0x20; 								// 0x20 = 0[01]0 0000
                    bytes = contaBytesSigned(*aux);
                    cabecalho |= bytes;								// grava o valor de bytes no cabeçalho
                }
                else{										// se for unsigned int
                    unsigned int* aux = valores;
                    bytes = contaBytesUnsigned(*aux);
                    cabecalho |= bytes;								// grava o valor de bytes no cabeçalho
                }
                 
                aux_descritor ++;
                if (aux_descritor[0] == '\0')
                    cabecalho |= 0x80;								// c = 1000 0000.
                
                fwrite(&cabecalho, sizeof(char), 1, arquivo);
                valores = valores + (bytes - 1);			// faz valores apontar para o ultimo byte gravavel (mais signific)
                
                for (int i = 0; i < bytes; i++){
                    fwrite(valores, sizeof(char), 1 , arquivo);
                    valores--;									//valores-- até apontar para uma pos antes do inicio
                }
                valores = valores + 4 + 1;						// valores agora aponta para o início do próximo dado.
            }
            
            else{											// se for string
                char *aux = valores;
                char tamanho = 0;
                tamanho = (aux_descritor[1] - 48)*10 + aux_descritor[2] - 48; //pegando o tamanho da string (s03 dá 3 por exemplo)
                bytes = 0;
                cabecalho |= 0x40;									// 0[1]00 0000
                
                while(*aux != '\0'){ 						// pega o tamanho da string
                    bytes++;
                    aux++;
                }
                
                aux_descritor += 3;									//pula 3 posiçoes(prox campo da struct)
                
                if (aux_descritor[0] == '\0' ) 					
                    cabecalho |= 0x80;								// c = 1000 0000.
                
                cabecalho |= bytes; 
                
                fwrite(&cabecalho, sizeof(char), 1 , arquivo); 		//escreve no arquivo cabecalho
                
                
                for(int i = 0; i < bytes ; i ++) {
                    fwrite(valores, sizeof(char), 1 , arquivo ); 	//escreve no arquivo todos os campos da string
                    valores ++;
                }
                
                valores = valores - bytes;							// volta para o inicio dos valores da string
                valores = valores + tamanho + (4 - tamanho%4);	 	// vai para o primeiro endereço depois do fim da string 
            }
        }
        nstructs--;
    }
    
    return 1;
}

void mostracomp (FILE *arq){
    char cabecalho;
    char p;
    char nstructs, numbytes;
    char ultimo = 0;
    
	fread(&p, sizeof(char), 1 , arq);
    nstructs = p;
	printf("Estruturas: %02x \n\n", nstructs);
    
    while (nstructs){
    	ultimo = 0;
    	while(!ultimo){
    		fread(&cabecalho, sizeof(char), 1 , arq);
    		if( (cabecalho & 0x80) != 0) 				// cabecalho com ultimo byte ligado -> ultimo campo da struct
    			ultimo = 1;
    		
			if( (cabecalho & 0x40) != 0){ 				// string
				printf("(str) ");
				
				numbytes = cabecalho & 0x3F; 			// quantos campos tem a string -> 0011 1111
				while(numbytes){
					char aux;
				    fread(&aux, sizeof(char), sizeof(char) , arq);
				    printf("%c", aux);
				    numbytes--;
				}
				printf("\n");
			}
			
			else if( (cabecalho & 0x20) != 0){ // signed int
				printf("(int) ");
				numbytes = cabecalho & 0x1F;
				char sinal = 'n';
				int num = 0;
				
				for(int i = numbytes; i>0; i--){
					int aux = 0;
				    fread(&aux, sizeof(char), sizeof(char), arq);
				    if(i == numbytes){
				        if((aux & 0x80) != 0)
				        sinal = 'n';						// se negativo muda a definicao (def) para 'n'
				    }
					num = num << 8 ;
			        num = num | aux;
				}
				
				num = num << (4-numbytes) * 8;
				num = num >> (4-numbytes) * 8;
				
				/*											// G A M B I A R R A
				if( sinal == 'n') {							// se o numero for negativo...
				    num =  num << (4-numbytes) * 8;
				    num = ~num;
				    num =  num >> (4-numbytes) * 8;
				    num ++;
				    num *= -1;         
				}*/
				printf("%d", num);
				printf(" (%08x)\n", num);
			}
			 
			else{                   //UNSIGNED, neste caso p ja contem o num de bytes gravado
				printf("(uns) ");
				numbytes = cabecalho & 0x1F;
				unsigned int num = 0, aux =0;
				    while(numbytes){
				        fread(&aux, sizeof(char), sizeof(char) , arq);
				        num = num << 8 ;
				        num = num | aux;
				        numbytes--;
				    }
				    
				printf("%0u", num);
				printf(" (%08x)\n", num);
			}
		}
		nstructs--;
	}
}



