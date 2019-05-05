int actualizar(int *red, int s, int frag);
int etiqueta_falsa(int *red,int dim,int j, int i, int *historial, int s1, int s2, int frag);
int etiqueta_ultima_revision(int *red, int *historial, int o, int i);



int clasificar(int *red, int dim)
{
	int i, j, frag, s, s1, s2;
	int *historial;
	
	historial = (int*)malloc(dim*dim*sizeof(int));
	
	for(i = 0; i < dim*dim; i++)
	{
		historial[i] = i;
	}
	
	frag = 2; // defino la etiqueta como 2 (poner etiqueta 1 seria confuso)
	
	/*
	Miro el primer elemento que es *red (o red[0]) y digo que si es 0, no cambie nada.
	Y si es 1 (o sea, else), le ponga el nombre de frag. y a frag le sume 1.
	*/
	if(red[0] != 0)
	{
		red[0] = frag;
		frag = frag + 1;
	}
	
	/* 
	Aca deberia recorrer mi primer linea, despues del primer elemento y 
	hacer lo mismo, mirando el estado del vecino de atras
	*/
	for(i = 1; i <dim; i++)
	{
		s = red[i-1];
		frag = actualizar(red+i, s, frag);
	}
	
	for(j = 1; j <dim; j++) // Recorre filas
	{
		s1 = red[dim*(j - 1)]; // Voy a mirar el primer elemento de la fila entonces solo me importa el que esta justo arriba
		frag = actualizar(red+dim*j,s1,frag);// Miro el primer elemento de la fila: solo me hace falta usar la funcion actualizar, porque no puedo tener conflicto. solo tengo un elemento arriba que puede ser distinto de 0
		
		for(i = 1; i < dim; i++) // Recorre columnas
		{
			if(red[dim*j + i] != 0)
			{
				s1 = red[dim*j + i - 1]; // El valor del que está a su izq
				s2 = red[dim*(j - 1) + i]; // El valor del que está arriba
				
				if(s1 == 0 && s2 == 0)
				{
					red[dim*j + i] = frag;
					frag = frag+1;
				}
				
				if(s1 != 0 && s2 == 0)
				{
					while(historial[s1] < 0) s1 = -historial[s1];
					red[dim*j + i] = s1;
				}
				
				if(s1 == 0 && s2 != 0)
				{
					while(historial[s2] < 0) s2 = -historial[s2];
					red[dim*j + i] = s2;
				}
				
				if(s1 != 0 && s2 != 0)
				{
					etiqueta_falsa(red, dim, j, i, historial, s1, s2, frag);
				}
			}
		}
	}
	for(i = 0; i < dim*dim; i++) // Reviso todo como quedó y le pngo a las etiquetas falsas su etiqueta real
	{
		if(red[i] != 0)
		{
			int o;
			o = red[i];
			etiqueta_ultima_revision(red, historial, o, i);
		}
	}
	free(historial);
	return 0;
}