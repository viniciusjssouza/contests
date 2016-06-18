/****************************************************************
* ACM 2011 - Latin America - H - Hedge Mazes
*
* Autor: Vinicius J. S. Souza
* Data: 7/11/2011
* Tecnicas: Teoria de grafos - descoberta de pontes
***************************************************************/
#include<iostream>
#include<cstdio>
#include<set>
#include<vector>
#include<cstdlib>
#include<cstring>
#include<algorithm>

#define para(i,B,N) for(int i = B; i < N; i++)
#define debug false
#define trace(x...) 	if(debug)printf(x);

using namespace std;

typedef vector<vector<int> > Grafo;
typedef pair<int,int> pii;

int V, E, Q;
bool visited[10010];
int cc[10010], comp;
Grafo g, g2;

int bridgeCont, cnt;

void searchC(Grafo &g, vector<int> &ord, vector<int> &low, pii par)
{
	int v = par.second;
	ord[v] = cnt++;
	low[v] = ord[v];
	for (int i = 0; i < g[v].size(); i++)
	{
		int v2 = g[v][i];
		if (ord[v2] == -1)
		{
			searchC(g, ord, low, pii(v,v2));
			if (low[v] > low[v2])
				low[v] = low[v2];
			if (low[v2] == ord[v2])
			{
				g2[v].push_back(v2);
				g2[v2].push_back(v);
				bridgeCont++; // v-v2 eh uma ponte
				//return;
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
		if (ord[i] == -1)
			searchC(g, ord, low, pii(i,i));
	}
	return (bridgeCont > 0);
}

void explorar(Grafo &g, int v) {
	visited[v] = true;
	cc[v] = comp;
	
	para(i,0,g[v].size()) {
		int w = g[v][i];
		if (!visited[w]) {
			explorar(g, w);				
		}
	}	
}

void dfs(Grafo &g) {
	para(v,0,V) {
		visited[v] = false;
		comp = 0;		
	}
	para(v,0,V) {
		if (!visited[v]) {
			explorar(g,v);
			comp++;
		}
	}
}

int main() {
	while (1) {
		scanf("%d %d %d", &V, &E, &Q);
		if (!V && !E && !Q)
			break;
		int a,b;
		g = Grafo(V, vector<int>());
		g2 = Grafo(V, vector<int>());
		para(i,0,E) {
			scanf("%d %d", &a, &b);
			a--; b--;
			g[a].push_back(b);
			g[b].push_back(a);
		}
		haPontes(g);
		dfs(g2);
		// queries em tempo constante
		para(q,0,Q) {
			scanf("%d %d", &a, &b);
			a--; b--;
			if (cc[a] == cc[b])
				printf("Y\n");
			else 
				printf("N\n");
		}
		printf("-\n");
	}
	return 0;
}
