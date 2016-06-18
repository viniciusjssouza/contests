/************************************************************************************************
* UVA 10276 - Hanoi Troubles Again! - Programming Challenges
*
* Autor: Vinicius J. S. Souza
* Data: 10/04/2009
* Tecnicas utilizadas: backtracking (muita atenção no enunciado... não é necessário testar TODAS as
						possibilidades!)
***************************************************************************************************/

#include<iostream>
#include<deque>
#include<cmath>

#define INFINITO 1000000000

using namespace std;

int n;

int backtrack(deque<int> &pegs, int max)
{
	bool placed = false;
	if (max >= INFINITO) return max+1;
	
	int result = 0;
	for (int i = 0; i < n; i++)
	{
		bool isCandidato = false;
		if (pegs[i] >= 0)
		{
			int soma = pegs[i] + max+1;
			float raiz = sqrt((float)soma);
			if (floor(raiz) == ceil(raiz))
				isCandidato = true;
		}
		else 
			isCandidato = true;
		if (isCandidato)
		{
			deque<int> candidatos = pegs;
			candidatos[i] = max+1;	
			placed = true;
			int next = max+1;
			result = backtrack(candidatos, max+1)+1;
			break;
		}
	}
	if (!placed) return 1;
	return result;
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	for (int test = 0; test < nTest; test++)
	{
		scanf("%d", &n);
		int max = -1;
		
		deque< int > pegs(n, -1);
		pegs[0] = 1;
		max = backtrack(pegs, 1);
		if (max >= INFINITO) printf("-1\n");
		else printf("%d\n", max);
	}
}
