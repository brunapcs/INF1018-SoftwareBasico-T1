

#include "gravacomp.h"
#include <stdio.h> 
#include <stdlib.h>


void mostracomp (FILE *arq){
    char cabecalho;
    char p;
    char nstructs, numbytes;
    char ultimo = 0;
    
	fread(&p, sizeof(char), 1 , arq);
    nstructs = p;
	printf("Estruturas: %02x \n", nstructs);
    
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
				int aux = 0;
				
				for(int i = numbytes; i>0; i--){
				    fread(&aux, sizeof(char), sizeof(char) , arq);
				    if( i == numbytes ){
				        if((aux & 0x80) != 0)
				        sinal = 'n';                           // se negativo muda a definicao (def) para 'n'
				    }
					num = num << 8 ;
			        num = num | aux;
				}
				
				if( sinal == 'n') {							// se o numero for negativo...
				    num =  num << (4-numbytes) * 8;
				    num = ~num;
				    num =  num >> (4-numbytes) * 8;
				    num ++;
				    num *= -1;         
				}
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














