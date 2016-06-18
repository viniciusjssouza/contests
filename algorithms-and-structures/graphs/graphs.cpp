/***********************************************************************
*		Algoritmos de Grafos
*
*************************************************************************/

/*************** Caminho maximo **********************************/
O problema do caminho maximo em um grafo comum é NP-completo. O que
pode ser feito é um DFS utilizando memoization para buscar todos os caminhos.

/****************** Topological sorting ***********************************/
topsort(graph *g, int sorted[])
{
	int indegree[MAXV];
	queue zeroin;
	int x, y;
	int i, j;
	compute_indegrees(g,indegree);
	init_queue(&zeroin);
	for (i=1; i<=g->nvertices; i++)
		if (indegree[i] == 0) 
			enqueue(&zeroin,i);
	j=0;
	while (empty(&zeroin) == FALSE) {
		j = j+1;
		x = dequeue(&zeroin);
		sorted[j] = x;
		for (i=0; i<g->degree[x]; i++) {
			y = g->edges[x][i];
			indegree[y] --;
			if (indegree[y] == 0) 
				enqueue(&zeroin,y);
		}
	}
	if (j != g->nvertices)
	printf("Not a DAG -- only %d vertices found\n",j);
}

compute_indegrees(graph *g, int in[])
{
	int i,j;
	/* counters */
	for (i=1; i<=g->nvertices; i++) 
		in[i] = 0;
	for (i=1; i<=g->nvertices; i++)
		for (j=0; j<g->degree[i]; j++) 
			in[ g->edges[i][j] ]++;
}



/*********** Minimum Spanning Tree - Kruskal - V lg(M) ****************/
unsigned long long kruskal(int start)
{
	unsigned long long total = 0;
	UFinit();
    int count = 0;
	for (int i = 0; i < 3; i++)
	{
		int size = edges[i].size();
		for (int k = 0; k < size; k++)
		{
			if (UFfind(edges[i][k].first) != UFfind(edges[i][k].second) )
			{
				UFmerge(edges[i][k].first, edges[i][k].second);
				if (!i) 
					total += MIN;
				else if (i == 1)
					total += MED;
				else
					total += MAX;
				count++;
				if (count >= N-1)
					return total;		
			}
		}
	}
	return total;
}

/**
* BFS capaz de descobrir se o grafo eh bipartido, ou seja, se este pode ser
* bicolorido.
*/
bool isBicolorable(const int &v)
{		
	deque<int> fila;
	colored[v] = RED;
	fila.push_back(v);

	while (fila.size())
	{
		register int vertice = fila[0];
		fila.erase(fila.begin());
		for (register int i = 0; i < arestas[vertice].size(); i++)
		{
			if (!colored[arestas[vertice][i]])
			{
				colored[arestas[vertice][i]] = -colored[vertice];
				parent[arestas[vertice][i]] = vertice;
				fila.push_back(arestas[vertice][i]);
			}
			else if (parent[vertice] != arestas[vertice][i] && 
				colored[arestas[vertice][i]] == colored[vertice])
				return false;				
		}
	}
	return true;		
}			


/********* Algortimo de componentes fortemente conexas - grafos direcionados - TARJAN*/
Input: Graph G = (V, E)

index = 0                         // DFS node number counter 
S = empty                         // An empty stack of nodes
forall v in V do
  if (v.index is undefined)       // Start a DFS at each node
    tarjan(v)                     // we haven't visited yet

