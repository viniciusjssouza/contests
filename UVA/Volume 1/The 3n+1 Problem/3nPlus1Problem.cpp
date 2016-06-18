/***********************************************************************************************
	100 - 3n + 1 problem - Programming Challenge
	Autor: Vinicius J. S. Souza
***********************************************************************************************/

#include <iostream>
#include <cstdio>

using namespace std;
typedef unsigned long long int64;

int64 getCircleLength(int64 x);

int main()
{
	long inicio = clock();
	
	//freopen("input.txt", "r", stdin);
	int64 i=0, k=0;
	while (scanf("%llu %llu", &i, &k) == 2)
	{
		int64 max = 0;
		int64 start = 0, end = 0;
		if (i > k)
		{
			start = k; end = i;
		}
		else
		{
			start = i; end = k;
		}
		for (int looper = start; looper <= end; looper++)
		{
			int64 length = getCircleLength(looper);
			if (length > max) max = length;
		}
		cout << i << " " << k << " " << max << endl; 
	}	
	//long fim = clock();
	//cout << endl << "Tempo:" << (fim-inicio);
	return 0;
}

int64 getCircleLength(int64 x)
{
	int64 conta = 0;
	while (x > 1)
	{
		if (!(x % 2)) x = x/2;
		else x = 3*x + 1;
		conta++;
	}
	conta++;
	return conta;
}
