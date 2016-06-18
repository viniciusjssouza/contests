/********************************************************************
* Sistema Cipoviario - Seletivas IME-USP 2007
*
* Autor: Vinicius J. S. Souza
* Data: 02/05/2010
* Tecnicas: minimum spanning tree utilizando Kruskal.. Prim nao passa...
Kruskal: log N, devido ao fato de nao ser necessario ordenar os vertices.
**********************************************************************/

#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#include<deque>

#define INF 0x7FFFFFFF
#define MIN 1235
#define MED 8977
#define MAX 10923

using namespace std;

typedef pair<int,int> edge;

int N, M;
vector<deque<edge> > edges(3);
int id[1010];
int sz[1010];

void UFinit()
{
	for (int i = 0; i < N; i++)
	{	
		id[i] = i;
		sz[i] = 1;
	}
}

int UFfind(int v)
{
	while (v != id[v])
		v = id[v];
	return v;
}

void UFmerge(int v, int w)
{
	int i = UFfind(v), j = UFfind(w);
	if (i == j)
		return;
	if (sz[i] < sz[j])
	{
		id[i] = j;
		sz[j] += sz[i];
	}
	else
	{
		id[j] = i;
		sz[i] += sz[j];
	}
}

/******* minimum spanning tree *************/
unsigned long long kruskal(int start)
{
	unsigned long long total = 0;
	UFinit();
    int count = 0;
	for (int i = 0; i < 3; i++)
	{
		int size = edges[i].size();
		for (int k = 0; k < size; k++)
		{
			if (UFfind(edges[i][k].first) != UFfind(edges[i][k].second) )
			{
				UFmerge(edges[i][k].first, edges[i][k].second);
				if (!i) 
					total += MIN;
				else if (i == 1)
					total += MED;
				else
					total += MAX;
				count++;
				if (count >= N-1)
					return total;		
			}
		}
	}
	return total;
}

int main()
{
	int instancia = 1;
	while (!feof(stdin) && scanf("%d %d", &N, &M) == 2)
	{
		if (instancia > 1) putchar('\n');
		for (int i = 0; i < 3; i++)
			edges[i].clear();
		for (int i = 0; i < M; i++)
		{
			int cost;
			edge lig;
			scanf("%d %d %d", &lig.first, &lig.second, &cost);
			lig.first--;
			lig.second--;
			if (cost == MIN)
				edges[0].push_back(lig);
			else if (cost == MED)
				edges[1].push_back(lig);
			else
				edges[2].push_back(lig);
		}
		printf("Instancia %d\n%llu\n", instancia++, kruskal(0));		
	}	
	return 0;
}



