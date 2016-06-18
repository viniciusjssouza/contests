/**************************************************************************
* Paises em Guerra - Regional - Maratona 2006
*
* Autor: Vinicius J. S. Souza
* Data: 14/03/2010
* Tecnicas: dijkistra + memoization(e nao floyd-warshall!)
* Dificuldade(1-10): 6
***********************************************************************/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
#include<deque>
#include<queue>
#include<map>
#include<algorithm>

#define INF 0x3f3f3f3f

using namespace std;

typedef pair<int, int> pii;

int N, E, K, i, k;
deque<deque<pii> >  g(510, deque<pii>());
int dist[510][510];
bool processed[510];
bool lig[510][510];

void dijkistra(int start) {
	priority_queue<pii, vector<pii>, greater<pii> > fila;
	dist[start][start] = 0;
	fila.push(pii(0, start));
	while (!fila.empty()) {
		pii top = fila.top();
		fila.pop();
		int v = top.second, d = top.first;		
		if (d <= dist[start][v]) {
			int size = g[v].size();
			for (int i = 0; i < size; i++) {
				int v2 = g[v][i].second;
				int cost = (lig[v][v2] && lig[v2][v]) ? 0 : g[v][i].first;
				if (dist[start][v2] > dist[start][v] + cost){
					dist[start][v2] = dist[start][v] + cost;
					fila.push(pii(dist[start][v2], v2));
				}
			}

		}
	}
	processed[start] = true;

}

int main() {
	long s = clock();
	while (true) {
		scanf("%d %d", &N, &E);
		if (!N)
			break;
		for (i = 1; i <= N; i++) {
			g[i].clear();
			dist[i][i] = 0;
			processed[i] = false;
			for (k = i+1; k <= N; k++) {
				dist[i][k] = dist[k][i] = INF; 
				lig[i][k] = lig[k][i] = false;
			}
		}
		for (i = 0; i < E; i++) {
			int a, b, w;
			scanf("%d %d %d", &a, &b, &w);
			g[a].push_back(pii(w, b));
			lig[a][b]= true;
		}
		scanf("%d", &K);
		
		
		for (i = 0; i < K; i++) {
			int o, d;
			scanf("%d %d", &o, &d);
			if (!processed[o]) 
				dijkistra(o);
			int result = dist[o][d];
			if (result >= INF)				
				printf("Nao e possivel entregar a carta\n");
			else
				printf("%d\n", result);

		}	
		putchar('\n');	
	}
//cout << (double)(clock()-s) / (double)CLOCKS_PER_SEC << endl;
	return 0;
}

