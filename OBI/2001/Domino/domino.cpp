/*************************************************************************
* Domino - OBI 2001
*
* Autor: Vinicius J. S. Souza
* Data: 14/07/2010
* Tecnicas: caminho euleriano
* Dificuldade(1-10): 5
************************************************************************/
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>

using namespace std;

typedef vector<vector<int> > grafo;

bool conexo(grafo &g, int start) {
	queue<int> fila;
	fila.push(start);
	bool used[7];
	memset(used, false, sizeof(used));
	used[start] =true;
	
	while(!fila.empty()) {
		int v = fila.front();
		fila.pop();
		for (int i = 0; i < g[v].size(); i++) {
			int w = g[v][i];
			if (!used[w]) {
				used[w] = true;
				fila.push(w);
			}
		}
	}
	for (int i = 0; i <= 6; i++) {
		if (g[i].size() && !used[i])
			return false;
	}
	return true;		
}

int main() {
	int N, tcase=1;
	while (true) {
		scanf("%d", &N);
		if (!N)
			break;
		grafo g(7);
		int x,y;
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
			g[y].push_back(x);
		}
		int conta = 0;
		for (int i = 0; i <= 6; i++) {
			if (g[i].size() % 2) {
				conta++;
				if (conta > 2)
					break;
			}
		}
		if (conexo(g, x) && (conta == 0 || conta == 2))
			printf("Teste %d\nsim\n\n", tcase++);
		else 
			printf("Teste %d\nnao\n\n", tcase++);
	}
	return 0;
}
 
