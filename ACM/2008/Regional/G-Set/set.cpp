/*************************************************************************
* UVa 11496 - Set - Maratona 2008 - Regional
*
* Autor: Vinicius J. S. Souza
* Data: 14/08/2009
* Tecnicas utilizadas: backtracking + combinatoria
*		- Existem apenas 21 sets possiveis, sendo que, 9 sao formados por
*	cartas iguais. Se a solucao otima tiver 3 ou mais set dos outros 12 tipos,		
*   pode-se entao substituir cada um desses sets por um outro formado apenas 
*   por cartas iguais. Assim, os 12 outros tipos de set tem, no maximo, 2 sets
*	por conjunto de cartas. Isso possibilita uma busca exaustiva pela solucao
*   otima utilizando backtracking no espaco de 3^12 possibilidades, independente-
*	mente do tamanho da entrada.
***************************************************************************/

#include<iostream>
#include<vector>
#include<map>
#include<string>

#define c1	0
#define c2	1
#define c3	2

#define t1	3
#define t2	4
#define t3	5

#define q1	6
#define q2	7
#define q3	8

int sets[12][3] = {
	c1, c2, c3,
	q1, q2, q3,
	t1, t2, t3,
	c1, q1, t1,
	c2, q2, t2,
	c3, q3, t3,
	c1, q2, t3,
	c1, q3, t2,
	c2, q1, t3,
	c2, q3, t1,
	c3, q1, t2,
	c3, t2, q1
};

using namespace std;

int backtrack(int cartas[], int setId, int &qnt)
{
	if (cartas[sets[setId][0]] < qnt || cartas[sets[setId][1]] < qnt ||
			cartas[sets[setId][2]] < qnt)
	{
		return 0;
	}
	cartas[sets[setId][0]] -= qnt;
	cartas[sets[setId][1]] -= qnt;
	cartas[sets[setId][2]] -= qnt;
	int max = 0;
	
	if (setId == 11)
	{
		max += (int) cartas[c1] / 3;
		max += (int) cartas[c2] / 3;
		max += (int) cartas[c3] / 3;
		max += (int) cartas[t1] / 3;
		max += (int) cartas[t2] / 3;
		max += (int) cartas[t3] / 3;
		max += (int) cartas[q1] / 3;
		max += (int) cartas[q2] / 3;
		max += (int) cartas[q3] / 3;
		cartas[sets[setId][0]] += qnt;
		cartas[sets[setId][1]] += qnt;
		cartas[sets[setId][2]] += qnt;		
		return max;		
	}
	for (int i = 0; i < 3; i++)
	{
		int result = backtrack(cartas, setId+1, i)+qnt;
		if (result > max)
			max = result;
	}	
	cartas[sets[setId][0]] += qnt;
	cartas[sets[setId][1]] += qnt;
	cartas[sets[setId][2]] += qnt;
	return max;
}

int main()
{
	char numStr[15], tipo[15];
	while (true)
	{
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		int cartas[9];
		for (int i = 0; i < 9; i++)
			cartas[i] = 0;
		for (int i = 0; i < n; i++)
		{
			scanf("%s %s", numStr, tipo);
			int num = 1;
			if (numStr[0] == 'd')
				num = 2;
			else if (numStr[0] == 't')
				num = 3;

			int type = 0;
			if (tipo[0] == 't')
				type = 3;
			else if (tipo[0] == 'q')
				type = 6;
			cartas[type+num-1]++;				
		}
		int max = 0;
		for (int i = 0; i < 3; i++)			
		{
			int result = backtrack(cartas, 0, i);
			if (result > max)
				max = result;
		}
		printf("%d\n", max);
	}
	return 0;
}
