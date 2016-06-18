/**************************************************************************
* UVa 11494 - Bolhas e Baldes - Maratona - Regional 2008
*
* Autor: Vinicius J. S. Souza
* Data: 10/08/2009
* Tecnicas utilizadas: a maioria dos algoritmos de sorting poderia ser
   utilizada aqui, pois todos possibilitam a contagem da troca de elementos.
   Porem, o tamanho da entrada (100.000) limita a solucao a um algoritmo de
   O(n) ou O(n lgn). Assim, o mais simples eh utilizar o mergeSort.
****************************************************************************/
#include<iostream>
#include<vector>

using namespace std;

int nTrocas;

void mergeSort(vector<int> &vet, int sup, int inf)
{
	if ( (sup - inf) <= 1)
		return;
	if ( (sup - inf) == 2)
	{
		if (vet[inf] > vet[sup-1])
		{
			int temp = vet[inf];
			vet[inf] = vet[sup-1];
			vet[sup-1] = temp;
			nTrocas++;
		}
		return;
	}
	
	int half = (sup+inf) / 2;
	mergeSort(vet, half, inf);
	mergeSort(vet, sup, half); 	

	vector<int> temp(sup-inf);
	int ptrInf = inf, ptrSup = half;
	int i = 0;
	for (; ptrInf < half && ptrSup < sup; i++)
	{
		if (vet[ptrSup] < vet[ptrInf])
		{
			temp[i] = vet[ptrSup];
			ptrSup++;
			nTrocas += (half - ptrInf);
		}
		else
		{
			temp[i] = vet[ptrInf];
			ptrInf++;
		}
	}
	if (ptrSup < sup)
		ptrInf = ptrSup;
	for (;i < temp.size(); i++, ptrInf++)
		temp[i] = vet[ptrInf];

	for (int k = inf, i = 0; k < sup; k++, i++)
		vet[k] = temp[i];
}

int main()
{	
	while (true)
	{
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		vector<int> vet(n);
		for (int i= 0; i < n; i++)
			scanf("%d", &vet[i]);
		nTrocas= 0;
		mergeSort(vet, n, 0);
		if (nTrocas % 2)
			printf("Marcelo\n");
		else
			printf("Carlos\n");
	}
	return 0;
}
