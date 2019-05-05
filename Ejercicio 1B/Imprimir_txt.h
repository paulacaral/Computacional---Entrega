int imprimirtxt(int *red, int dim)
{	
	FILE *fp;
	char filename[64];
	sprintf(filename, "matrizdim_%i.txt", dim);
	fp = fopen(filename,"w");
	
	int i,j;
	for(i = 0; i < dim; i++)
	{
		for(j = 0; j < dim; j++)
		{
			fprintf(fp, "%d ", red[dim*i + j]);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");
	fclose(fp);
return 0;
}