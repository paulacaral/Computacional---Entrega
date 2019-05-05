#pragma once

int etiqueta_perc(int *red, int dim, int *vec1, int *vec2)
{
	int h, i, j;
	
	i = 0;	
	h = 0;
	
	for(i = 0; i < dim*dim; i++) 
	{
		vec1[i] = 0;
		vec2[i] = 0;
	}
	i = 0;
	for(i = 0; i < dim; i++)
	{

		j = red[i];
		vec1[j] = 1;		
		
	}
	
	i = 0;
	for(i = 0; i < dim; i++)
	{
		j = red[dim*(dim-1)+i];
		
		vec2[j] = 1;
		
	}
	
	// Si percola, h = etiqueta del percolante.
	for(i = 1; i < dim*dim; i++) if((*(vec1+i))*(*(vec2+i))) h = i;
	
	return h;
}