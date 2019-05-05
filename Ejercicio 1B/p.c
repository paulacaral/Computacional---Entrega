/* gcc -Wall -O3 -o p.exe p.c -lm*/

/* Problema 1b*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

/* DeclaraciÃ³n */
int poblar(int *red, float p, int dim);
int imprimir(int *red,int dim);
int clasificar(int *red, int dim);
int actualizar(int *red, int s, int frag);
int etiqueta_falsa(int *red,int dim,int j, int i, int *historial,int s1, int s2, int frag);
int etiqueta_ultima_revision(int *red, int *historial, int o, int i);
int myperco(int *red, int dim);

int main(int argc, char* argv[])
{
	int dim;
    int *red;
    float p, p_perc;
	int k, cant_de_iteraciones, casos_fav;
	int i, cant_de_curvas;;
	FILE *fp;
	char filename[64];


	i = 0;
	cant_de_curvas = 1;
	k = 0;
	cant_de_iteraciones = 1000;
	p_perc = 0.0;
	
	// Valores por default: 
	p=0.3;
    dim=20;
	
	
	// Pedir argumentos
	//printf("Ingrese dimension de la red: \n"); 
    //scanf("%d",&dim); 
	//printf("Ingrese probabilidad de poblar: \n"); 
	//scanf("%f",&p);	
	//printf("Ingrese precision: \n"); 
	//scanf("%i",&precision);
	//printf("Ingrese cantidad de iteraciones: \n"); 
	//scanf("%i",&cant_de_iteraciones);	
	
	// Argumentos desde cmd
	
	if (argc==2 || argc==3) sscanf(argv[1],"%d",&dim); /* || es "o". entonces esto me dice que si le paso un argumento mas ademas de prueba.exe, esa va a ser la dim. y si ademas le paso un tercer argumento, va a ser la probabilidad p. */
    if (argc==3) sscanf(argv[2],"%f",&p); /* lo unico que cambia esto es poder cambiar las dimensiones de la red y etc desde la linea de comando y no volviendo a modificar este archivo todas las veces*/

	// Defino la red 
	red = (int*)malloc(dim*dim*sizeof(int));
	

    printf("\n");
	printf("dim = %d\n",dim);
    printf("p= %f\n\n",p);
	
	
	for(i=0; i<cant_de_curvas; i++)
	{
	//sprintf(filename, "dim_%i_Pperc_%i.txt", dim,i);
	sprintf(filename, "dim_%i_Pperc_9.txt", dim);
	
	fp = fopen(filename,"w");
	for(p = 0.55 ; p <= 0.65 ; p = p + 0.001)
	{
	    casos_fav = 0;
		for(k=0;k<cant_de_iteraciones;k=k+1)
		{	
			srand(time(NULL)+k+i*cant_de_iteraciones);
			//srand(time(NULL)+k);
			
			poblar(red,p,dim);		
			clasificar(red,dim);
		
			if(myperco(red,dim)==1)
			{
				casos_fav = casos_fav + 1;
			}
			
		}
	p_perc = casos_fav/(float)cant_de_iteraciones;
	fprintf(fp, "%f\t", p);
	fprintf(fp, "%f\n", p_perc);
	}
	fclose(fp);
	}
    free(red);

	return 0;
}

int poblar(int *red, float p, int dim)
{
	int i;
    float r; /* definir todas las variables primero asi es mas facil encontrarlas */
	for(i=0; i<dim*dim;i=i+1)
	{
        r = (float)rand()/(float)RAND_MAX; /* rand() me tira enteros entre 0 y RAND_MAX entonces tengo que hacer el cociente para que  me quede algo entre 0 y 1 */
		*(red+i)=0;

		if(r<p)
		{
			*(red+i)=1;
		}
	}
	return 0;
}

	
int imprimir(int *red,int dim)
{
	int i,j;
	for(i=0;i<dim;i=i+1)
	{
		for(j=0;j<dim;j=j+1)
		{
			printf("%d ", *(red+dim*i+j));
		}
		printf("\n"); /* esto cambia d elinea. hace un nuevo renglon. entonces poniendo esto lo puedo ver como una matriz */
	}

        printf("\n"); // lo mismo, la gracia es que me separa la ultima linea de matriz de la siguiente linea de comando entonces es mas prolijo 

	return 0;
}



