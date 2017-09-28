#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s {
    int  i;
    char s1[5];
    unsigned int u;
  }Estrutura;


int gravacomp (int nstructs, void *est, char* descritor, FILE* arq){
    fwrite(&nstructs, sizeof(char),1,arq); // escreve primeiro byte
  //while(nstructs>0){
   
    char c = 0x00; //byte de cabecalho
    char d = *descritor;
    descritor++; //descritor aponta para prox byte

    if(*descritor == '\0' ) //se esse for o ultimo campo do desc, o 1 bit eh ligado
        c = c | 0x01;
     c = c << 7;
   
    if (d == 'i'){ // signed int
        c = c | 0x20; // 0x20 = 0010 0000
    /********* CABECALHO *****************/ 
       
    }
       
   else if (d == 'u'){ //inteiro sem sinal
    /********* CABECALHO *****************/ 
      if(((Estrutura *)est)->u >0xFFFFFF)// se foram necessarios 4 bytes
       c = c | 0x04;
      else if (((Estrutura *)est)->u <=0xFFFFFF && ((Estrutura *)est)->u > 0xFFFF)
        c = c | 0x03;
      else if (((Estrutura *)est)->u <= 0xFFFF && ((Estrutura *)est)->u >0xFF)
        c = c | 0x02;
      else
        c = c | 0x01;
   
      fwrite(&c, sizeof(char), 1, arq); //escreve cabecalho
      /********* ***** *****************/ 
     printf("%d", ((Estrutura *)*est[0])->u);
   
    //}
//   else{
   
   
    //}

    return 1;
}


int main(){
    /***** Abertura do Arquivo ******/
    FILE *arq = fopen ("Arquivo.txt", "wb");
    if (arq == NULL){
        printf("Problemas na abertura do arquivo\n");
        exit(1);
    }
    /*****************************/
    int num=2, i=0; //numero de arrays da estrutura
    char desc[15] = "iis03us10";
   
    Estrutura vet[2];

    /*  obs que primeiro argumento deve ser menor q 255 para dar certo
         pois estamos assumindo q ocupara um byte so, depois otimizar para
         caso primeiro arg seja maior que 255 */
    gravacomp(2, vet, desc, arq);
   


    return 0;
} 