procedure tarjan(v)
  v.index = index                 // Set the depth index for v
  v.lowlink = index
  index = index + 1
  S.push(v)                       // Push v on the stack
  forall (v, v') in E do          // Consider successors of v
    if (v'.index is undefined)    // Was successor v' visited?
        tarjan(v')                // Recurse
        v.lowlink = min(v.lowlink, v'.lowlink)
    else if (v' is in S)          // Was successor v' in stack S? 
        v.lowlink = min(v.lowlink, v'.index)
  if (v.lowlink == v.index)       // Is v the root of an SCC?
    print "SCC:"
    repeat
      v' = S.pop
      print v'
    until (v' == v)


/*************************************************************************
**************** Fluxo maximo - Ford Fulkerson **************************
*************************************************************************/
#define NULO -1
#define MAXN  300
// Definicoes para bipartite matching
#define SOURCE  MAXN-2
#define SINK 	MAXN-1
#define OFFSET  110

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

typedef vector<vector<edge> > grafo;

int parent[MAXN];
bool used[MAXN];
grafo g(MAXN, vector<edge>());


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
				if (g[w][i].to == sink) return; // cuidado ao utilizar!!
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

/* Cuidado ao adicionar edges da arvore residual!! Deve-se primeiro verificar se
   já não existe uma edge de volta entre as arestas: */
for (int i = 1; i <= N; i++) {
	for (int k = 0; k < g[i].size(); k++){
		if (find_edge(g, g[i][k].to, i) == NULO)
			g[g[i][k].to].push_back(edge(i, 0, true));
	}
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

/*********** Caminho Hamiltoniano ******************/
In the mathematical field of graph theory, a Hamiltonian path (or traceable path), is a path 
in an undirected graph which visits each vertex exactly once. A Hamiltonian cycle 
(or Hamiltonian circuit) is a cycle in an undirected graph which visits each vertex exactly 
once and also returns to the starting vertex. Determining whether such paths and cycles exist 
in graphs is the Hamiltonian path problem which is NP-complete.

A simple graph with n vertices (n ≥ 3) is Hamiltonian if each vertex has degree n/2 or greater.

/******** Caminho Euleriano ****************************/
An Eulerian path (also known as Eulerian trail or Euler walk) is a path that uses each edge 
exactly once, while an Eulerian circuit (also known as Eulerian cycle or Euler tour) is a cycle 
that begins and ends in the same vertex.

Eulerian Circuits
   • For undirected graph, if the graph is connected and every vertex has an even
       degree, there exists an Eulerian Circuit for the graph
   • For a directed graph, if the graph is strongly connected and indegree of every
       vertex is equal to the outdegree, there exists an Eulerian Circuit for the graph.
Eulerian Path
  	Um grafo nao direcionado possui um caminho euleriano se tiver um numero de vertices
de grau impar igual a 0 ou 2. Nao existe um grafo com apenas um vertice de grau
impar. Para grafos com dois vertices de grau impar, o caminho euleriano inicia em
um e termina no outro.

ATENCAO: um vertice que liga a si mesmo em um grafo nao orientado conta como grau + 2
(duas ligacoes).

void getEulerianCycle(map<int, list<int> > &grafo, deque<int> &path, int v)
{
	if (!grafo[v].size())
		path.push_front(v);
	else
	{
		for (list<int>::iterator ite = grafo[v].begin(); ite != grafo[v].end(); ite++)
		{
			int color = *ite;
			list<int>::iterator aux = ite;
			ite--;
			grafo[v].erase(aux);			
			for (list<int>::iterator ite2 = grafo[color].begin(); ite2 != grafo[color].end(); ite2++)
			{
				if (*ite2 == v)
				{
					grafo[color].erase(ite2);
					break;
				}
			}			
			getEulerianCycle(grafo, path, color);
		}
		path.push_front(v);
	}
}

/************* Floyd-Warshall **********************************/
for (int k = 1; k <= N; k++) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j<= N; j++) {
			g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
		}
	}
} 


/******* Dijkistra *************/
int getCaminhoMin(Grafo &g, int start, int destination, vector<pii> &parent)
{
    parent = vector<pii>(n, pii(-1,-1));
	vector<int> distance(n, MAX);
    priority_queue<pii, vector<pii>, greater<pii> > fila;
	distance[start] = 0;
	fila.push(pii(0, start));

	while (!fila.empty())
	{
		pii top = fila.top();
		fila.pop();
		int v = top.second, d = top.first;
		if (d <= distance[v])
		{
			for (int i = 0; i < g[v].size(); i++)
			{
				int v2 = g[v][i].lig, cost = g[v][i].peso;
				if (distance[v2] > distance[v] + cost)
				{
					distance[v2] = distance[v] + cost;
					parent[v2] = pii(v, i);
					fila.push(pii(distance[v2], v2));
				}
			}
		}
	}
	return distance[destination];
}
 
/*** Exemplo de procedimento de montagem de um grafo **/
for (int i = 0; i < m; i++)
{
    int x, y, peso;
    cin >> x; 
    Aresta a;
    cin >> a.lig >> a.peso; 
    g.arestas[x].push_back(a);
}

/*************** Breadth First Search - Busca em largura *****************************/
bfs(graph *g, int start)
{
        queue q;                        /* queue of vertices to visit */
        int v;                          /* current vertex */
        int i;                          /* counter */
        init_queue(&q);
        enqueue(&q,start);
        discovered[start] = TRUE;
        while (empty(&q) == FALSE) {
                v = dequeue(&q);
                process_vertex(v);
                processed[v] = TRUE;
                for (i=0; i<g->degree[v]; i++)
                    if (valid_edge(g->edges[v][i]) == TRUE) {
                        if (discovered[g->edges[v][i]] == FALSE) {
                                enqueue(&q,g->edges[v][i]);
                                discovered[g->edges[v][i]] = TRUE;
                                parent[g->edges[v][i]] = v;
                        }
                        if (processed[g->edges[v][i]] == FALSE)
                                process_edge(v,g->edges[v][i]);
                    }
        }
}


/***************** Depth First Search - Busca em profundidade ********************/
dfs(graph *g, int v)
{
        int i;                        /* counter */
        int y;                        /* successor vertex */
        if (finished) return;         /* allow for search termination */
        discovered[v] = TRUE;
        process_vertex(v);
        for (i=0; i<g->degree[v]; i++) {
                y = g->edges[v][i];
                if (valid_edge(g->edges[v][i]) == TRUE) {
                        if (discovered[y] == FALSE) {
                                parent[y] = v;
                                dfs(g,y);
                        } else
                                if (processed[y] == FALSE)
                                        process_edge(v,y);
                }
                if (finished) return;
        }
        processed[v] = TRUE;
}

/********** Encontrando ciclos utilizando DFS ************/
   That all edges fall into these two classes is an amazing property of depth-first search.
Why can’t an edge go to a brother or cousin node instead of an ancestor? In DFS, all
nodes reachable from a given vertex v are expanded before we finish with the traversal
from v, so such topologies are impossible for undirected graphs. The case of DFS on
directed graphs is somewhat more complicated but still highly structured.
   Back edges are the key to finding a cycle in an undirected graph. If there is no back
edge, all edges are tree edges, and no cycle exists in a tree. But any back edge going
from x to an ancestor y creates a cycle with the path in the tree from y to x. Such a
cycle is easy to find using dfs:

process_edge(int x, int y)
{
           if (parent[x] != y) {         /* found back edge! */
                     printf("Cycle from %d to %d:",y,x);
                     find_path(y,x,parent);
                     finished = TRUE;
           }
}

/******** Componentes conectadas *****************/
A connected component of an undirected graph is a maximal set of vertices such that
there is a path between every pair of vertices. These are the separate “pieces” of the
graph such that there is no connection between the pieces.
  An amazing number of seemingly complicated problems reduce to finding or counting
connected components. For example, testing whether a puzzle such as Rubik’s cube or
the 15-puzzle can be solved from any position is really asking whether the graph of legal
configurations is connected.
  Connected components can easily be found using depth-first search or breadth-first
search, since the vertex order does not matter. Basically, we search from the first vertex.
Anything we discover during this search must be part of the same connected component.
We then repeat the search from any undiscovered vertex (if one exists) to define the
next component, and so on until all vertices have been found:

connected_components(graph *g)
{
  int c;
  int i;                          /* counter */
  initialize_search(g);
  c = 0;
  for (i=1; i<=g->nvertices; i++)
          if (discovered[i] == FALSE) {
                  c = c+1;
                  printf("Component %d:",c);
                  dfs(g,i);
                  printf("\n");
          }
}

/******************************** Pontes em grafos *****************************/
/*******************************************************************************/
Uma aresta de um grafo é uma  ponte  (= bridge = separation edge)  se ela é a única aresta que 
atravessa algum corte do grafo.  [Pontes são também conhecidas com arestas de corte, mas nós 
não vamos usar essa terminologia.]
Em outras palavras, uma ponte é uma aresta cuja remoção aumenta o número de componentes do grafo. 

We use the vertex-indexed array low to keep track of the lowest preorder number (ord value) 
referenced by any back edge in the subtree rooted at the vertex. For example, the value of low[9]
is 2 because one of the back edges in the subtree rooted at 9 points to 4 (the vertex with preorder 
number 2), and no other back edge points higher in the tree. Nodes 5, 7, and 12 are the ones for 
which the low value is equal to the ord value.

int V, E;
int bridgeCont, cnt;

void searchC(Grafo &g, vector<int> &ord, vector<int> &low, pii par)
{
	int v = par.second;
	ord[v] = cnt++;
	low[v] = ord[v];
	for (int i = 0; i < g[v].size(); i++)
	{
		if (bridgeCont)
			return;
		int v2 = g[v][i];
		if (ord[v2] == -1)
		{
			searchC(g, ord, low, pii(v,v2));
			if (low[v] > low[v2])
				low[v] = low[v2];
			if (low[v2] == ord[v2])
			{
				bridgeCont++; // v-v2 eh uma ponte
				return;
			}			
		}
		else if (v2 != par.first)
			if (low[v] > ord[v2]) 
				low[v] = ord[v2];  		
	}	
}

bool haPontes(Grafo &g)
{
	vector<int> ord(V, -1), low(V, -1);
	bridgeCont = 0, cnt = 0;
	for (int i = 0; i < V; i++)
	{
		if (bridgeCont)
			return true;
		if (ord[i] == -1)
			searchC(g, ord, low, pii(i,i));
	}
	return (bridgeCont > 0);
}


