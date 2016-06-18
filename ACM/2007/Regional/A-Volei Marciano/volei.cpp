/********************************************************
* ACM - Volei Marciano - Regional de 2007
*
* Autor:Vinicius J. S. Souza
* Data: 21/05/2010
* Tecnicas utilizadas: geometria computacional + fluxo max (Edmond-Karp)
*********************************************************/
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
#include<map>
#include<set>
using namespace std;

#define INF 0x3f3f3f3f
#define all(v) (v).begin(), (v).end()

const float EPS = 1e-5;
inline int cmp(float x, float y = 0, float tol = EPS){
   return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

int N;

struct point {
   float x, y;
   point(float x = 0, float y = 0): x(x), y(y) {}
   point operator +(point q) { return point(x + q.x, y + q.y); }
   point operator -(point q) { return point(x - q.x, y - q.y); }
   point operator *(float t) { return point(x * t, y * t); }
   point operator /(float t) { return point(x / t, y / t); }
   /*produto interno */
   float operator *(point q) { return x * q.x + y * q.y; }
   /* produto vetorial */
   float operator %(point q) { return x * q.y - y * q.x; }
   int cmp(point q) const {
   if (int t = ::cmp(x, q.x)) return t;
   return ::cmp(y, q.y);
   }
   bool operator ==(point q) const { return cmp(q) == 0; }
   bool operator !=(point q) const { return cmp(q) != 0; }
   bool operator < (point q) const { return cmp(q) < 0; }
   static point pivot;
};
point point::pivot;
float abs(point p) { return hypot(p.x, p.y); }
float arg(point p) { return atan2(p.y, p.x); }

typedef vector<point> polygon;
/* Calcula o angulo entre os vetores qp e qr
   ATENCAO: o resultado pode ser negativo!
 */
inline float angle(point p, point q, point r) {
  point u = p - q, v = r - q;
  return atan2(u % v, u * v);
}

inline int ccw(point p, point q, point r) 
{
   return cmp((p - r) % (q - r));
}

////////////////////////////////////////////////////////////////////////////////
// Decide se q está sobre o segmento fechado pr.
//
bool between(point p, point q, point r) {
  return ccw(p, q, r) == 0 && cmp((p - q) * (r - q)) <= 0;
}

///////////////////////////////////////////////////////////////////////////////
// Classifica o ponto p em relação ao polígono T.
//
// Retorna 0, -1 ou 1 dependendo se p está no exterior, na fronteira
// ou no interior de T, respectivamente.
//
int inPoly(point &p, polygon &T) {
  float a = 0; int N = T.size();
  for (int i = 0; i < N; i++) {
    if (between(T[i], p, T[(i+1) % N])) return -1;
    a += angle(T[i], p, T[(i+1) % N]);
  }
  return cmp(a) != 0;
}

/********************** Fluxo maximo em redes **********************/
/********************* Edmond - Karp *****************************/
#define NULO -1
#define MAXN  1000
// Definicoes para bipartite matching
#define SOURCE  MAXN-2
#define SINK 	MAXN-1
#define OFFSET  500

struct edge {
  int v;
  int capacity;
  int flow;
  int residual;
  edge(int lig, int cap) 
  { v = lig, capacity = residual = cap;  flow = 0;}	
};

typedef vector<vector<edge> > grafo;

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
	while (true){
		scanf("%d", &N);
		if (!N) break;
		polygon poly(N);
		set<int> sx, sy;
		for (int i = 0; i < N; i++) {
			scanf("%f %f", &poly[i].x, &poly[i].y);	
			sx.insert(poly[i].x);
			sy.insert(poly[i].y);
		}
		map<int, int> mpX;
		map<int, int> mpY;
		set<int>::iterator itx, ity;
		int cntX = 1;
		int cntY = OFFSET;	
		g[SOURCE].clear();
		g[SINK].clear();
		for (itx = sx.begin(); itx != sx.end(); itx++) {
			for (ity = sy.begin(); ity != sy.end(); ity++) {
				point p(*itx, *ity);
				if (inPoly(p, poly) != 0)
					continue;
				if (!mpX[p.x]) {
					g[cntX].clear();
					g[SOURCE].push_back(edge(cntX, 1));
					g[cntX].push_back(edge(SOURCE, 0));
					mpX[p.x] = cntX++;							
				}
				if (!mpY[p.y]) {
					g[cntY].clear();
					g[cntY].push_back(edge(SINK, 1));
					g[SINK].push_back(edge(cntY, 0));
					mpY[p.y] = cntY++;							
				}					
				int x = mpX[p.x], y = mpY[p.y];
				g[x].push_back(edge(y, 1));
				g[y].push_back(edge(x, 0));
			} 
		}
		int fluxo = netflow(g, SOURCE, SINK);
		printf("%d\n", (sx.size()+sy.size())-fluxo);
	}	
	return 0;
}

