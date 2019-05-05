#pragma once

int ns(int dim, int *red, int *n_s, int *vec)
{
	FILE *fp;
	char filename[64];
	float p;
	int i, k, n, fragmento;
	
	sprintf(filename, "dim_%i_ns2_5.txt", dim);

	fp = fopen(filename, "w");
	srand(1);
	for(p = 0.540 ; p <= 0.5500 ; p = p + 0.0001)
	{
		
		i = 0;
		printf("p %f\n",p);
		fprintf(fp, "%f\t", p);

		//reinicio n_s
		for(i = 0; i<dim*dim; i++)
		{
			n_s[i] = 0;
		}

		for(k = 0; k <= 27000; k++)
		{ 
			//reinicio vec
			for(i = 0; i < dim*dim; i++)
			{
				vec[i] = 0;
			}
						
			poblar(red, p, dim);		
			clasificar(red, dim);
			
			// Calculo de n_s
			
			for(i = 0; i < dim*dim; i++)
			{
				fragmento = *(red+i);
				vec[fragmento]++;
			}	
			i = 0;
			for(i = 0; i < dim*dim; i++)
			{
				n = vec[i];
				(*(n_s+n))++;
			}
			i = 0;
		}
		
		for(k = 0; k < dim*dim; k++)
		{
			fprintf(fp, "%i ", *(n_s + k));
		}
			
	fprintf(fp, "\n");
	fprintf(fp, "\n");
	}
	fclose(fp);
	return 0;
}