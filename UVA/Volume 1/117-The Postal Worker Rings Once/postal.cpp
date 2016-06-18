/****************************************************************
* UVa 117 - The Postal Worker Rings Once
*
* Autor: Vinicius J. S. Souza
* Data: 28/03/2010
* Tecnicas: Caminho Euleriano + Dijkistra (Shortest Path) 
*************************************************************/
#include<iostream>
#include<deque>
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>

using namespace std;

#define INF 0x3f3f3f3f

typedef pair<int,int> pii;

deque<deque<pii> > g(30);
char input[150];
int dist[1000]; 
int d, o;

int dijkistra() {
    priority_queue<pii, vector<pii>, greater<pii> > fila;
	dist[o] = 0;
	fila.push(pii(0, o));
	while (!fila.empty()) {
		pii top = fila.top();
		fila.pop();
		int v = top.second, d = top.first;
		if (d <= dist[v]) {
			int size = g[v].size();
			for (int i = 0; i < size; i++) {
				int v2 = g[v][i].second, cost = g[v][i].first;
				if (dist[v2] > dist[v] + cost) {
					dist[v2] = dist[v] + cost;
					fila.push(pii(dist[v2], v2));
				}
			}
		}
	}
	return dist[d];
}

int main() {
	while (!feof(stdin)) {
		for (int i = 0; i < 30; i++) {
			g[i].clear();
			dist[i] = INF;				
		}
		int total = 0;
		while (true) {
			if (scanf("%s", input) != 1)
				return 0;
			if (!strlen(input))
				return 0;
			if (!strcmp(input, "deadend"))
				break;
			int len = strlen(input);
			int a = input[0]-'a';
			int b = input[len-1]-'a';
			g[a].push_back(pii(len, b));
			g[b].push_back(pii(len, a));	
			total += len;
		}	
		int odd = 0;
		for (int i = 0; i < 30; i++) {
			if (g[i].size() & 1) {
				if (!odd)
					o = i;
				else if (odd == 1)
					d = i;
				odd++;					
			}
		}
		if (!odd) {
			printf("%d\n", total);
		} else {
			printf("%d\n", total + dijkistra());		
		}		
	}
	return 0;	
}
