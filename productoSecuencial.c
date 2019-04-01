#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int numLines(FILE *f);

void fillArray(FILE *f, int size, int *array);

int dotProd(int *array1, int *array2, int size);

int main (int argc, char *argv[]){

	if(argc != 3){
		printf("Recuerde que debe ingresar los nombres de los 2 archivos separados por un espacio\n");
		exit(1);
	}

	//Abriendo archivos
	FILE *f1 = fopen(argv[1], "r");
	FILE *f2 = fopen(argv[2], "r");

	if(f1 == NULL || f2 == NULL){
		printf("Error al abrir archivos\n");
	}

	printf("Ingreso: %s y %s\n", argv[1], argv[2]);

	//Contando lineas de cada archivo
	int len1, len2;
	len1 = numLines(f1);
	len2 = numLines(f2);

	//Retornando puntero al inicio de cada archivo
	rewind(f1);
	rewind(f2);

	printf("Longitud de 1: %d \nLongitud de 2: %d\n", len1, len2);

	if(len1 != len2){
		printf("Los vectores deben tener el mismo tamaño");
	}

	//Creando vectores
	int *array1	= malloc(len1* sizeof(int));
	int *array2	= malloc(len2* sizeof(int));

	fillArray(f1, len1, array1);
	fillArray(f2, len2, array2);

	//Multiplicación 

	//Midiendo tiempo
	struct timeval begin, end;
	gettimeofday(&begin, NULL);

	int result = dotProd(array1, array2, len1);

	gettimeofday(&end, NULL);

	//Tiempo que tomó
	double elapsed = (end.tv_sec - begin.tv_sec) + 
              ((end.tv_usec - begin.tv_usec)/1000000.0);

	//Imprimir
	printf("Resultado = %d\n", result);

	//Imprimiendo tiempo
	printf("El programa tomó: %f segundos\n", elapsed);
}

int numLines(FILE *f){
	int counter = 0;
	char chr = getc(f);

	while(chr != EOF){

        if (chr == '\n')
        {
            counter++;
        } 

        chr = getc(f);
	}

	return counter;
}

void fillArray(FILE *f, int size, int *array){
	char num[size];
	for(int i = 0; i < size; i++){
		fgets(num, size+1, f);
		array[i] = atoi(num);
	}
}

int dotProd(int *array1, int *array2, int size){
	int result = 0;

	for(int i = 0; i < size; i++){

		result += array1[i] * array2[i];
	}

	return result;
}