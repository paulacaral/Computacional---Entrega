#pragma once
float prob_critica_para_masa(int* red, int dim, int* vec1, int* vec2, float p, int cant_de_percolantes)
{
	
	int i, j;
	//srand(time(NULL)+k);
	j = 0;
	i = 2;
	p = 0.5;

	while (j < cant_de_percolantes)
	{

		poblar(red,p,dim);		
		clasificar(red,dim);
		if(myperco(red, dim, vec1, vec2) == 1)
		{
			p = p-1/(float)(2*i);
			i = i+2;
			j = j+1;
		}
		else
		{
			p = p+1/(float)(2*i);
			i = i+2;
		}
	}

	return p;
}