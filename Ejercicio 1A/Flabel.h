#pragma once
int etiqueta_falsa(int *red, int dim, int j, int i, int *historial, int s1, int s2, int frag)
{
	while(historial[s1] < 0)
	{
		s1 = -historial[s1];
	}
	while(historial[s2] < 0)
	{
		s2 = -historial[s2];
	}	
	
	if(s1 < s2)
	{
		historial[s2] = -s1; // cambio el valor de historial a su nueva etiqueta falsa
		red[dim*j + i] = s1; // cambio el valor de la red que estba mirando por la etiqueta real correspondiente 
	}		
	else
	{
		if(s1 == s2)
		{
			historial[s2] = s1; 
			historial[s1] = s1; 
			red[dim*j + i] = s1; 
		}
		else
		{
			historial[s1] = -s2; // cambio el valor de historial a su nueva etiqueta falsa
			red[dim*j + i] = s2; // cambio el valor de la red que estba mirando por la etiqueta real correspondiente 
		}
	}
	
	return 0;
}