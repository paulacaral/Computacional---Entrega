int imprimir(int *red, int dim)
{	
	int i,j;
	for(i = 0; i < dim; i++)
	{
		for(j = 0; j < dim; j++)
		{
			printf("%d ", red[dim*i + j]);
		}
		printf("\n");
	}
	printf("\n");
	
return 0;
}