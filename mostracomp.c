
#include "gravacomp.h"
#include <stdio.h> 
#include <stdlib.h>


void mostracomp (FILE *arq){
    char p;
    char numstructs, numbytes;
    
    
	fread(&p, sizeof(char), 1 , arq);
    numstructs = p ;
	printf("Estruturas: %02x \n", numstructs);
    
    
    fread(&p, sizeof(char), 1 , arq);


   // while(numstructs){
	
 /*       if( p >= 128){ // se este for o ultimo byte da estrutura
			p-=0x80;
             numstructs -- ;
		}
  */
    
    
    if(p >= 0x40 ){ // STRING
        printf("(str)");
       numbytes = p - 0x40; 			//quantos campos tem a string
        while(numbytes){
            fread(&p, sizeof(char), sizeof(char) , arq);
            printf("%c", p);
            numbytes--;
            }
        
    }
    else if(p>=0x20){ // SIGNED
        printf("(int)");
        numbytes = p - 0x20;
        int num =0, i;
        char aux;
        char def = 'n';
        for( i = numbytes; i>0 ; i--){
            fread(&aux, sizeof(char), sizeof(char) , arq);
            if(i == numbytes ){  // checa o primeiro byte (mais sig) para ver se int eh positivo ou negativo
               if( aux < 0x80)
                def = 'p' ;                 // se positivo muda a definicao (def) para 'p'
            }
            printf("Aux lida: %02x\n", aux);
                aux = ~aux;
            printf("Aux negada: %02x\n", aux);
                num = num <<8 ;
                num = num | aux;
            printf("Num %02x\n", num);
            if(i == 1)
                num ++;         //complemento a 2 no byte menos significativo
        }
        if( def == 'p')
          num = num * -1;
        
        printf("%d", num);
        printf(" (%08x)", num);
    }
     
    else{                   //UNSIGNED, neste caso p ja contem o num de bytes gravado
		printf("(uns)");
        numbytes = p;
        unsigned int num = 0, aux =0;
            while(numbytes){
                fread(&aux, sizeof(char), sizeof(char) , arq);
                num = num << 8 ;
                num = num | aux;
                numbytes--;
            }
        printf(" %0u", num);
        printf(" (%08x)", num);
    }
}















