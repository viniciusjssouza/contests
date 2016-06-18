/*************************************************************************************
* UVa 11497 - Divisao da Nlogonia - Maratona - Regional 2008
*
* Autor: Vinicius J. S. Souza
* Data: 10/08/2009
***************************************************************************************/

#include<iostream>

using namespace std;

int main()
{
	while (true)
	{
		int n ;
		scanf("%d", &n);
		if (!n)
			break;
		int xdiv, ydiv, x, y;
		scanf("%d %d", &xdiv, &ydiv);
		for (int i = 0; i < n; i++)
		{
			scanf("%d %d", &x, &y);
			if (x == xdiv || y == ydiv)
				printf("divisa\n");
			else if (x > xdiv && y > ydiv)
				printf("NE\n");
			else if (x < xdiv && y > ydiv)
				printf("NO\n");
			else if (x < xdiv && y < ydiv)
				printf("SO\n");
			else
				printf("SE\n");
		}
	}
	return 0;
}

