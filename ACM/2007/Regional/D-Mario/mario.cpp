/***************************************************************************
* D-Mario Maratona de Programacao - Regional 2007
*
* Autor: Vinicius J. S. Souza
* Data: 10/09/2009
* Tecnicas: busca binaria 
* Complexidade: O(nlgn)
**************************************************************************/
#include<iostream>
#include<cstdlib>
#include<vector>
#define TAM 100010
#define MAX 987654321

using namespace std;

int K, N;

int bsearchL(vector<int> &vet, int x, int inf, int sup)
{
	if (sup - inf == 1)
	{	
		if (vet[inf] > x && inf-1 >= 0)
			return inf-1;
		else return inf;
	}
	if ( sup - inf == 2 )
	{
		if (x >= vet[inf+1])
			return inf+1;
		else if (x >= vet[inf])
			return inf;
		else if (inf - 1 >= 0)
			return inf-1;
		else
			return inf;
	}
	int middle = (sup + inf) / 2;
	if (vet[middle] == x)
		return middle;
	else if (vet[middle] > x)
		return bsearchL(vet, x, inf, middle);
	else 
		return bsearchL(vet, x, middle, sup); 
}

int bsearchR(vector<int> &vet, int x, int inf, int sup)
{
	if (sup - inf == 1)
	{	
		if (vet[inf] < x && inf+1 < N)
			return inf+1;
		else return inf;
	}
	if ( sup - inf == 2 )
	{
		if (x <= vet[inf])
			return inf;
		else if (x <= vet[inf+1])
			return inf+1;
		else if (sup < N)
			return sup;
		else
			return inf;
	}
	int middle = (sup + inf) / 2;
	if (vet[middle] == x)
		return middle;
	else if (vet[middle] > x)
		return bsearchR(vet, x, inf, middle+1);
	else
		return bsearchR(vet, x, middle+1, sup); 
}

int main()
{
	while (true)
	{
		scanf("%d %d", &K, &N);
		if (!K && !N)
			break;
		int minimo = MAX;
		int missing = K-1;
		vector<int> vet(N, 0);
		for (int i = 0; i < N; i++)
			scanf("%d", &vet[i]);
		for (int i = 0; i < N; i++)
		{			
			if (vet[i] + missing < 100000)
			{
				int num = vet[i] + missing;
				int loc = bsearchR(vet, num, 0, N);
				int dif = abs(missing - (loc-i));
				if (vet[loc] != num)
					dif++;
				if (dif < minimo)
					minimo = dif;
			}

			if (vet[i] >= K)
			{
				int num = vet[i] - missing;
				int loc = bsearchL(vet, num, 0, N);
				int dif = abs(missing - (i-loc));
				if (vet[loc] != num)
					dif++;
				if (dif < minimo)
					minimo = dif;
			}
		}
		printf("%d\n", minimo);		
	}
	return 0;
}
