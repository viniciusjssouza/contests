/*********************************************************************
* Almost Shortest Path - Final Sul-americana 2008
*
* Autor: Vinicius J. S. Souza
* Data: 24/08/2009
* Tecnicas utilizadas: algoritmo de caminho minimo, Dijkistra
***********************************************************************/

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<deque>
#include<vector>
#include<queue>
#include<set>

#define MAX 987654321

using namespace std;

int n, m;

struct Edge
{
   int lig;
   int peso;
   bool enable;         
};

typedef vector<vector<Edge> > Grafo;
typedef pair<int,int> pii;

void remove(Grafo &g, set<pii> &toRemove)
{
	for (set<pii>::iterator ite = toRemove.begin(); ite != toRemove.end(); ite++)
		g[(*ite).first][(*ite).second].enable = false;
}

void marcaParaRemocao(set<pii> &toRemove, vector<pii> &parent, int end)
{
	pii par = parent[end];
	while (par.first >= 0 && par.second >= 0)
	{
		toRemove.insert(par);
		par = parent[par.first];			
	}
}

int getCaminhoMin(Grafo &g, int start, int destination, vector<pii> &parent)
{
    parent = vector<pii>(n, pii(-1,-1));
	vector<int> distance(n, MAX);
    priority_queue<pii, vector<pii>, greater<pii> > fila;
	distance[start] = 0;
	fila.push(pii(0, start));

	while (!fila.empty())
	{
		pii top = fila.top();
		fila.pop();
		int v = top.second, d = top.first;
		if (d <= distance[v])
		{
			for (int i = 0; i < g[v].size(); i++)
			{
				if (!g[v][i].enable)
					continue;
				int v2 = g[v][i].lig, cost = g[v][i].peso;
				if (distance[v2] > distance[v] + cost)
				{
					distance[v2] = distance[v] + cost;
					parent[v2] = pii(v, i);
					fila.push(pii(distance[v2], v2));
				}
			}
		}
	}
	return distance[destination];
}

int main()
{
	int start ,end;
    while(true)
    {
        scanf("%d %d", &n, &m);
        if (!n && !m) break;
        scanf("%d %d", &start, &end);
        Grafo g(n, vector<Edge>());
        for (int i = 0; i < m; i++)
        {
            Edge e;
			int x;
			scanf("%d %d %d", &x, &e.lig, &e.peso);
			e.enable= true;
            g[x].push_back(e);
        }
		vector<pii> parent;	
        int pathCost = getCaminhoMin(g, start, end, parent);
        if (pathCost == MAX)
		{
			printf("-1\n");
			continue;	
		}	      
		set<pii> toRemove;
		marcaParaRemocao(toRemove, parent, end);
		pii par = parent[end];
		while (par.first >= 0 && par.second >= 0)
		{
			g[par.first][par.second].enable = false;
			vector<pii> newParent;
			int pc = getCaminhoMin(g, start, end, newParent);
			if (pc == pathCost)
				marcaParaRemocao(toRemove, newParent, end);
			g[par.first][par.second].enable = true;
			par = parent[par.first];			
		}
		remove(g, toRemove);
		int newPathCost = pathCost;
		while (newPathCost == pathCost)
		{
			toRemove.clear();
			newPathCost = getCaminhoMin(g, start, end, parent);
			marcaParaRemocao(toRemove, parent, end);
			remove(g, toRemove);
		}
     	if (newPathCost == MAX)
			newPathCost = -1;
		printf("%d\n", newPathCost);
    }	
	return 0;
}
