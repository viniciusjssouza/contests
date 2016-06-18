/*****************************************************************
* Dengue - OBI 2001
*
* Autor: Vinicius J. S. Souza
* Data: 15/07/2010
* Tecnica: bfs - shortest path em grafos com peso unitario
* Dificuldade: 4
*******************************************************************/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

#define INF 0x3fffffff
#define NULO -1

typedef vector<vector<int> > grafo;
typedef pair<int,int> pii;

int dist[110][110], parent[110], maxDist, posto;
int N;
bool used[110];

void bfs(grafo &g, int start) {
	queue<pii> fila;
	for (int i = 1; i <= N; i++) {
		used[i] = false;
		parent[i] = NULO;
	}
	fila.push(pii(0, start));
	used[start] = true;
	int finalV = NULO;
	while (!fila.empty()) {
		pii par = fila.front();
		fila.pop();
		int v = par.second, custo = par.first;
		for (int i = 0; i < g[v].size(); i++) {
			int w = g[v][i];
			if (!used[w] && dist[start][w] == INF) {
				dist[start][w] = dist[w][start] = custo+1;
				if (dist[start][w] > maxDist) {
					finalV = w;
					maxDist = dist[start][w];
				}
				used[w] = true;
				parent[w] = v;
				fila.push(pii(dist[start][w], w));
			}
		}
	}
	if (finalV != NULO) {
		int conta = maxDist / 2, v = finalV;
		for (int i = 0; i < conta; i++)
			v = parent[v];
		posto = v;
	} 
}

int main() {
	int tcase = 1;
	while (true) {
		scanf("%d", &N);
		if (!N)
			break;
		for (int i = 1; i <= N; i++)
			for (int k = i+1; k <= N; k++)
				dist[i][k] = dist[k][i] = INF;
		grafo g(N+1);
		for (int i = 0; i < N-1; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
			g[y].push_back(x);
		}
		maxDist = -1;
		posto = 1;
		for (int i = 1; i <= N; i++) {
			if (g[i].size() == 1) {
				bfs(g,i);
			}
		}
		printf("Teste %d\n%d\n\n", tcase++, posto);
	}	
	return 0;
} 
