#pragma once

int masa_percolante(int *red, int dim, int *vec1, int *vec2)
{
	int h, i, j, masa;
	
	masa = 0;
	h = 0;
	
	for(i = 0; i < dim*dim; i++) 
	{
		vec1[i] = 0;
		vec2[i] = 0;
	}
	
	for(i = 0; i < dim; i++)
	{
		j = red[i];
		
		vec1[j] = 1;
		
		j = red[dim*(dim-1)+i];
		
		vec2[j] = 1;
	}
	
	// Si percola, h = 1.
	for(i = 1; i < dim*dim; i++) if((*(vec1+i))*(*(vec2+i))) h = i;
	
	for(i = 1; i < dim*dim; i++)
		{
			if ((*(red+i)) == h && h != 0) masa++;
		}
	return masa;
}