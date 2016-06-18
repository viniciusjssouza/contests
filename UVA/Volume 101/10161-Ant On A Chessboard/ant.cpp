/***********************************************************************************
* UVa 10161 - Ant on a Chessboard - Programming Challenges
*
* Autor: Vinicius J. S. Souza
* Data: 2/10/2009
* Tecnicas: inducao matematica
***********************************************************************************/


#include<iostream>
#include<cmath>

using namespace std;

int main()
{
	unsigned long long n;
	while (true)
	{
		scanf("%llu", &n);
		if (!n) break;
		long long int quadro = ceil(sqrt(n));
		long long int inicio = ((quadro-1) * (quadro-1)) + 1;
		long long int dif = n - inicio;	
		long long int x, y;
		if (!(quadro & 1))		 
		{
			if ( dif < (quadro - 1) )
			{
				x = dif+1;
				y = quadro;
			}
			else if ( dif > (quadro - 1) )
			{
				x = quadro;
				y = (quadro << 1) -dif - 1;
			}
			else
				x = y = quadro;
		}
		else
		{
			if ( dif < (quadro - 1) )
			{
				x = quadro;
				y = dif + 1;
			}
			else if ( dif > (quadro - 1) )
			{
				x = (quadro << 1) - dif - 1;
				y = quadro;
			}
			else
				x = y = quadro;
		}
		printf("%llu %llu\n", x, y);		
	}
	return 0;
}
