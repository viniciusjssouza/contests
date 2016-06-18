/****************************************************************
* E-Reliable Nets - North America - East Central - 2005
*
* Autor: Vinicius J. S. Souza
* Data: 29/08/2010
* Tecnicas: Busca recursiva + algoritmo de Tarjan para pontes em Grafos
* Dificuldade (1-10): 6
*****************************************************************/
#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

#define INF 0x3fffffff

int N, M;

typedef vector<vector<int> > grafo;
typedef pair<int,int> pii;

int best, bridgeCont, cnt;
bool enable[25];
int w[25], lig[25][2], ord[20], low[20];
grafo g;

void searchC(pii par)
{
	int v = par.second;
	ord[v] = cnt++;
	low[v] = ord[v];
	for (int i = 0; i < g[v].size(); i++)
	{
		if (bridgeCont)
			return;
		int e = g[v][i];
		if (!enable[e])
			continue;
		int v2 = lig[e][0];
		if (v2 == v)
			v2 = lig[e][1];
		
		if (ord[v2] == -1)
		{
			searchC(pii(v,v2));
			if (low[v] > low[v2])
				low[v] = low[v2];
			if (low[v2] == ord[v2])
			{
				bridgeCont++; // v-v2 eh uma ponte
				return;
			}			
		}
		else if (v2 != par.first) {
			if (low[v] > ord[v2]) 
				low[v] = ord[v2];  
		}		
	}	
}

bool isReliable()
{
	memset(ord, -1, sizeof(ord));
	memset(low, -1, sizeof(low));
	bridgeCont = cnt = 0;
	searchC(pii(1,1));
	for (int i = 1; i <= N; i++)
	{
		if (ord[i] < 0)
			return false;
	}
	return (bridgeCont == 0);
}

void backtrack(int e, int cost) {
	enable[e] = true;
	cost += w[e];
	if (cost < best){
		if (isReliable()) {
			best = cost;
		} else {
			for (int i = e+1; i < M; i++) {
				backtrack(i, cost);
			}
		}
	}
	cost -= w[e];
	enable[e] = false;
}

int main() {
	int tcase = 1;
	while (1) {
		scanf("%d %d", &N, &M);
		if (!N && !M)
			break;
		g = grafo(N+1);
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &lig[i][0], &lig[i][1], &w[i]);
			g[lig[i][0]].push_back(i);
			g[lig[i][1]].push_back(i);
		}
		best = INF;
		memset(enable, true, sizeof(enable));
		if (!isReliable()) {
			printf("There is no reliable net possible for test case %d.\n", tcase++);
			continue;
		}
		memset(enable, false, sizeof(enable));
		for (int i = 0; i < M; i++) {
			backtrack(i,0);
		}
		if (best < INF)		
			printf("The minimal cost for test case %d is %d.\n", tcase++, best);
		else 
			printf("There is no reliable net possible for test case %d.\n", tcase++);
	}
	return 0;
} 
