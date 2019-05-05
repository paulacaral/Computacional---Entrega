/* gcc -Wall -O3 -o p.exe p.c -lm*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Poblar.h"
#include "Imprimir.h"
#include "Clasificar.h"
#include "Flabel.h"
#include "Tlabel.h"
#include "Actualizar.h"
#include "Myperco.h"
#include "Masa_perc.h"

//#include "imprimir_txt.h"
#include "n_s.h"
#include "Prob_critica_metodo1a.h"
#include "Masa_Prob_critica.h"

int poblar(int *red, float p, int dim);
int imprimir(int *red, int dim);
int clasificar(int *red, int dim);
int actualizar(int *red, int s, int frag);
int etiqueta_falsa(int *red,int dim,int j, int i, int *historial,int s1, int s2, int frag);
int etiqueta_ultima_revision(int *red, int *historial, int o, int i);
int myperco(int *red, int dim, int *vec1, int *vec2);

int imprimirtxt(int *red, int dim);
int ns(int dim, int *red, int *n_s, int *vec);
int masa_percolante(int *red, int dim, int *vec1, int *vec2);
float Uno_a_prob_critica(int *red, int dim, int* vec1, int* vec2, float p, int cant_de_iteraciones, int precision);
float prob_critica_para_masa(int* red, int dim, int* vec1, int* vec2, float p, int cant_de_percolantes);

int main(int argc, char* argv[])
{
	int dim, *red, *vec, *vec1, *vec2, *n_s;
	float p;

	p = 0.5;
    dim = 20;
	//int h = 0;
	
	if (argc==2 || argc==3) sscanf(argv[1],"%d",&dim); /* || es "o". entonces esto me dice que si le paso un argumento mas ademas de prueba.exe, esa va a ser la dim. y si ademas le paso un tercer argumento, va a ser la probabilidad p. */
    if (argc==3) sscanf(argv[2],"%f",&p); /* lo unico que cambia esto es poder cambiar las dimensiones de la red y etc desde la linea de comando y no volviendo a modificar este archivo todas las veces*/

	// Defino la red 
	red = (int*)malloc(dim*dim*sizeof(int));
	vec1 = (int*)malloc(dim*dim*sizeof(int));
	vec2 = (int*)malloc(dim*dim*sizeof(int));
	
	vec = (int*)malloc(dim*dim*sizeof(int));
	n_s = (int*)malloc(dim*dim*sizeof(int));
	
    printf("\n");
	printf("dim = %d\n",dim);
    printf("p= %f\n\n",p);
	
	//////////////////////////////////////////////////////
	int cant_de_iteraciones = 27000;
	int cant_de_percolantes = 10;

	int k = 0;
	int m = 0;

	srand(1);
	
	FILE* fp;
	char filename[64];
	
	sprintf(filename, "dim_%i_MasaPerc.txt", dim);

	fp = fopen(filename,"w");
	
	for(k = 0; k < cant_de_iteraciones; k++)
	{	
		printf("iteracion %i\n", k);
		p = prob_critica_para_masa(red, dim, vec1, vec2, p, cant_de_percolantes);
		fprintf(fp, "%f\t", p);
		m = masa_percolante(red, dim, vec1, vec2);
		fprintf(fp, "%i\n", m);
	}
	
	fclose(fp);
	//////////////////////////////////////////////////////
	
	//poblar(red, p, dim);
	//clasificar(red, dim);
	//imprimirtxt(red, dim);
	//imprimir(red, dim);
	//ns(dim, red, n_s, vec);

    free(red);
	free(vec);
	free(vec1);
	free(vec2);
	free(n_s);
	
	return 0;
}