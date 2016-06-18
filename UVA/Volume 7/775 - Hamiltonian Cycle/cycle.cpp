/**************************************************************************
* Maratona - Final Brasileira 1998 - Problema C - Hamiltonian Cycle
* UVA - 775
* Autor: Vinicius J. S. Souza
* Data: 12/03/2009
* Tecnicas utilizadas: travessia de grafos com DFS (busca em profundidade)
*****************************************************************************/

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<cstdlib>

using namespace std;

vector<int> son;
int n;
bool findCiclo = false;

void printGrafo(const vector<vector<bool> > &grafo)
{
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n ;k++)
		{
			cout << grafo[i][k] << ' ';
		}
		cout << endl;
	}
}

bool isHamiltonianCycle()
{
	int v = son[0];
	int conta = 1;
	while (v > 0)
	{
		//cout << "opa " << v << endl;
		conta++;
		v = son[v];
		if (conta > n+1) break;
	} 
	if (conta == n) return true;
	return false;
}

void dfs(const vector<vector<bool> > &grafo, int v, vector<bool> processado)
{
	processado[v] = true;
	//cout << v << endl;
	for (int i = 0; i < n; i++)
	{
		if (i == v) continue;
		if (findCiclo) return;
		if (grafo[v][i])
		{
			if (!processado[i])
			{
				//cout << "Chamando para " << i << endl;
				son[v] = i;
				if (son[i] == v) son[i] = -1;
				dfs(grafo, i, processado);
				
				
			}
			else
			{
				if (son[i] == v) continue;
				//cout << "Verificando ciclo h\n";
				if (isHamiltonianCycle() && !i)
				{
					son[v] = i;
					findCiclo = true;
					return;
				}
			}
		}
	}
}

int main()
{
	string input = "";
	while (!feof(stdin))
	{
		getline(cin,input);
		if (input != "")
			n = atoi(input.c_str());
		else break;
		vector<vector<bool> > grafo(n, vector<bool>(n, false)); 
		vector<bool> processado = vector<bool>(n, false);
		son = vector<int>(n, -1);
		while (1)
		{
			getline(cin, input);
			if (input == "%")
				break;
			istringstream is(input);
			int x, y;
			is >> x >> y;
			grafo[x-1][y-1] = grafo[y-1][x-1] = true;
		}
		//printGrafo(grafo);
		findCiclo = false;
		dfs(grafo, 0, processado);
		
		if (!findCiclo)
			printf("N\n");
		else
		{
			int v = 0;
			do
			{
				if (v)
					putchar(' ');
				printf("%d", v+1);
				v = son[v];				
			}while(v);
			printf(" 1\n");
		}	
	}	
	return 0;
}
