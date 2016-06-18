/************************************************************************************************
 * UVa problem - 10038 - Jolly Jumpers - Programming Challenges
 * Autor: Vinicius Jose Silveira de Souza
 * Data: 19/02/2008 
 ************************************************************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>

#define  MAXN   3010	

using namespace std;

void initNumMarcados();
bool isJolly();

bool numMarcados[MAXN];
int n = 0;

int main()
{
	freopen("input.txt", "r", stdin);
	
	while (true)
	{
		string buffer;
		/* inicializa o vetor de numeros marcados */
		initNumMarcados();
		long nums[MAXN];
		if (feof(stdin)) return 0;
		cin >> n;
		if (feof(stdin)) return 0;
		if (n > 1)
		{
			for (int i = 0; i < n; i++)
			{	
				cin >> nums[i];
				if (i > 0)
				{
					long diferenca = nums[i] - nums[i-1];
					if (diferenca < 0) diferenca = -diferenca;
					numMarcados[diferenca] = true;
				}
			}
			if (isJolly())
				cout << "Jolly\n";
			else
				cout << "Not jolly\n";
		}
		else if (n == 1)
		{
			int aux;
			cin >> aux;
			cout << "Jolly\n";
		}
		else if (n == 0)
			cout << "Not jolly\n";
	}
}

void initNumMarcados()
{
	for (int i = 0; i < MAXN; i++)
	{
		numMarcados[i] = false;
	}
}

bool isJolly()
{
	for (int i = 1; i < n; i++)
		if (!numMarcados[i]) return false;
	return true;
}