/*********************************************************************************
* Mesa da Sra. Montagny - Seletivas IME-USP
*
* Autor: Vinicius J. S. Souza
* Data: 21/01/2010
* Tecnicas: BFS (tecnica para descobrir se um grafo eh bipartido)
********************************************************************************/
#include<iostream>
#include<cstdio>
#include<list>
#include<vector>
#include<deque>

using namespace std;

#define FREE 	0
#define RED		-1
#define BLACK	 1

int convidados[110];
vector<list<int> > amigos(110, list<int>());
int colored[110];
int parent[110];
int N, M;

bool isBipartido(const int v)
{		
	deque<int> fila;
	colored[v] = RED;
	fila.push_back(v);

	while (fila.size())
	{
		int vertice = fila[0];
		fila.pop_front();
		for (int i = 0; i < amigos[vertice].size(); i++)
		{
			if (!colored[amigos[vertice][i]])
			{
				colored[amigos[vertice][i]] = -colored[vertice];
				parent[amigos[vertice][i]] = vertice;
				fila.push_back(amigos[vertice][i]);
			}
			else if (parent[vertice] != amigos[vertice][i] && 
				colored[amigos[vertice][i]] == colored[vertice])
				return false;				
		}
	}
	return true;		
}			

int main()
{
	int instancia = 1;	
	while(!feof(stdin) && scanf("%d %d", &N, &M) == 2)
	{
		if (instancia > 1)
			putchar('\n');
		for (int i = 0; i < N; i++)
		{
			amigos[i+1].clear();			
			colored[i+1] = FREE;
			parent[i+1] = -1;
		}
		for (int i = 0; i < M; i++)
		{
			int a,b;
			scanf("%d %d", &a, &b);
			amigos[a].push_back(b);
			amigos[b].push_back(a);
		}
		printf("Instancia %d\n", instancia);
		printf("%s", isBipartido(1) ? "sim\n" : "nao\n");
		instancia++;
	}
	return 0;	
}

