int poblar(int *red, float p, int dim)
{
	int i;
    float r;
	
	for(i = 0; i < dim*dim; i++)
	{
        r = (float)rand()/(float)RAND_MAX;
		red[i] = 0;

		if(r < p)
		{
			red[i] = 1;
		}
	}
	return 0;
}