#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

#define INF 0x3fffffff

int C, E, L, P;
int dist[55];
bool used[55];
typedef vector<vector<int> > grafo;
typedef pair<int, int> pii;

void bfs(grafo &g, int start) {
	for (int i = 1; i <= C; i++) {
		used[i] = false;
		dist[i] = INF;
	}
	queue<pii> fila;
	fila.push(pii(start, 0));
	used[start] = true;
	dist[start] = 0;
	while (!fila.empty()){
		int v = fila.front().first, depth = fila.front().second;
		fila.pop();
		if (depth < P) {
			for (int i= 0; i < g[v].size(); i++) {
				int w = g[v][i];
				if (!used[w]) {
					used[w] = true;
					dist[w] = depth+1;
					fila.push(pii(w, depth+1));
				}
			}
		}
	}	
}

int main() {
	int tcase=1;
	while (true) {
		scanf("%d %d %d %d", &C, &E, &L, &P);
		if (!C && !E && !L && !P)
			break;
		grafo g(C+1, vector<int>());
		for (int i = 0; i < E; i++) {
			int x,y;
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
			g[y].push_back(x);	
		}
		bfs(g, L);
		printf("Teste %d\n", tcase++);
		for (int i = 1; i <= C; i++) {
			if (i != L && dist[i] < INF) {
				printf("%d ", i);
			}
		}
		printf("\n\n");
	}
	return 0;
} 
