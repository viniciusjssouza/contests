/*****************************************************************************
* Ants Colony - ACM - 2010 - Final Sul-Americana
*
* Autor: Vinicius J. S. Souza
* Data: 28/10/2010
* Tecnicas: dfs
* Dificuldade(1-10): 7 
**********************************************************************/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>

#define para(i,N)  for(int i = 0; i < N; i++) 
#define INF 0x3fffffff

using namespace std;

typedef long long int int64;
typedef pair<int64, int> pii;
typedef vector<vector<pii> > grafo;


int N, A, Q;
int64 dist[100005], L;
int parent[100005], h[100005], root[100005];
int used[100005];

grafo g;

void dfs(int v, int64 d, int hl, int r) {
	root[v] = r;
	dist[v] = d;
	h[v] = hl;
	para(i, g[v].size()) {
		int w = g[v][i].second;			
		if (w == parent[v])
			continue;
		parent[w] = v;
		dfs(w, d+g[v][i].first, hl+1, (v == 0 ? w : r));
	}
}

int main() {	
	while (true) {
		scanf("%d", &N);
		if (!N) break;
		g = grafo(N);
		para(i, N-1) {
			scanf("%d %lld", &A, &L);
			g[i+1].push_back(pii(L, A));
			g[A].push_back((pii(L, i+1)));
		}
		para(i, N) {
			parent[i] = -1;
		}
		dfs(0,0,0,0);
		
		scanf("%d", &Q);
		string result;
		para(i, Q) {
			int a,b, ancA, ancB;
			scanf("%d %d", &a, &b);
			int64 res = 0;
			if (root[a] != root[b]) {
				res = dist[a] + dist[b];	
			}else {
				int ha = h[a];
				int hb = h[b];
				ancA = a;
				ancB = b;
				for (;ha > hb; ha--) {
					ancA = parent[ancA];
				}
				for (;hb > ha; hb--) {
					ancB = parent[ancB];
				}
				while(ancA != ancB) {
					ancA = parent[ancA];
					ancB = parent[ancB];
				}
				res = dist[a] + dist[b] - 2* dist[ancA];
			}
			if (i)
				printf(" %lld", res);	
			else printf("%lld", res);	
		}
		putchar('\n');
	}
	return 0;
}
