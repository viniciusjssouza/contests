/***************************************************************
* Passeio de bicicleta - Seletiva IOI
*
* Autor: Vinicius J. S. Souza
* Data: 12/07/2010
* Tecnicas: DFS com memoization
* Dificuldade(1-10): 6
************************************************************/
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

#define NULO -1

using namespace std;

int P, L, I;

typedef vector<vector<int> > grafo;

int path[155], h[155];
int length[155];

int longestPath(grafo &g, int v) {
	if 	(path[v] != NULO)
		return path[v];
	int val = 0;
	for (int i = 0;i < g[v].size(); i++) {
		int w = g[v][i];
		val = max(val, longestPath(g, w)+1);
	} 
	path[v]= val;
	return val;
}


int main() {
	int tcase= 1;
	while (true) {
		scanf("%d %d %d", &P, &L, &I);
		if (!P && !L && !I)
			break;
		for (int i = 1; i <= P; i++) {
			scanf("%d", &h[i]);
		}
		grafo g(P+1, vector<int>());
		memset(path, NULO, sizeof(path));
		for (int i = 0; i < L; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			if (h[x] > h[y]) {
				g[x].push_back(y);
			}
		}
		printf("Teste %d\n%d\n\n", tcase++, longestPath(g, I));
	}
	return 0;
}
 
