/************************************************************************************
* UVa 11493 - Salao do Clube - Maratona de Programacao - Regional 2008
*
* Autor: Vinicius J. S. Souza
* Data: 07/08/2009 
*************************************************************************************/
#include<iostream>
#include<map>
#include<cmath>
#include<vector>
#include<algorithm>

using namespace std;

#define MAX 987654321

int getMin(vector<int> &tabuas, map<int, int> qnt, int d, int n)
{	
	int result = 0;
	if (qnt[d] <= n)
	{
		result += qnt[d];
		n -= result;
		qnt[d] = 0;
	}
	else
	{
		result += n;
		n = 0;
		qnt[d] -= result;					
	}
	for (int i = 0; i < tabuas.size() && n > 0; i++)
	{
		if (!qnt[tabuas[i]])
			continue; 
		else
			qnt[tabuas[i]]--;
		int resto = d - tabuas[i];
		if (qnt[resto] > 0)
		{
			n--;
			result += 2;
			qnt[resto]--;
		} 
		else
			qnt[tabuas[i]]++;
	}
	if (n > 0)
		return MAX;
	return result;
}

int main()
{
	int d1, d2;
	bool isInicio = true;
	while (true)
	{
		if (!isInicio)
			putchar('\n');
		else
			isInicio = false;
		scanf("%d %d", &d1, &d2);
		if (!d1 && !d2) 
			break;
		int nTabuas, largura;
		scanf("%d %d", &largura, &nTabuas);
		map<int, int> qnt;
		vector<int> tabuas(nTabuas);
		for (int i = 0; i < nTabuas; i++)
		{
			scanf("%d", &tabuas[i]);
			qnt[tabuas[i]]++;
		}
		
		int minimo = MAX;
		
		if ( !((d2 * 100) % largura) )
			minimo = getMin(tabuas, qnt, d1, ((d2 * 100) / largura) );		
		if ( !((d1 * 100) % largura) )
			minimo = min(minimo, getMin(tabuas, qnt, d2, ((d1 * 100) / largura) ));
		if (minimo == MAX)
			printf("impossivel");
		else
			printf("%d", minimo);
	}	
	return 0;
}