int clasificar(int *red, int dim)
{
	int i,j;
	int frag;
	int s,s1,s2;
	int *historial;
	
	historial = (int*)malloc(dim*dim*sizeof(int));
	for(i=0;i<dim*dim;i=i+1)
	{
		*(historial+i) = i;
	}

	
	frag = 2; // defino la etiqueta como 2 (poner etiqueta 1 seria confuso)
	
	if(*red!=0) // miro el primer elemento que es *red y digo que si es 0, no cambie nada. y si es 1 (o sea, else), le ponga el nombre de frag. y a frag le sume 1.
	{
		*red = frag;  
		frag = frag +1;
	}
	
	for(i=1;i<dim;i=i+1) // aca deberia recorrer mi primer linea, despues del primer elemento y hacer lo mismo, mirando el estado del vecino de atras
	{
		s = *(red+i-1);
		frag = actualizar(red+i, s, frag);
	}
	for(j=1;j<dim;j=j+1) // Recorre filas
	{
		s1 = *(red+dim*(j-1)); // Voy a mirar el primer elemento de la fila entonces solo me importa el que esta justo arriba
		frag = actualizar(red+dim*j,s1,frag);// Miro el primer elemento de la fila: solo me hace falta usar la funcion actualizar, porque no puedo tener conflicto. solo tengo un elemento arriba que puede ser distinto de 0
		for(i=1;i<dim;i=i+1) // Recorre columnas
		{
			if(*(red+dim*j+i)!=0)
			{
				s1 = *(red+dim*j+i-1); // El valor del que está a su izq
				s2 = *(red+dim*(j-1)+i); // El valor del que está arriba
				if(s1==0 && s2==0)
				{
					*(red+dim*j+i) = frag;
					frag = frag+1;
				}
				if(s1!=0 && s2==0)
				{
					while(*(historial+s1)<0) s1=-(*(historial+s1));
					*(red+dim*j+i) = s1;
				}
				if(s1==0 && s2!=0)
				{
					while(*(historial+s2)<0) s2=-(*(historial+s2));
					*(red+dim*j+i) = s2;
				}
				if(s1!=0 && s2!=0)
				{
					etiqueta_falsa(red,dim,j,i,historial,s1,s2,frag);
				}
			}
		}
	}
	for(i=0;i<dim*dim;i=i+1) // Reviso todo como quedó y le pngo a las etiquetas falsas su etiqueta real
	{
		if(*(red+i)!=0)
		{
			int o;
			o = *(red+i);
			etiqueta_ultima_revision(red,historial,o,i);
		}
	}
	return 0;
}

int actualizar(int *red, int s, int frag)
{
	if(*red!=0)
	{
		if(s==0)
		{
			*red = frag;
			frag = frag+1;
		}
		else
		{
			*red = s;
		}
	}

	return frag;
}

int etiqueta_falsa(int *red,int dim,int j, int i, int *historial,int s1, int s2, int frag)
{
	while(*(historial+s1)<0)
	{
		s1 = -*(historial+s1);
	}
	while(*(historial+s2)<0)
	{
		s2 = -*(historial+s2);
	}	
	
	if(s1<s2)
	{
		*(historial+s2) = -s1; // cambio el valor de historial a su nueva etiqueta falsa
		*(red+dim*j+i) = s1; // cambio el valor de la red que estba mirando por la etiqueta real correspondiente 
	}		
	else
	{
		if(s1==s2)
		{
			*(historial+s2) = s1; 
			*(historial+s1) = s1; 
			*(red+dim*j+i) = s1; 
		}
		else
		{
			*(historial+s1) = -s2; // cambio el valor de historial a su nueva etiqueta falsa
			*(red+dim*j+i) = s2; // cambio el valor de la red que estba mirando por la etiqueta real correspondiente 
		}
	}
	
	return 0;
}

int etiqueta_ultima_revision(int *red, int *historial, int o, int i)
{
	while(*(historial+o)<0)
	{
		o = -*(historial+o);
	}
	*(red+i) = o;
	return 0;
}

int myperco(int *red, int dim)
{
	int h,i,j;
	int *vec1,*vec2;
	
	h=0;
	vec1=(int *)malloc(dim*dim*sizeof(int));
	vec2=(int *)malloc(dim*dim*sizeof(int));
	
	for(i=0;i<dim*dim;i++) 
	{
		*(vec1+i)=0;
		*(vec2+i)=0;
	}
	
	for(i=0;i<dim;i++)
	{
	j=*(red+i);
    *(vec1+j)=1;
	j=*(red+dim*(dim-1)+i);
    *(vec2+j)=1;		
	}
	
	// Si percola, h = 1.
	for(i=1;i<dim*dim;i++) if ((*(vec1+i))*(*(vec2+i))) h=1;

	free(vec1);
	free(vec2);
	return h;
}
