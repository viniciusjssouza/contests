/**********************************************************
* UVA 10092 - The Problem with the problem setter
*
* Autor: Vinicius J. S. Souza
* Data: 01/05/2010
* Tecnicas: Algoritmo de fluxo em redes - Edmond-Karp
*********************************************************/
#include<iostream>
#include<cstdio>
#include<deque>
#include<vector>
#include<queue>
#include<algorithm>
#include<set>

using namespace std;

/*************** Fluxo maximo - Edmond-Karp **************************/
#define MAXN 1200
#define OFFSET 1100 	
#define INF 0x3fffffff
#define SOURCE	MAXN-2
#define SINK	MAXN-1
#define NULO -1

struct edge {
  int v;
  int capacity;
  int flow;
  int residual;
  edge(int lig, int cap) 
  { v = lig, capacity = residual = cap;  flow = 0;}	
};

typedef vector<vector<edge> > grafo;

int np, nk;
int fluxo;
int parent[MAXN];
bool used[MAXN];
grafo g(MAXN, vector<edge>());


void bfs(int source, int sink) {
	for (int i = 0, sz = g.size(); i < sz; i++) {
		parent[i] = NULO;
		used[i] = false;
	}
	queue<int> fila;
	used[source] = true;
	fila.push(source);
	while (!fila.empty()) {
		int w = fila.front();
		fila.pop();
		for (int i = 0, sz = g[w].size(); i < sz; i++) {
			if (!used[g[w][i].v] && g[w][i].residual > 0) {
				fila.push(g[w][i].v);
				used[g[w][i].v] = true;
				parent[g[w][i].v] = w;				
				if (g[w][i].v == sink) return;
			}
		}
	}
}

int find_edge(int x, int y) {
	int e= NULO;
    for (int i=0, sz = g[x].size(); i< sz; i++)
        if (g[x][i].v == y)
             e = i;
	return e;
}

int path_volume(int start, int end){
	int v = parent[end];
    if (v == -1) return(0);
    int eLoc = find_edge(v, end);
    if (start == v)
        return(g[v][eLoc].residual);
    else
        return(min(path_volume(start, v),
                g[v][eLoc].residual));		    
}

void augment_path(int start, int end, int volume) {
    if (start == end) return;
	int v = parent[end];
    int eLoc = find_edge(v,end);        
    g[v][eLoc].flow += volume;
    g[v][eLoc].residual -= volume;
    eLoc = find_edge(end, v);
    g[end][eLoc].residual += volume;
    augment_path(start, v, volume);        	
}

int netflow(grafo &g, int source, int sink) {
    int volume;             /* weight of the augmenting path */
    bfs(source, sink);
    volume = path_volume(source, sink);
    while (volume > 0 ) {
		augment_path(source,sink,volume);
		bfs(source, sink);
		volume = path_volume(source, sink);
    }
}

int main() {
	while (true) {
		scanf("%d %d", &nk, &np);
		if (!nk && !np) 
			break;
		g[SOURCE].clear();
		g[SINK].clear();
		for (int i = 1; i <= nk ; i++) {
			int c;
			scanf("%d", &c);
			g[i+OFFSET].clear();
			g[i+OFFSET].push_back(edge(SOURCE, 0));
			g[SOURCE].push_back(edge(i+OFFSET, c));
		}				
		for (int i = 1; i <= np; i++) {
			int num;
			g[i].clear();
			scanf("%d", &num);
			g[SINK].push_back(edge(i, 0));
			g[i].push_back(edge(SINK,1));				
			for (int k = 0; k < num; k++) {
				int w;
				scanf("%d", &w);
				g[i].push_back(edge(w+OFFSET, 0));
				g[w+OFFSET].push_back(edge(i, 1));
			}	
		}
		netflow(g, SOURCE, SINK);
		bool ok = true;
		for (int i = 0, sz = g[SOURCE].size(); i < sz; i++) {
			if (g[SOURCE][i].residual) {
				ok = false;
				break;
			}
		}
		if (ok) {
			printf("1\n");
			for (int i = 1; i <= nk; i++) {
				for (int k = 0, sz = g[i+OFFSET].size(); k < sz; k++) {
					if (!g[i+OFFSET][k].residual)
						printf("%d ", g[i+OFFSET][k].v);						
				}
				putchar('\n');				
			}
		} else 
			printf("0\n");
	}	
	return 0;
}
