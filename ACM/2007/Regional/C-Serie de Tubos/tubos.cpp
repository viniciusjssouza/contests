/*************************************************************************
* C-Serie de Tubos - Regional 2007
*
* Autor: Vinicius J. S. Souza
* Data: 09/09/2009
* Tecnicas: busca de pontes em grafos nao-direcionados.
****************************************************************************/
#include<iostream>
#include<vector>

using namespace std;

typedef vector<vector<int> > Grafo;
typedef pair<int,int> pii;

int V, E;
int bridgeCont, cnt;

void searchC(Grafo &g, vector<int> &ord, vector<int> &low, pii par)
{
	int v = par.second;
	ord[v] = cnt++;
	low[v] = ord[v];
	for (int i = 0; i < g[v].size(); i++)
	{
		if (bridgeCont)
			return;
		int v2 = g[v][i];
		if (ord[v2] == -1)
		{
			searchC(g, ord, low, pii(v,v2));
			if (low[v] > low[v2])
				low[v] = low[v2];
			if (low[v2] == ord[v2])
			{
				bridgeCont++;
				return;
			}			
		}
		else if (v2 != par.first)
			if (low[v] > ord[v2]) 
				low[v] = ord[v2];  		
	}	
}

bool haPontes(Grafo &g)
{
	vector<int> ord(V, -1), low(V, -1);
	bridgeCont = 0, cnt = 0;
	for (int i = 0; i < V; i++)
	{
		if (bridgeCont)
			return true;
		if (ord[i] == -1)
			searchC(g, ord, low, pii(0,0));
	}
	return (bridgeCont > 0);
}

int main()
{
	while (true)
	{
		scanf("%d %d", &V, &E);
		if (!V && !E)
			break;
		Grafo g = Grafo(V, vector<int>());
		for (int i= 0; i < E; i++)
		{
			int x, y;
			scanf("%d %d", &x,&y);
			g[x-1].push_back(y-1);
			g[y-1].push_back(x-1);
		}
		if (haPontes(g))
			printf("N\n");
		else
			printf("S\n");		
	}
	return 0;
}
