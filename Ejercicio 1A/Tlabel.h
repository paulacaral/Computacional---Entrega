#pragma once
int etiqueta_ultima_revision(int *red, int *historial, int o, int i)
{
	while(historial[o] < 0)
	{
		o = -historial[o];
	}
	red[i] = o;
	return 0;
}