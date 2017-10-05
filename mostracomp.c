
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
        char def = 'n';
        int num = 0, i;
        int aux =0;
        for(i=numbytes; i>0 ; i--){
            fread(&aux, sizeof(char), sizeof(char) , arq);
            if( i == numbytes ){
                if(aux>0x80)
                def = 'n';                           // se negativo muda a definicao (def) para 'n'
            }
                num = num << 8 ;
                num = num | aux;
        }
        if( def == 'n') {
            num =  num << (4-numbytes) * 8;
            num = ~num;
            num =  num >> (4-numbytes) * 8;
            num ++;
            num *= -1;         }
       
        
      printf("\n%d", num);
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















