/**********************************************************************
* Kids Wishes - ACM 2010 - Final Sul-Americana
*
* Autor: Vinicius J. S. Souza
* Data: 31/10/2010
* Tecnicas: dfs, ciclos em grafos, mapas
* Dificuldade (1-10): 6 
**********************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<map>
#include<set>
#include<vector>
#include<queue>
#include<algorithm>

#define para(i,N) for(int i = 0; i < N; i++)

using namespace std;

typedef vector<set<int> > grafo;

int K, W, conta;
grafo g(100005);
map<int, int> mapa;
int used[100005];

bool findCycle(int v, int parent) {
	used[v] = true;
	conta++;
	set<int>::iterator it = g[v].begin();
	for(; it != g[v].end(); it++) {
		int w = (*it);
		if (!used[w]) {
			if (findCycle(w, v))
				return true;
		} else if (w != parent) {
				return true;	
		}
	}
	return false;
}

int main() {
	while(1) {
		scanf("%d %d", &K, &W);
		if (!K && !W)
			break;
		mapa.clear();
		bool ok = true;
		int id = 1;
		para(i, W) {
			int a, b;
			scanf("%d %d", &a, &b);
			if (!mapa[a]) {
				g[id].clear();
				used[id] = false;
				mapa[a] = id++;				
			}
			if (!mapa[b]) {
				g[id].clear();
				used[id] = false;
				mapa[b] = id++;
			}
			a = mapa[a];
			b = mapa[b];			
			g[a].insert(b);
			g[b].insert(a);
			if (g[a].size() > 2 || g[b].size() > 2)
				ok = false;
		}		
		if (ok) {
			for (int i = 1; i < id; i++) {
				conta = 0;
				if (!used[i] && findCycle(i,-1) && conta < K) {
					ok = false;
					break;
				}		
			}
		}
		printf("%c\n", ok ? 'Y' : 'N');
	}
	return 0;
}

