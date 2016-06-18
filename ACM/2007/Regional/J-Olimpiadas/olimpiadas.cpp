/****************************************************************************
* J - Olimpiadas - Regional 2007
*
* Autor: Vinicius J. S. Souza
* Data: 06/07/2010
* Tecnicas: Grafos - variacao do algoritmo de max flow
* Dificuldade: 8
*****************************************************************************/
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<map>
#include<cmath>

#define INF 0x3fffffff

using namespace std;

/********************** Fluxo maximo em redes **********************/
/********************* Edmond - Karp *****************************/
#define NULO -1
#define MAXN  55

struct edge {
  int to;
  int capacity;
  int flow;
  int residual;
  bool back;	
  edge(int lig, int cap, bool b = false) 
  { to = lig, capacity = residual = cap;  flow = 0; back = b;}	
  int getFlow() {return capacity - residual;}	
};

struct node{
  int v;
  int minFlow;
  int ndias;
  node(int vert, int m , int d) 
  { v = vert, minFlow = m;  ndias = d;}	
};


typedef vector<vector<edge> > grafo;
typedef pair<int,int> pii;
int N, M, A;
int fluxo;
int parent[MAXN];
bool used[MAXN];
int maxDias;
map<int, int> days;


int find_edge(grafo &g, int x, int y) {
	int e= NULO;
    for (int i=0, sz = g[x].size(); i< sz; i++) {
        if (g[x][i].to == y) {
             e = i;
			break;
		}
	}
	return e;
}

void removeFlow(grafo &path, int flow) {
   int ant = N;
   int v = parent[N];
   while (v > 0) {
	  int e = find_edge(path, v, ant);
      path[v][e].residual += flow;
	  ant = v;
	  v = parent[v];
   }
}

bool findPath(grafo &g) {
	for (int i = 1; i <= N; i++) {
		parent[i] = NULO;
		used[i] = false;
	}
	queue<node> fila;
	fila.push(node(1, INF, 0));
	used[1] = true;
	while (!fila.empty()) {
		node no = fila.front();
		fila.pop();
		if (no.v == N){
			days[no.ndias] += no.minFlow;
			if (maxDias < no.ndias)
			  maxDias = no.ndias;
			removeFlow(g, no.minFlow);
			return true;
		}
		for (int i = 0; i < g[no.v].size(); i++) {
			int w = g[no.v][i].to;
			if (!used[w] && g[no.v][i].getFlow() > 0) {
			    used[w] = true;
				parent[w] = no.v;
				fila.push(node(w, min(no.minFlow, g[no.v][i].getFlow()), no.ndias+1));
			}
		}
	}
	return false;
}

void bfs(grafo &g, int source, int sink) {
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
			if (!used[g[w][i].to] && g[w][i].residual > 0) {
				fila.push(g[w][i].to);
				used[g[w][i].to] = true;
				parent[g[w][i].to] = w;				
				if (g[w][i].to == sink) return; 
			}
		}
	}
}

int path_volume(grafo &g, int start, int end){
	int v = parent[end];
    if (v == -1) return(0);
    int eLoc = find_edge(g, v, end);
    if (start == v)
        return(g[v][eLoc].residual);
    else
        return(min(path_volume(g, start, v),
                g[v][eLoc].residual));		    
}

void augment_path(grafo &g, int start, int end, int volume) {
    if (start == end) return;
	int v = parent[end];
    int eLoc = find_edge(g, v,end);        
    g[v][eLoc].flow += volume;
    g[v][eLoc].residual -= volume;
    eLoc = find_edge(g, end, v);
    g[end][eLoc].residual += volume;
    augment_path(g, start, v, volume);        	
}

int netflow(grafo &g, int source, int sink) {
    int volume;             /* weight of the augmenting path */
	int flow = 0;
    bfs(g, source, sink);
    volume = path_volume(g, source, sink);
    while (volume > 0 ) {
		flow += volume;
		augment_path(g, source,sink,volume);
		bfs(g, source, sink);
		volume = path_volume(g, source, sink);		
    }
	return flow;
}

int main() {
	while (true) {
		scanf("%d %d %d", &N, &M, &A);
		if (!N && !M && !A) break;
		grafo g(N+1, vector<edge>());
		grafo path(N+1, vector<edge>());
		maxDias = -1;
		for (int i = 0; i< M; i++) {
			int o, d, s;
			scanf("%d %d %d", &o, &d, &s);
			g[o].push_back(edge(d, s));
			
		}
		for (int i = 1; i <= N; i++) {
			for (int k = 0; k < g[i].size(); k++){
				if (find_edge(g, g[i][k].to, i) == NULO)
					g[g[i][k].to].push_back(edge(i, 0, true));
			}
		}

		g[0].push_back(edge(1, A));
		g[1].push_back(edge(0, 0, true));
		netflow(g, 0, N);
		
		for (int i = 1; i <= N; i++) {
			for (int k = 0; k < g[i].size(); k++){
				if (!g[i][k].back)
				  path[i].push_back(g[i][k]);
			}
		}
		while(findPath(path));
		int total = 0, soma = 0, conta= 0;		
		while(conta <= maxDias && total < A) {
			soma += days[++conta];
			total += soma;
		}
	    int missing = A - total;
		if (missing > 0)
		  conta += (int)ceil((float)missing / (float)soma);

		if (conta < 0) {
			printf("N:%d M:%d A:%d\n", N, M, A);
			for (int i = 0; i <= N; i++) {
				printf("---- Vertice %d ---------\n", i);
				for (int k = 0; k < g[i].size(); k++){
					printf("Para %d  fluxo:%d  cap:%d res:%d\n", g[i][k].to, g[i][k].getFlow(), g[i][k].capacity, g[i][k].residual);
				}
				putchar('\n');
			}
			return 0;		
		}
		printf("%d\n", conta);
		days.clear();
	}		
	return 0;
}
