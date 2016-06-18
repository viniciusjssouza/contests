/***********************************************************************
* Final Mundial de 2008 - Seletivas IME-USP 2007
*
* Autor: Vinicius J. S. Souza
* Data: 10/03/2010
* Tecnicas: all-pairs shortest path - floyd-warshall pausado
* Dificuldade (1-10): 6
***********************************************************************/
#include<iostream>
#include<algorithm>
#include<deque>
#include<cstdio>

#define MAXV 110
#define INF  0x3f3f3f3f

using namespace std;

int N, M, C;

struct Co {
	int o;
	int d;
	int idx;
};

int cities[MAXV][MAXV];
deque<deque<Co> > cons(MAXV, deque<Co>());
int inst = 1;
int result[10010];

int main() {
	while (!feof(stdin) && scanf("%d %d", &N, &M) == 2) {
		if (inst > 1)
			putchar('\n');
		for (int i = 0; i <= N; i++) {
			cons[i].clear();
			for (int k = i+1; k <= N; k++) {
				cities[i][k] = cities[k][i] = INF;
			}
		}
		for (int i = 0; i < M; i++) {
			int u,v,w;
			scanf("%d %d %d", &u, &v, &w);
			cities[u][v] = min(w, cities[u][v]);
		}
		scanf("%d", &C);
		for (int i = 0; i < C; i++) {
			Co co;
			int t;
			scanf("%d %d %d", &co.o, &co.d, &t);
			co.idx = i;
			cons[t].push_back(co);
		}
		for (int k = 0; k <= N; k++) {
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					cities[i][j] = min(cities[i][j], cities[i][k]+cities[k][j]);	
				}
			}
			int size = cons[k].size();
			for (int i = 0; i < size; i++) {
				result[cons[k][i].idx] = cities[cons[k][i].o][cons[k][i].d];
				if (result[cons[k][i].idx] >= INF)
					result[cons[k][i].idx] = -1;
			}
		}		
		printf("Instancia %d\n", inst++);
		for (int i = 0; i < C; i++) {
			printf("%d\n",result[i]);	
		}		
		
	}
	return 0;
}
