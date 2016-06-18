/*************************************************************
* A lei vai a cavalos - Seletiva IME-USP - 2006
*
* Autor: Vinicius J. S. Souza
* Data: 27/04/2010
* Tecnicas: algoritmo de fluxo maximo - Edmond-Karp
**************************************************************/
#include<iostream>
#include<queue>
#include<cstdio>
#include<vector>

using namespace std;

#define NULO -1
#define MAXN  300
// Definicoes para bipartite matching
#define SOURCE  MAXN-2
#define SINK 	MAXN-1
#define OFFSET  110

struct edge {
  int v;
  int capacity;
  int flow;
  int residual;
  edge(int lig, int cap) 
  { v = lig, capacity = residual = cap;  flow = 0;}	
};

typedef vector<vector<edge> > grafo;

int N, M, K;
int fluxo;
int parent[MAXN];
bool used[MAXN];
grafo g(MAXN, vector<edge>());

/*************** Fluxo maximo - Edmond-Karp **************************/
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
	int flow = 0;
    bfs(source, sink);
    volume = path_volume(source, sink);
    while (volume > 0 ) {
		flow += volume;
		augment_path(source,sink,volume);
		bfs(source, sink);
		volume = path_volume(source, sink);		
    }
	return flow;
}

int main() {
    int tcase = 1;
    while (!feof(stdin) && scanf("%d %d %d", &N, &M, &K) == 3) {
		g[SOURCE].clear();
		g[SINK].clear();
		for (int i = 1; i <= M; i++) {
			g[i].clear();
			g[SINK].push_back(edge(i, 0));
			g[i].push_back(edge(SINK, 1));	
		}
		for (int i = 1; i <= N; i++) {
			int x;
			scanf("%d", &x);
			g[OFFSET+i].clear();
			g[OFFSET+i].push_back(edge(SOURCE, 0));
			g[SOURCE].push_back(edge(OFFSET+i, x));
		}
		for (int i=0; i< K; i++) {
			int c,s;
			scanf("%d %d", &c, &s);
			g[s].push_back(edge(OFFSET+c, 0));
			g[c+OFFSET].push_back(edge(s, 1));
		}
		int fluxo = netflow(g, SOURCE, SINK);	    
		printf("Instancia %d\n%d\n\n", tcase++, fluxo);		
    }
}
 
