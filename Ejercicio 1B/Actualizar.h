#pragma once
int actualizar(int *red, int s, int frag)
{
	if(red[0] != 0)
	{
		if(s == 0)
		{
			red[0] = frag;
			frag = frag + 1;
		}
		else
		{
			red[0] = s;
		}
	}
	return frag;
}