#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N_STRUCTS 2	
#define MAX 64

typedef struct Ponto {
	int x;
	int y;
} Ponto;



int main(){	
	Ponto* array;
	char descritor[] = {'i', 'i'};
	FILE* arquivo;
	
	arquivo = fopen ("file.txt", "w+");
	
	array = (Ponto*)malloc(sizeof(Ponto)*N_STRUCTS);
	array[0].x = 1;
	array[0].y = 3;
	array[1].x = 5;
	array[1].y = 9;

	
	fclose (arquivo);

	return 0;
}
